using namespace std;
#ifndef UI_SELECTION_HPP
#define UI_SELECTION_HPP

#include "ui_step.hpp"
#include "ui.hpp"

class UI_Selection : public UI_Step{

  private:
    list<std::string> selectList;
    std::string selection;
    void display(UI *ui);
   
  protected:
    void setList(list<std::string>);
    std::string getSelection();
  
};

#endif /* UI_SELECTION_HPP */
