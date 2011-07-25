

#include "lwip/api.h"

 
static void testserver(void* arg)
{
  struct netconn *server, *client;
  struct ip_addr srv_addr;
  struct netbuf sendbuf;
  char *check = (void *)&(srv_addr.addr);
  check[0] = 10;
  check[1] = 0;
  check[2] = 0;
  check[3] = 1;

  server = netconn_new(NETCONN_TCP);

  netconn_bind(server, NULL, 44); 

  netconn_listen(server);

  netconn_accept(server, &client);

  if(client != NULL) printf("Connected\n");
  printf("Check 1\n");

  char *senddata = "Just print this plzzzzz!!";

  
  netconn_write(client, senddata, strlen(senddata), 0);

  netconn_close(client);
  netconn_delete(client);

  netconn_close(server);
  netconn_delete(server);
}
int main(int argc, char **argv)
{
  my_init();
  sys_thread_new("test_server", testserver, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
  sleep(10000);
}
 
