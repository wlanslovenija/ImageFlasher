
using namespace std;
#include "ui.hpp"
#include "welcome.hpp"
#include "netiface.hpp"

UIStep* Welcome::next() {
    if(nextStep == NULL)
        nextStep = new NetifStep((Step *)this);
    return nextStep;
    //Change this to network interface selection
}

UIStep* Welcome::back() {
  return backStep;
}

void Welcome::init()
{
  this->setName("Welcome");
  this->setDesc("Please follow the instructions in every step to successfully flash your router");
}

void Welcome::display(UI *uif)
{
}

void Welcome::process() {
    
}

