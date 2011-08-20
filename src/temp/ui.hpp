#ifndef IMGFLSHR_UI_H
#define IMGFLSHR_UI_H

#include <list>
#include <string>
#include <iostream>
#include "step.hpp"
#include "step_manager.hpp"

/* Forward Declarations */
class UIStep;

/*
 * Class UI
 *    - Abstracts the User Interface to the steps
 *    - Runs the steps in the right order
 */
class UI {

  private:
  StepManager step_manager;
  Step *current_step;

  /*
   * The action to be taken from the current step.
   * Contains reference to the previous step or next step depending upon the user
   */
  UIStep *action;
  void set_action(Step *act);


  /* proceed()
   * Decides where to proceed, previous step or next step, depending upon the interaction with the user 
   * Uses set_action() to set the action.
   */
  void proceed();


  public:

  /* run()
   * Runs the UI
   * Called from the main() in the beginning.
   * 
   */
  void run();

  
};

#endif /* IMGFLSHR_UI_H */
