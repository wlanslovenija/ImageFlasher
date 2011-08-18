#ifndef IMGFLSHR_UI_H
#define IMGFLSHR_UI_H

#include <list>
#include <string>
#include <iostream>
#include "step.hpp"
class UIStep;

#include "step_manager.hpp"
class UI {

  private:
  StepManager step_manager;
  Step *current_step;
  UIStep *action;

  void init_step();
  void proceed();

  void set_action(Step *act);

  public:
  void run();

  
};

#endif /* IMGFLSHR_UI_H */
