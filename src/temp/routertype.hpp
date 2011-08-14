using namespace std;

#ifndef GUI_ROUTER_TYPE_HPP
#define GUI_ROUTER_TYPE_HPP

#include "step.hpp"
#include "ui_selection.hpp"
#include "ui_step.hpp"
#include <list>
#include <string>

class RouterStep : public UISelection {
  protected:
  
  public:
    RouterStep();
    
    std::string getNext();

    void init();
    void process();
};

#endif /* GUI_ROUTER_TYPE_HPP */
