using namespace std;
#ifndef UI_STEP_HPP
#define UI_STEP_HPP

#include "ui.hpp"
#include "step.hpp"

/* 
 * Class UIStep 
 *
 * An abstraction over steps with different UI layouts
 * 
 */
class UIStep : public Step{
  private:

    /* Name : display()
     * Renders the Step on the UI
     * Should be implemented by all the layout subclasses
     * Params:
     *    - ui, reference to the UI object where the layout has to be rendered
     */
    virtual void display(UI *ui) = 0;

    /*
     * UI::run() requires access to display() as it renders the step on the UI
     */
    friend void UI::run();

  public:
    void initStep();
};
#endif /* UI_STEP_HPP */
