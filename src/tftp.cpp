
#define RAND_LOC_PORT 49127

#include "tftp.hpp"
#include "lwip/udp.h"
#include <unistd.h>
#include <fcntl.h>

TftpClient::TftpClient()
{
        connected = false;
        loc_port = RAND_LOC_PORT;
        rtt = DEFAULT_RTT * 1000;
}

void TftpClient::error(const char *msg, bool fatal)
{
        fprintf(stderr, msg);
        fprintf(stderr, "\n");
        if(fatal)
                exit(1);
        return;
}

TftpClient::~TftpClient()
{
        // Any required cleanup
}

static void *safe_malloc(int size)
{
       void *memptr = malloc(size); 
       if(memptr == NULL)
               fprintf(stderr, "Insufficient memory\n"); 
       return memptr;
}

void TftpClient::use_local_port(u16_t port)
{
        loc_port = port;
        return;
}
void TftpClient::set_mode(u8_t m) 
{
        mode = m;
        return;
}

int TftpClient::connect(char *host, u16_t port)
{

        if(connected == true){
               error(lwip_strerr(ERR_ISCONN), false); 
        }

        ipaddr_aton(host, &rem_host);
        rem_port = port;

        return 0;
}

TftpClient::TftpClient(char *host, u16_t port)
{
        err_t e = connect(host, port);   
        if(e != ERR_OK)
                error(lwip_strerr(e), true);
}

void TftpClient::set_rtt(int value)
{
        rtt = value * 1000;
        return;
}

void ack_recvr(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *host, u16_t port)
{
        TftpClient *tc = (TftpClient *) arg;
        if(memcmp(host, &(tc->rem_host), sizeof(struct ip_addr)) != 0)
                return;

        char *data = (char *) p->payload;
        u16_t len = p->len;

        u16_t blk;
        
        u16_t opcode = ntohs(*(u16_t *)data);
        if(opcode == 4){
                char *tmp = data+sizeof(u16_t);
                blk = ntohs(*(u16_t *)tmp);

                if(blk == 0)
                        tc->sec_port = port;

               // Ignore duplicate ACK'S
               if(blk < tc->blkno)
                      return;

               // ACK to current block
               tc->blkno++;
               sys_sem_signal(&tc->snd_nxt);

               return;
        }

        if(opcode == 5){
                tc->error(data+4, true);
        }
        tc->error("Recieved irrelavent data from target..... Ignoring", false);
}

void hndl_pkt(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *host, u16_t port)
{

        TftpClient *tc = (TftpClient *)arg;
        if(memcmp(host, &(tc->rem_host), sizeof(struct ip_addr)) != 0)
                return;

        char *data = (char *)p->payload;
        u16_t datalen = p->len;

        u16_t opcode = ntohs(*(u16_t *)data);
        if(opcode == 3){

                u16_t pktblk = ntohs(*(u16_t *)(data+2));

                // Send ack to pktblk
                struct ack *a = (struct ack *) safe_malloc(sizeof(struct ack));
                a->opcode = htons(4);
                a->blkno = htons(pktblk);
                struct pbuf *sndbuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct ack), PBUF_ROM);
                sndbuf->payload = a;
                udp_sendto(pcb, sndbuf, host, port);
                //pbuf_free(sndbuf);

                // If the pkt isn't a duplicate write the data into f
                if(pktblk < tc->blkno)
                        return;

                write(tc->fd, data+4,datalen-4);

                tc->blkno++;
                
                if(datalen-4 < 512){
                        //sleep(2);
                        sys_sem_signal(&(tc->get_wait));
                }

                return;

        }
        
        if(opcode == 5){
                tc->error(data+4, true);
        }

        tc->error("Recieved irrelavent data from target..... Ignoring", false);

}

int TftpClient::get(char *rem_file, char *loc_file)
{
        struct udp_pcb * pcb = udp_new();
        err = udp_bind(pcb, IP_ADDR_ANY, loc_port);
        if(err != ERR_OK){
                error(lwip_strerr(err), false);
                return -1;
        }

        fd = open(loc_file, O_WRONLY);

        blkno = 1; 

        // Craft the initial get request with appropriate mode 
        int bufsize =  strlen(rem_file) + 4 + (mode == MODE_NETASCII ? strlen("netascii") : strlen("octet")); 
        char *pkt = (char *)safe_malloc(bufsize);
        memset(pkt, 0, bufsize);
        u16_t *opcode = (u16_t *) pkt;
        *opcode = htons(1);
        memcpy(pkt+2, rem_file, strlen(rem_file)+1);
        if(mode == MODE_NETASCII)
                memcpy(pkt+3+strlen(rem_file), "netascii", strlen("netascii"));
        else
                memcpy(pkt+3+strlen(rem_file), "octet", strlen("octet"));
  

        // Set the packet recv handler
        udp_recv(pcb, hndl_pkt, this);

        // Send the packet 
        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, bufsize, PBUF_ROM); 
        p->payload = pkt;
        udp_sendto(pcb, p, &rem_host, rem_port);

        // Block the thread until the request is satisfied
        sys_sem_new(&get_wait, 0);
        sys_arch_sem_wait(&get_wait, 0);
        sys_sem_free(&get_wait);
        udp_remove(pcb);
        //pbuf_free(p);
}

int TftpClient::put(char *filename)
{
        struct udp_pcb * pcb = udp_new();
        err = udp_bind(pcb, IP_ADDR_ANY, loc_port);
        if(err != ERR_OK){
                error(lwip_strerr(err), false);
                return -1;
        }


        fd = open(filename, O_RDONLY);

        sys_sem_new(&snd_nxt, 0);

        // Craft the initial get request with appropriate mode 
        int bufsize =  strlen(filename) + 4 + (mode == MODE_NETASCII ? strlen("netascii") : strlen("octet")); 
        char *pkt = (char *)safe_malloc(bufsize);
        memset(pkt, 0, bufsize);
        u16_t *opcode = (u16_t *) pkt;
        *opcode = htons(2);
        memcpy(pkt+2, filename, strlen(filename)+1);
        if(mode == MODE_NETASCII)
                memcpy(pkt+3+strlen(filename), "netascii", strlen("netascii"));
        else
                memcpy(pkt+3+strlen(filename), "octet", strlen("octet"));



        blkno = 0;
        // Set the packet recv handler
        udp_recv(pcb, ack_recvr, this);

        // Send the packet 
        u32_t w_ack;
        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, bufsize, PBUF_ROM); 
        p->payload = pkt;
        do{

                err_t e = udp_sendto(pcb, p, &rem_host, rem_port);
                if(e != ERR_OK)
                        error(lwip_strerr(e), false);
                w_ack = sys_arch_sem_wait(&snd_nxt, rtt);

        }while(w_ack == SYS_ARCH_TIMEOUT);
        pbuf_free(p);


        // Craft the next data packet
        char data[600];
        u16_t *tmp;
        int kbytes;

        while(1){
                tmp = (u16_t *)data;
                *tmp = htons(3);
                tmp = (u16_t *)(data+sizeof(u16_t));
                *tmp = htons(blkno);

                kbytes = read(fd, data+4, 512);

                p = pbuf_alloc(PBUF_TRANSPORT, 4+kbytes, PBUF_ROM);
                p->payload = data;

                do{
                        err_t e = udp_sendto(pcb, p, &rem_host, sec_port);
                        w_ack = sys_arch_sem_wait(&snd_nxt, rtt);
                }while(w_ack == SYS_ARCH_TIMEOUT);
                pbuf_free(p);

                if(kbytes < 512){
                        udp_remove(pcb);
                        sec_port = 0;
                        free(pkt);
                        return 0;
                }
        }
}


/*

int TftpClient::hndl_pkt(char *pkt, int pktlen, u16_t blkno, int fd)
{
        u16_t *pktblk = (u16_t*)pkt;

        // Send ack to pktblk
        struct ack a;
        a.opcode = 4;
        a.blkno = *pktblk;
        struct netbuf *sndbuf = netbuf_new();
        err = netconn_send(conn, sndbuf);
        netbuf_delete(sndbuf);

        // If the pkt isn't a duplicate write the data into f
        if(*pktblk < blkno)
                return blkno;
        
        write(fd, pkt+2, pktlen-2);
        return blkno+1;
}

int TftpClient::get(char *rem_file, char *loc_file)
{
        int loc_fd = open(loc_file, O_WRONLY);
        char *data;
        u16_t datalen;

     //    Craft the initial get request with appropriate mode 
        int bufsize =  strlen(rem_file) + 4 + (mode == MODE_NETASCII ? strlen("netascii") : strlen("octet")); 
        char *pkt = (char *)safe_malloc(bufsize);
        memset(pkt, 0, bufsize);
        u16_t *opcode = (u16_t *) pkt;
        *opcode = htons(1);
        memcpy(pkt+2, rem_file, strlen(rem_file)+1);
        if(mode == MODE_NETASCII)
                memcpy(pkt+3+strlen(rem_file), "netascii", strlen("netascii"));
        else
                memcpy(pkt+3+strlen(rem_file), "octet", strlen("octet"));

        for(int i=0;i<bufsize; i++){
                if(pkt[i] < 9)
                        putchar(pkt[i]+'0');
                else
                        putchar(pkt[i]);
        }

        //write(0, pkt, bufsize);

        // Send the RRQ 
        struct netbuf *sndbuf = netbuf_new();
        netbuf_ref(sndbuf, pkt, bufsize);
        err = netconn_send(conn, sndbuf);
        netbuf_delete(sndbuf);
        free(pkt);

        if(err != ERR_OK)
                return -1;

        // Keep recv-ing data packets 

        u16_t curblk = 0;  // #edit check this one if starting block no is 1
        while(1){

        printf("Here\n");
                netconn_recv(conn, &sndbuf); 
        printf("Here\n");
                netbuf_data(sndbuf, (void **)&data, &datalen);  

                opcode = (u16_t *)data;
                if(*opcode == 5){
                        curblk = hndl_pkt(data+2, datalen-2, curblk, loc_fd);
                        netbuf_delete(sndbuf);
                        if(datalen-4 < 512){
                                break;
                        }
                }

        }

        close(loc_fd);
}

*/
