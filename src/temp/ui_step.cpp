using namespace std;
#include <iostream>
#include "ui_step.hpp"
#include "step.hpp"

void UI_Step::initStep()
{
  Step *step = this;

  step->init();

  cout << endl << "*******************************************" << endl << endl;

  cout << "Step : " << step->get_name() << endl << endl;

  cout << step->get_desc(); 
}

