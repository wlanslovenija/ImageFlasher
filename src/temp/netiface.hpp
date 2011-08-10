using namespace std;

#ifndef IMGFLSHR_NETIFACE_HPP
#define IMGFLSHR_NETIFACE_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include <list>
#include <string>

class NetIface : public Step ,public UI_Selection {
  protected:
    Step *nextStep;
    Step *backStep;
  
  public:
    NetIface(Step *step);
    
    Step *next();
    Step *back();

    void init();
    void process();
};

#endif /* IMGFLSHR_WELCOME_HPP */
