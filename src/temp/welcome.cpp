
using namespace std;
#include "ui.hpp"
#include "welcome.hpp"
#include "netiface.hpp"

UI_Step* Welcome::next() {
    if(nextStep == NULL)
        nextStep = new NetIface((Step *)this);
    return nextStep;
    //Change this to network interface selection
}

UI_Step* Welcome::back() {
  return backStep;
}

void Welcome::init()
{
  this->set_name("Welcome");
  this->set_desc("Please follow the instructions in every step to successfully flash your router");
}

void Welcome::display(UI *uif)
{
}

void Welcome::process() {
    
}

