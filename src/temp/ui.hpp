#ifndef IMGFLSHR_UI_H
#define IMGFLSHR_UI_H

#include <list>
#include <string>
#include <iostream>
#include "step.hpp"
class UIStep;

class UI {

  private:
  Step *currentStep;
  UIStep *action;

  void init_step();
  void proceed();
  
  public:
  void run();

  void init_selection(std::list<std::string> items);
  std::string get_selection(std::list<std::string> items);

  void init_input(std::string msg);
  std::string get_input(std::string item);

  void set_action(Step *act);


};

#endif /* IMGFLSHR_UI_H */
