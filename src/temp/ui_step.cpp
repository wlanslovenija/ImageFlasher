using namespace std;
#include <iostream>
#include "ui_step.hpp"
#include "step.hpp"

void UIStep::initStep()
{

  Step *step = this;

  step->init();

  for(int i =0; i < 100; i++)
    cout << endl;

  cout << "Step : " << step->get_name() << endl << endl;

  cout << step->get_desc(); 
}

