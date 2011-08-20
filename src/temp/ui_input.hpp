using namespace std;

#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "ui_step.hpp"
#include "step.hpp"
#include "ui.hpp"
#include <string>

/* Class UIInput
 *
 * Abstraction for a layout page which reads a text input from the user
 *
 */
class UIInput : public UIStep {
  private:
    std::string input;
    std::string prompt;

    /* Name : display()
     * Renders the Step on the UI
     * Params:
     *    - ui, reference to the UI object where the layout has to be rendered
     */
    void display(UI *ui);

  public:

    /* Name : setPrompt()
     * Sets the prompt message for the input prompt
     * Params:
     *    - str, the prompt message as std::string
     */
    void setPrompt(std::string str);


    /* Name : getInput()
     * Returns the text input of the user 
     */
    std::string getInput();
};

#endif /* UI_INPUT_HPP */
