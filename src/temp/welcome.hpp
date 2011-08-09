using namespace std;

#ifndef IMGFLSHR_WELCOME_H
#define IMGFLSHR_WELCOME_H

#include "step.hpp"


class Welcome : public Step {
  protected:
    Step *nextStep;
    Step *backStep;
  
  public:
    
    Step *next();
    Step *back();

    void init();
    void display(UI *ui);
    void process();
};

#endif /* IMGFLSHR_WELCOME_H */
