
using namespace std;
#include "ui.hpp"
#include "netiface.hpp"
#include "image.hpp"
#include <list>
#include <pcap.h>
#include "step.hpp"
#include "ui_selection.hpp"


NetifStep::NetifStep(Step *step)
{
  backStep = dynamic_cast<UIStep*>(step);
}

UIStep* NetifStep::next() {
  if(nextStep == NULL){
    nextStep = new ImageStep((Step *)this);
  }

  return nextStep;
  //Change this to image selection
}

UIStep* NetifStep::back() 
{
  return backStep;
}

void NetifStep::init()
{
  list<string> ifaces;
  //Step information
  this->setName("Network Interface");
  this->setDesc("Please select the network interface connected to your router");

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

