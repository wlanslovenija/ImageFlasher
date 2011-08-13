//using namespace imgfl; 
using namespace std;

#include "ui.hpp"
#include "welcome.hpp"
#include <list>
#include <stdlib.h>
#include "ui_step.hpp"

void UI::run()
{
    Step *welcome = new Welcome;
    
    action = dynamic_cast<UIStep *>(welcome);
    while(action != NULL){

        this->currentStep = action;

        UIStep * uistep = dynamic_cast<UIStep *> (currentStep); 
        uistep->initStep();
        uistep->display(this);
        
        currentStep->process();

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
        if(currentStep->next() == NULL)
            cout << "Please enter 'f' to finish or b for back :";
        else if(currentStep->back() == NULL)
            cout << "Please enter 'n' for next or 'q' to quit:";
        else
        cout << "Please enter 'b' for back or 'n' for next :";

        cin  >> inp;

        if(inp == "b" || (currentStep->back() == NULL && inp == "q")){
            action = currentStep->back();
            break;
        }else if(inp == "n" || (currentStep->next() == NULL && inp == "f")){
            action = currentStep->next();
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
