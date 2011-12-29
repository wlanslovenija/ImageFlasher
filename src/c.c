
#include "lwip/api.h"
extern char *prefif;
extern int local_ip[], local_gw[], local_nm[];

static void testclient(void* arg)
{
       char **argv = arg;

       struct netconn *client;
       struct ip_addr srv_addr;
       struct netbuf *recvbuf;

       int bufsize;
       char buf[512] = "This is a test message\n";
       char buf2[512] = "This is the second test msg\n";
       inet_aton(argv[1], (struct in_addr*)&srv_addr);
       char *buf3;

       client = netconn_new(NETCONN_TCP);
       netconn_connect(client, (struct ip_addr_t *)&srv_addr , atoi(argv[2]));

       printf("Connected\n");
       while(1){

///*               Reading client
              netconn_recv(client, &recvbuf);
              netbuf_data(recvbuf, &buf3, &bufsize); 
              write(1, buf3, bufsize);
//*/
              
/*
              scanf("%s", buf);
              netconn_write(client, buf, strlen(buf), 0);
*/

       }
//*/

      netconn_write(client, buf, strlen(buf), 0); 
      sleep(3);
       netconn_write(client, buf2, strlen(buf2), 0);

       netconn_close(client);
       netconn_delete(client);
}

int main(int argc, char **argv)
{
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


       prefif = "vboxnet0";
       my_init();
       sys_thread_new("test_client", testclient, argv, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

       // #edit: Replace the sleep call with thread_join() call
       sleep(10000);
}
