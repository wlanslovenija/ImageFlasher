using namespace std;
#ifndef UI_SELECTION_HPP
#define UI_SELECTION_HPP

#include "ui_step.hpp"
#include "ui.hpp"

/* Class UISelection
 *
 * Abstraction for a layout page which allows to select an option from a list 
 *
 */
class UISelection : public UIStep{

  private:
    list<std::string> selectList;
    std::string selection;

    /* Name : display()
     * Renders the Step on the UI
     * Params:
     *    - ui, reference to the UI object where the layout has to be rendered
     */
    void display(UI *ui);

  protected:

    /* Name : setList()
     * Sets the list of options to be displayed
     * Params:
     *    -options, the list of options as list<std::string>
     */
    void setList(list<std::string> options);

    /* Name : getSelection()
     * Returns the choice selected by the user as std::string
     */
    std::string getSelection();
  
};
#endif /* UI_SELECTION_HPP */
