
using namespace std;
#include "ui.hpp"
#include "welcome.hpp"
#include "netiface.hpp"

Welcome::Welcome(){
  step_id = "welcome";
  next_step = "netif";
}

std::string Welcome::getNext() {
    return next_step;
}


void Welcome::init()
{
  setName("Welcome");
  setDesc("Please follow the instructions in every step to successfully flash your router");
}

void Welcome::display(UI *uif)
{
}

void Welcome::process() {
}

