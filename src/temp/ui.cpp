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
    
    action = welcome;
    while(action != NULL){

        this->cur_step = action;

        UI_Step * uistep = (void *)cur_step;
        uistep->initStep();
        uistep->display(this);
        
        cur_step->process();

        proceed();
    }
}

string UI::get_input(string msg)
{
  string inp;
  cout << endl;
  cin  >> inp;
  cout << endl;

  return inp;
} 

void UI::set_action(Step *step)
{
    action = step;
}

void UI::proceed()
{
    std::string inp;
    cout << endl;
    while(1){
        if(cur_step->next() == NULL)
            cout << "Please enter 'f' to finish or b for back :";
        else if(cur_step->back() == NULL)
            cout << "Please enter 'n' for next or 'q' to quit:";
        else
        cout << "Please enter 'b' for back or 'n' for next :";

        cin  >> inp;

        if(inp == "b" || (cur_step->back() == NULL && inp == "q")){
            action = cur_step->back();
            break;
        }else if(inp == "n" || (cur_step->next() == NULL && inp == "f")){
            action = cur_step->next();
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
