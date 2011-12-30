/*
 * Usage: ./telnet <remote_ip> <remote_port>
 */ 

#include "lwip/api.h"
#define STDIN 0
#define STDOUT 1

extern char *prefif;

extern int local_ip[], local_gw[], local_nm[];

static struct netconn *conn;

static void netread(void *arg)
{
  int nbytes;
  char *buf;
  conn = netconn_new(NETCONN_TCP);
  struct netbuf *recvbuf;

  char **argv = arg;

  struct ip_addr remote;
  inet_aton(argv[1], &(remote.addr));

  netconn_connect(conn, (struct ip_addr_t *)&remote, atoi(argv[2]));

  while(1){
    err_t e = netconn_recv(conn, &recvbuf);
    netbuf_data(recvbuf, (void**)&buf, (u16_t*)&nbytes); 
    write(STDOUT, buf, nbytes);
    netbuf_free(recvbuf);
    netbuf_delete(recvbuf);
  }
}

int main(int argc, char **argv)
{
  if(argc != 3){
    printf("Usage: ./telnet <remote-ip> <remote-port>\n");
    exit(0);
  }
  char buf[512];
  prefif = "vboxnet0";

  local_ip[0]=192;
  local_ip[1]=168;
  local_ip[2]=56;
  local_ip[3]=11;


  local_gw[0]=192;
  local_gw[1]=168;
  local_gw[2]=56;
  local_gw[3]=11;

  local_nm[0]=255;
  local_nm[1]=255;
  local_nm[2]=255;
  local_nm[3]=0;

  my_init();

  sys_thread_new("netread", netread, argv, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

  int n;
  sleep(3);
  do{ 
    n = read(STDIN, buf, sizeof(buf));
    netconn_write(conn, buf, n, 0);

  }while(1);

}
