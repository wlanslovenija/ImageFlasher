using namespace std;
#include "ui_input.hpp"
#include <iostream>
#include <string>

void UIInput::display(UI *ui)
{
  
  cout << endl << prompt << endl;
  cin  >> input;
  cout << endl;
}

void UIInput::setPrompt(std::string str)
{
  prompt = str;
}

std::string UIInput::getInput()
{
  return input;
}
