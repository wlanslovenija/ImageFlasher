using namespace std;

#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "ui_step.hpp"
#include "step.hpp"
#include "ui.hpp"
#include <string>

class UIInput : public UIStep {
  private:
    std::string input;
    std::string prompt;
    void display(UI *ui);

  public:
    void setPrompt(std::string str);
    std::string getInput();
};




#endif /* UI_INPUT_HPP */
