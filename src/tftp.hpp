#ifndef IMAGEFLASHER_TFTP_HPP
#define IMAGEFLASHER_TFTP_HPP

#define MODE_NETASCII 1
#define MODE_OCTET 2
#define DEFAULT_RTT 1

extern "C"{
#include "lwip/api.h"
}

struct ack {
        u16_t opcode;
        u16_t blkno;
};

class TftpClient {
        private:
                struct ip_addr rem_host;
                u16_t rem_port;
                u16_t sec_port;
                u16_t blkno;
                int rtt;
                bool connected;
                u8_t mode;
                err_t err;
                sys_sem_t get_wait;
                sys_sem_t snd_nxt;
                u16_t loc_port;
                int fd;
                struct udp_pcb *pcb;

                friend void hndl_pkt(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *host, u16_t port);
                friend void ack_recvr(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *host, u16_t port);
               

        public:
                TftpClient();
                TftpClient(char *host, u16_t port);
                ~TftpClient();
                int connect(char *host, u16_t port);
                void set_mode(u8_t m);
                void use_local_port(u16_t port);
                int get(char *rem_file, char *loc_file);
                int put(char *file);
                void set_rtt(int value);
                void error(const char *msg, bool fatal);

};

#endif /* IMAGEFLASHER_TFTP_HPP */
