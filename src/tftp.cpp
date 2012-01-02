
#define RAND_LOC_PORT 49127

#include "tftp.hpp"
#include "lwip/udp.h"
#include <unistd.h>
#include <fcntl.h>

TftpClient::TftpClient(){
        connected = false;
        conn = netconn_new(NETCONN_UDP);
        loc_port = RAND_LOC_PORT;
}

TftpClient::~TftpClient()
{
        if(conn == NULL)
                return;
        netconn_close(conn);
        netconn_delete(conn);
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

s8_t TftpClient::connect(char *host, u16_t port)
{

        if(connected == true)
                return ERR_CONN;
        ipaddr_aton(host, &rem_host);
        rem_port = port;
        err_t e = netconn_connect(conn, &rem_host, rem_port);
        return e;
}

TftpClient::TftpClient(char *host, u16_t port)
{
        connect(host, port);   
}

void TftpClient::set_rtt(int value)
{
        rtt = value;
        return;
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

                putchar(data[2]+'0');
                putchar(data[3]+'0');
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
                        return ;

                write(tc->fd, data+4, datalen-4);
                tc->blkno++;
                
                if(datalen-4 < 512){
                        sleep(2);
                        sys_sem_signal(&(tc->get_wait));
                }

                return;

        }

}

int TftpClient::get(char *rem_file, char *loc_file)
{
        struct udp_pcb * pcb = udp_new();
        err = udp_bind(pcb, IP_ADDR_ANY, loc_port);
        if(err = ERR_USE){
                // Port already in use
        }

        if(mode == MODE_NETASCII)
                fd = open(loc_file, O_WRONLY|O_CREAT);
        else
                fd = open(loc_file, O_WRONLY);

        blkno = 1; // Confirm this 

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
        //pbuf_free(p);
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
