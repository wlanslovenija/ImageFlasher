//using namespace imgfl; 
using namespace std;
#include "ui.hpp"
#include <list>


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

void UI::proceed_to(Step *step)
{
  this->cur_step = step;

  cout << endl << "*******************************************" << endl << endl;

  cout << "Step : " << step->get_name() << endl << endl;

  cout << step->get_desc();
}

int main()
{
  UI x;
  list<string> names;
  names.push_back("linux");
  names.push_back("winxp");
  names.push_back("BSD");
  names.push_back("solaris");
  x.init_selection(names);
  cout << x.get_selection(names);

  x.init_input("What is my name? ");
  x.get_input("What is my name? ");
}
