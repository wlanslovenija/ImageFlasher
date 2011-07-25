
#include "lwip/api.h"

 
static void testclient(void* arg)
{
  struct netconn *client;
  struct ip_addr srv_addr;
  struct netbuf *recvbuf;
  inet_aton("192.168.56.101", (struct in_addr*)&srv_addr);

  char buf[512];

  client = netconn_new(NETCONN_TCP);

  printf("Now!\n");
  printf("Error : %d\n",netconn_connect(client, NULL, htons(1234))); 


  sleep(1000);
  netconn_recv(client, &recvbuf);

  netbuf_data(recvbuf, &buf, 512); 

  printf("%s\n", buf);

  netconn_close(client);
  netconn_delete(client);
}
int main(int argc, char **argv)
{
  my_init();
  sys_thread_new("test_client", testclient, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
  sleep(10000);
}
 
