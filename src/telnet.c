/****
#include "lwip/api.h"

static FILE *p=0;
 
static void testclient(void* arg)
{
  struct netconn *client;
  struct ip_addr srv_addr;
  struct netbuf *recvbuf;

  char **argv = arg;

  inet_aton(argv[1], (struct in_addr*)&srv_addr);

  char buf[512];

  client = netconn_new(NETCONN_TCP);

  netconn_connect(client, NULL, atoi(argv[2]));

  netconn_recv(client, &recvbuf);

  netbuf_data(recvbuf, &buf, 512); 


  netconn_close(client);
  netconn_delete(client);
}

static void read_stdin(void *arg){
  
  sleep(1000);
  fdset fds;

  while(1){
    FD_ZERO(&fds);
    FD_SET(stdin, &fds);
    FD_SET(p, &fds);

    select((p>stdin?p+1:stdin+1), &fds, NULL, NULL, NULL);

    if(FD_ISSET(p, &fds)){
      nbytes = read(p, buf, 512);
      write(stdout, buf, nbytes);
    }
    
    
  
  }

}

int main(int argc, char **argv)
{
  my_init();
  sys_thread_new("test_client", testclient, argv, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

  sys_thread_new("read_stdin", read_stdin, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
 


****/


#include "lwip/api.h"

static struct netconn *conn;

static void netread(void *arg)
{
  int nbytes;
  char *buf;
  conn = netconn_new(NETCONN_TCP);

  struct ip_addr remote;
  inet_aton(argv[1], &(local.addr));
 
  netconn_connect(conn, remote, atoi(argv[2]));

  while(1){
    netconn_recv(client, &recvbuf);
    netbuf_data(recvbuf, &buf, &nbytes); 
    write(stdout, buf, nbytes);
  }
}

int main(int argc, char **argv)
{
  my_init();

  sys_thread_new("netread", netread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

  int n;
  do{

    n = read(stdin, buf, sizeof(buf));
    
    netconn_write(conn, buf, n, 0);

  }while(1);

}
