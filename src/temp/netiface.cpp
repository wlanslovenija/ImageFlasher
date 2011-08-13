
using namespace std;
#include "ui.hpp"
#include "image.hpp"
#include "netiface.hpp"
#include <list>
#include <pcap.h>
#include "step.hpp"
#include "ui_selection.hpp"


NetIface::NetIface(Step *step)
{
  backStep = dynamic_cast<UI_Step*>(step);
}

UI_Step* NetIface::next() {
  if(nextStep == NULL){
    nextStep = new ImageStep((Step *)this);
  }

  return nextStep;
  //Change this to image selection
}

UI_Step* NetIface::back() 
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
    allifs = allifs->next;
  }

  setList(ifaces);

}

void NetIface::process() 
{
  cout << getSelection();
}

