
using namespace std;
#include "ui.hpp"
#include "netiface.hpp"
#include <list>
#include <pcap.h>

NetIface::NetIface(Step *step)
{
  backStep = step;
}

Step* NetIface::next() {
  return NULL;
  //Change this to image selection
}

Step* NetIface::back() 
{
  return backStep;
}

void NetIface::init()
{
  list<string> ifaces;
  //Step information
  this->set_name("Network Interface");
  this->set_desc("Please select the network interface connected to your router");

  //Initializing the list of choices for selection
  char pcerrbuf[PCAP_ERRBUF_SIZE];
  pcap_if_t *allifs;
  if(pcap_findalldevs(&allifs, pcerrbuf) == -1)
    cout << pcerrbuf; 
  while(allifs != NULL){
    ifaces.push_back(allifs->name);
  }

  setList(ifaces);

}

void NetIface::process() 
{
  cout << getSelection();
}

