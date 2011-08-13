using namespace std;

#ifndef GUI_ROUTER_TYPE_HPP
#define GUI_ROUTER_TYPE_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"
#include <list>
#include <string>

class RouterStep : public UI_Selection {
  protected:
    UI_Step *nextStep;
    UI_Step *backStep;
  
  public:
    RouterStep(Step *step);
    
    UI_Step *next();
    UI_Step *back();

    void init();
    void process();
};

#endif /* GUI_ROUTER_TYPE_HPP */
