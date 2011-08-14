//using namespace imgfl; 
using namespace std;

#include "ui.hpp"
#include "welcome.hpp"
#include <list>
#include <stdlib.h>
#include "ui_step.hpp"

void UI::run()
{
    action = step_manager.getStep("welcome","");
    while(action != NULL){

        current_step = action;

        UIStep * uistep = dynamic_cast<UIStep *> (current_step); 
        uistep->initStep();
        uistep->display(this);
        
        current_step->process();

        proceed();
    }
}

void UI::set_action(Step *step)
{
    action = static_cast<UIStep*> (step);
}

void UI::proceed()
{

  std::string inp, prev_id, next_id;
  cout << endl;
  prev_id = step_manager.getPrev(current_step->getID());
  next_id = current_step->getNext();


  while(1){
    if(current_step->getNext() == "")
      cout << "Please enter 'f' to finish or b for back :";
    else if(next_id == "")
      cout << "Please enter 'n' for next or 'q' to quit:";
    else
      cout << "Please enter 'b' for back or 'n' for next :";

    cin  >> inp;

    if(inp == "b" || (prev_id == "" && inp == "q")){
      action = step_manager.getStep(prev_id, current_step->getID());
      break;

    }else if(inp == "n" || (prev_id == "" && inp == "f")){
      action = step_manager.getStep(next_id, current_step->getID());
      break;

    }else{
      continue;
    }
  }
}

int main()
{
  UI *ui = new UI;

  ui->run();
}
