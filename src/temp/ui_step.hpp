using namespace std;
#ifndef UI_STEP_HPP
#define UI_STEP_HPP

#include "ui.hpp"
#include "step.hpp"

class UIStep : public Step{
  private:
    virtual void display(UI *ui) = 0;
    friend void UI::run();

  public:
    void initStep();
};
#endif /* UI_STEP_HPP */
