using namespace std;

#ifndef IMGFLSHR_NETIFACE_HPP
#define IMGFLSHR_NETIFACE_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"
#include <list>
#include <string>

class NetifStep : public UISelection {
  protected:
  
  public:
    NetifStep();
    
    std::string getNext();
    std::string getPrev();

    void init();
    void process();
};

#endif /* IMGFLSHR_WELCOME_HPP */
