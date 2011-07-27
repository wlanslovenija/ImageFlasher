#include "httpserver-netconn.h"
extern char *prefif;

int main(int argc, char **argv)
{
  prefif = argv[1];
  my_init();
  http_server_netconn_init();

}
