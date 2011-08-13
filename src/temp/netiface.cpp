
using namespace std;
#include <list>
#include <pcap.h>
#include "ui.hpp"
#include "netiface.hpp"
#include "image.hpp"
#include "step.hpp"
#include "ui_selection.hpp"


NetifStep::NetifStep()
{
  prev_step = "welcome";
  next_step = "image";
}

std::string NetifStep::getNext() {
  return next_step;
}

std::string NetifStep::getPrev() 
{
  return prev_step;
}

void NetifStep::init()
{
  list<string> ifaces;
  
  //Step information
  setName("Network Interface");
  setDesc("Please select the network interface connected to your router");

  //Initializing the list of choices for selection
  char pcerrbuf[PCAP_ERRBUF_SIZE];
  pcap_if_t *allIfs;
  if(pcap_findalldevs(&allIfs, pcerrbuf) == -1)
    cout << pcerrbuf; 
  while(allIfs != NULL){
    ifaces.push_back(allIfs->name);
    allIfs = allIfs->next;
  }

  setList(ifaces);

}

void NetifStep::process() 
{
  cout << getSelection();
}

