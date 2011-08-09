//using namespace imgfl; 
using namespace std;

#include "ui.hpp"
#include "welcome.hpp"
#include <list>
#include <stdlib.h>

void UI::run()
{
    Step *welcome = new Welcome;
    
    action = welcome;
    while(action != NULL){
        init_step();
        cur_step->display(this);
        cur_step->process();
        proceed();

    }
}

void UI::init_input(string msg)
{
  cout << endl;
  cout << msg;
}

string UI::get_input(string msg)
{
  string inp;
  cout << endl;
  cin  >> inp;
  cout << endl;

  return inp;
} 

void UI::init_selection(list<string> items){
  int i = 1;
  
  for(list<string>::iterator itr = items.begin();
        itr != items.end(); itr++ ){
    
    cout << i << ". " << *itr << endl;
    i++;

  }

  cout << endl << "Enter your choice [1 - " << i-1 <<"]: ";
}

string UI::get_selection(list<string> items)
{
  int i;

  cin >> i;

  while(i > items.size() || i < 1){
    cout << endl << "Please enter a valid choice :";
    cin >> i;
  }

  list<string>::iterator itr = items.begin();

  for(;i != 1; i--) itr++;

  return *itr;
}

void UI::set_action(Step *step)
{
    action = step;
}

void UI::init_step()
{
  this->cur_step = action;

  this->cur_step->init();

  cout << endl << "*******************************************" << endl << endl;

  cout << "Step : " << this->cur_step->get_name() << endl << endl;

  cout << this->cur_step->get_desc();
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
