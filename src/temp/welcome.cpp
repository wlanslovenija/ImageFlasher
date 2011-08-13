
using namespace std;
#include "ui.hpp"
#include "welcome.hpp"
#include "netiface.hpp"

Welcome::Welcome(){
  next_step = "netif";
  prev_step = "";
}

std::string Welcome::getNext() {
    return next_step;
}

std::string Welcome::getPrev() {
  return prev_step;
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

