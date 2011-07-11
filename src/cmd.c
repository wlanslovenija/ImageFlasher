
#include "api.h"


int main(int argc, char **argv)
{
  if(argc != 3){
    usage();
    exit(1);
  }

  flash(argv[1],argv[2]);

}


void flash(char *target_addr, char* img)
{

  tftp_serv(target_addr, img);

}


void tftp_serv(char *target_addr, char* img)
{

  struct netconn *serv, *client;
  struct ip_addr *peer_addr;
  u16_t peer_port, *opcode;
  struct netbuf *rcv_buf, *send_buf;
  char *rcv_data, *send_data;
  u32_t len;

  serv = netconn_new(NETCONN_UDP); 

  netconn_bind(serv, NULL, IPPORT_TFTP);

  netconn_listen(serv);

  while(1){
    client = netconn_accept(serv);
    
    netconn_peer(client, &peer_addr, &peer_port);

    if(*peer_addr != srt_to_addr(target_addr))
      continue;
    
    while(rcv_buf = netconn_rcv(client)){

      netbuf_data(rcv_buf, &rcv_data, &len);

      opcode = rcv_data;

      switch(*opcode){

        case 1:
          // TFTP RRQ
          // Check if routers make requests
          // If they do match with the char *img
          //  If they don't match send error
          // If they do match 
          //  Open the image file 
          // Send first block
        case 4:
          // ACK 
          // Figure out the next block number
          // Send the next block
        case 5:
          // Error
          error((int*)rcv_data+2,rcv_data+4);
          exit(1);
          // Handle Error code
          // Direct Error message to stderr
          // Terminate
        case 2:
          // WRQ
          error("Recieved write request from client : quitting\n");
          char *wrq_err = "Write request rejected";
          netbuf_ref(send_buf,wrq_err,strlen(wrq_err));
          netconn_send(client, send_buf);
          exit(1);
          // Error that WRQ disabled
          // Terminate
        case 3:
          // Datablock 
          error("Recieved unexpected data block : quitting\n");
          char *data_err = "Unexpected data block recieved";
          netbuf_ref(send_buf,data_err,strlen(data_err));
          netconn_send(client, send_buf);
          exit(1);

          // Error that Datablock unexpected
          // Terminate
      }
    }

    break;
  }

}

