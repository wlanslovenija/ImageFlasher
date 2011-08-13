using namespace std;
#include <iostream>
#include "ui_selection.hpp"
#include "ui.hpp"

void UISelection::display(UI *ui){

  int i = 1;
  cout << endl;
  
  for(list<string>::iterator itr = selectList.begin();
        itr != selectList.end(); itr++ ){
    
    cout << i << ". " << *itr << endl;
    i++;
  }
  cout << endl << "Enter your choice [1 - " << i-1 <<"]: ";

  cin >> i;
  cin.ignore();

  while(i > selectList.size() || i < 1){
    cout << endl << "Please enter a valid choice :" ; 
    cin >> i;
    cin.ignore();
    cin.clear();
  }
  

  list<string>::iterator itr = selectList.begin();

  for(;i != 1; i--) itr++;

  selection =  *itr;
}

void UISelection::setList(list<std::string> List){
  list<std::string>::iterator itr = List.begin();
  selectList.clear();

  while(itr != List.end()){
    selectList.push_back(*itr);
    itr++;
  }
}

std::string UISelection::getSelection(){
  return selection;
}
