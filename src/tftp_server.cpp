using namespace std;
extern "C" {
  #include "lwip/api.h"
}

#include "tftp_server.hpp"
#include <fstream>
#include <iostream>
static void error(char *errmsg)
{
  cerr << errmsg;
}


void TftpServer::start(){
  
  struct netconn *serv, *client;
  struct ip_addr peer_addr, target_addr;

  u16_t peer_port, *opcode, len;
  struct netbuf *recv_buf, *send_buf;
  char *recv_data, *send_data;
  char *errbuf;
  char buf[512];
  u32_t block, imgfd, nbytes;
  
  ifstream img_strm;

  serv = netconn_new(NETCONN_UDP); 

  netconn_bind(serv, IP_ADDR_ANY, TFTP_PORT);

  netconn_listen(serv);

  while(1){
    errno = netconn_accept(serv, &client);
    
    netconn_peer(client, &peer_addr, &peer_port);

    if(memcmp((const void *)&peer_addr, (const void *)&target_addr, sizeof(struct ip_addr)) != 0){
      netconn_delete(client);
      continue;
    }
    
    while(1){
      netconn_recv(client, &recv_buf);
        if(recv_buf == NULL)
          break;
      netbuf_data(recv_buf, (void **)&recv_data, &len);
      netbuf_delete(recv_buf);

      opcode = (u16_t *)recv_data;

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
            error((char *)"Unexpected RRQ from client : quitting\n");
            errbuf = (char *)"Unexpected RRQ recieved";
            netbuf_ref(send_buf, errbuf, strlen(errbuf));
            exit(1);
          }

          img_strm.open(recv_data+2);

        case 4:
          // ACK 
          // Check if the ACK is appropriate
          // Figure out the next block number
          // Send the next block
          if(block == 0){
            error((char *)"Unexpected ACK from client : quitting\n");
            errbuf = (char *)"Unexpected ACK recieved";
            netbuf_ref(send_buf, errbuf, strlen(errbuf));
            netconn_send(client, send_buf);
            exit(1);
          }

          netbuf_ref(send_buf, buf, nbytes);
          netconn_send(client, send_buf);

          img_strm.read(buf, 512);
          nbytes = img_strm.gcount();

        case 5:
          // Error
          error(recv_data+4);
          exit(1);
          // Handle Error code
          // Direct Error message to stderr
          // Terminate
        case 2:
          // WRQ
          error((char *)"Recieved write request from client : quitting\n");
          errbuf = (char *)"Write request rejected";
          netbuf_ref(send_buf,errbuf,strlen(errbuf));
          netconn_send(client, send_buf);
          exit(1);
          // Error that WRQ disabled
          // Terminate
        case 3:
          // Datablock 
          error((char *)"Recieved unexpected data block : quitting\n");
          errbuf = (char *)"Unexpected data block recieved";
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

int main(int argc, char **argv)
{
       TftpServer ts;
       ts.start();
       return 0;
}
