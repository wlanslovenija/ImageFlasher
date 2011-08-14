using namespace std;

#ifndef IMGFLSHR_WELCOME_HPP
#define IMGFLSHR_WELCOME_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"


class Welcome : public UIStep {
  protected:
  
  public:
    Welcome();
    
    std::string getNext();

    void init();
    void display(UI *ui);
    void process();
};

#endif /* IMGFLSHR_WELCOME_HPP */
