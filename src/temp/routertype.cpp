using namespace std;
#include "ui.hpp"
#include "routertype.hpp"
#include "step.hpp"
#include "ui_selection.hpp"
#include "image.hpp"
#include <list>
#include <string>

RouterStep::RouterStep()
{
  prev_step = "image";
}

std::string RouterStep::getNext() {
  return next_step;  
}

std::string RouterStep::getPrev()
{
  return prev_step;
}

void RouterStep::init(){
  list<std::string> types;

  //Step information
  setName("Router Type");
  setDesc("Please select the type of your router");

  //Router types;
  types.push_back("LinkSys");

  setList(types);
}

void RouterStep::process()
{
  next_step = "";
  cout << getSelection();
}
