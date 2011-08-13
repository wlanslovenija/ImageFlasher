//using namespace imgfl; 
using namespace std;

#include "ui.hpp"
#include "welcome.hpp"
#include <list>
#include <stdlib.h>
#include "ui_step.hpp"

void UI::run()
{
    action = step_manager.getStep("welcome");
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
    std::string inp;
    cout << endl;
    while(1){
        if(current_step->getNext() == "")
            cout << "Please enter 'f' to finish or b for back :";
        else if(current_step->getPrev() == "")
            cout << "Please enter 'n' for next or 'q' to quit:";
        else
        cout << "Please enter 'b' for back or 'n' for next :";

        cin  >> inp;

        if(inp == "b" || (current_step->getPrev() == "" && inp == "q")){
            action = step_manager.getStep(current_step->getPrev());
            break;
        }else if(inp == "n" || (current_step->getNext() == "" && inp == "f")){
            action = step_manager.getStep(current_step->getNext());
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
