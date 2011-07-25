
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

  struct netconn *serv, *client;
  struct ip_addr *peer_addr, *target_addr;

  u16_t peer_port, *opcode;
  struct netbuf *recv_buf, *send_buf;
  char *recv_data, *send_data;
  char *errbuf;
  char buf[512];
  u32_t len, block, imgfd, nbytes;
  

  serv = netconn_new(NETCONN_UDP); 

  netconn_bind(serv, NULL, TFTP_PORT);

  netconn_listen(serv);

  while(1){
    errno = netconn_accept(serv, &client);
    
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

      opcode = recv_data;

      switch(*opcode){

        case 1:
          // TFTP RRQ
          // Check if routers make requests
          // If they do match with the char *img
          //  If they don't match send error
          // If they do match 
          //  Open the image file 
          // Send first block
          if(block != 0){
            error("Unexpected RRQ from client : quitting\n");
            errbuf = "Unexpected RRQ recieved";
            netbuf_ref(send_buf, errbuf, strlen(errbuf));
            exit(1);
          }

          imgfd = open(recv_data+2, O_RDONLY);
          if(imgfd == -1){
            
          }

        case 4:
          // ACK 
          // Check if the ACK is appropriate
          // Figure out the next block number
          // Send the next block
          if(block == 0){
            error("Unexpected ACK from client : quitting\n");
            errbuf = "Unexpected ACK recieved";
            netbuf_ref(send_buf, errbuf, strlen(errbuf));
            netconn_send(client, send_buf);
            exit(1);
          }

          nbytes = read(imgfd, buf, 512);
          netbuf_ref(send_buf, buf, nbytes);
          netconn_send(client, send_buf);

        case 5:
          // Error
          error((int*)recv_data+2,recv_data+4);
          exit(1);
          // Handle Error code
          // Direct Error message to stderr
          // Terminate
        case 2:
          // WRQ
          error("Recieved write request from client : quitting\n");
          errbuf = "Write request rejected";
          netbuf_ref(send_buf,errbuf,strlen(errbuf));
          netconn_send(client, send_buf);
          exit(1);
          // Error that WRQ disabled
          // Terminate
        case 3:
          // Datablock 
          error("Recieved unexpected data block : quitting\n");
          errbuf = "Unexpected data block recieved";
          netbuf_ref(send_buf,errbuf,strlen(errbuf));
          netconn_send(client, send_buf);
          exit(1);

          // Error that Datablock unexpected
          // Terminate
      }
    }

    netconn_delete(client);
    netconn_delete(serv);
    break;
  }

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
