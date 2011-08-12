using namespace std;

#ifndef IMGFLSHR_WELCOME_H
#define IMGFLSHR_WELCOME_H

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"


class Welcome : public UI_Step {
  protected:
    UI_Step *nextStep;
    UI_Step *backStep;
  
  public:
    
    UI_Step *next();
    UI_Step *back();

    void init();
    void display(UI *ui);
    void process();
};

#endif /* IMGFLSHR_WELCOME_H */
