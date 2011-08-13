using namespace std;
#include "ui.hpp"
#include "routertype.hpp"
#include "step.hpp"
#include "ui_selection.hpp"
#include "image.hpp"
#include <list>
#include <string>

RouterStep::RouterStep(Step *step)
{
  backStep = dynamic_cast<UIStep*>(step);
}

UIStep* RouterStep::next() {
  return nextStep;  
}
UIStep* RouterStep::back()
{
  return backStep;
}

void RouterStep::init(){
  list<std::string> types;

  //Step information
  this->setName("Router Type");
  this->setDesc("Please select the type of your router");

  //Router types;
  types.push_back("LinkSys");

  setList(types);
}

void RouterStep::process()
{
  nextStep = NULL;
  cout << getSelection();
}
