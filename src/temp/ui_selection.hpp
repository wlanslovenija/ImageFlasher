using namespace std;
#ifndef UI_SELECTION_HPP
#define UI_SELECTION_HPP

#include "ui_step.hpp"
#include "ui.hpp"

class UISelection : public UIStep{

  private:
    list<std::string> selectList;
    std::string selection;
    void display(UI *ui);
   
  protected:
    void setList(list<std::string>);
    std::string getSelection();
  
};

#endif /* UI_SELECTION_HPP */
