using namespace std;
#include "ui.hpp"
#include "routertype.hpp"
#include "step.hpp"
#include "ui_selection.hpp"
#include <list>
#include <string>

RouterStep::RouterStep()
{
  step_id = "router";
}

std::string RouterStep::getNext() {
  return next_step;  
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
