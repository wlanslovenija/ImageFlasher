using namespace std;

#ifndef IMGFLSHR_NETIFACE_HPP
#define IMGFLSHR_NETIFACE_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"
#include <list>
#include <string>

class NetIface : public UI_Selection {
  protected:
    UI_Step *nextStep;
    UI_Step *backStep;
  
  public:
    NetIface(Step *step);
    
    UI_Step *next();
    UI_Step *back();

    void init();
    void process();
};

#endif /* IMGFLSHR_WELCOME_HPP */
