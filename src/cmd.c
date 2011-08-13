
#include "lwip/api.h"
#include <fcntl.h>
#include <errno.h>
#define TFTP_PORT 69

int main(int argc, char **argv)
{
  if(argc != 3){
    printf("Usage : imgflshr <interface> <firmware-image>\n");
    exit(1);
  }

  my_init();
  flash(argv[1],argv[2]);

}


void flash(char *target_addr, char* img)
{

  tftp_serv(img);

}


void tftp_serv(char* img)
{

}


/*
void http_serv(char *img)
{
  struct netconn *serv, *client;
  struct ip_addr *peer_addr, *target_addr;

  struct netbuf *recv_buf, *send_buf;
  char *recv_data, *send_data;
  char *errbuf;
  char buf[512];
  u32_t len, block, imgfd, nbytes;
  

  serv = netconn_new(NETCONN_TCP); 

  netconn_bind(serv, NULL, HTTP_PORT);

  netconn_listen(serv);

  while(1){
    if(netconn_accept(serv, &client) != ERR_OK){
      //Error in connection
    }
    
    netconn_peer(client, &peer_addr, &peer_port);

    if(memcmp(peer_addr, target_addr, sizeof(struct ip_addr)) != 0){
      netconn_delete(client);
      continue;
    }

    while(1){
      netconn_recv(client, recv_buf);
        if(recv_buf == NULL)
          break;
      netbuf_data(recv_buf, &recv_data, &len);

      if(memcmp(recv_buf,"GET /\r\n",strlen("GET /\r\n")) == 0){
      // HTTP Get Request
      }


    }

  }
  
}

void tftp_client(char *img)
{


}

void telnet_client(char *img)
{


}

*/
