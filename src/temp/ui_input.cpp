using namespace std;
#include "ui_input.hpp"
#include <iostream>
#include <string>

void UI_Input::display(UI *ui)
{
  
  cout << endl << prompt << endl;
  cin  >> input;
  cout << endl;
}

void UI_Input::setPrompt(std::string str)
{
  prompt = str;
}

std::string UI_Input::getInput()
{
  return input;
}
