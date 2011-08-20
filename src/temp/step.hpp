using namespace std;
#ifndef IMGFLSHR_STEP_HPP
#define IMGFLSHR_STEP_HPP

#include <string>

/* Forward declarations */
class UI;
class UIStep;


/* Class Step
 * This class represents a basic step in the flashing process
 * It defines the basic functionality of a step in the flashing process
 */

class Step {
  protected:
    
    /* 
     * Reference to the UI object that uses the step object
     */
    UI *ui;

    std::string next_step;
    std::string step_id;

    std::string step_name;
    std::string step_desc;

    void setName(std::string name);

    void setDesc(std::string name);

  public:

    std::string getName();
    std::string getDesc();
    std::string getID();

    /* 
     * Returns a string id of the next step.
     *
     * Has to be implemented by each any subclass of Step.
     *
     */
    virtual std::string getNext()   = 0;

    /*
     * Initializes the basic elements of the step like 
     *  - step_name
     *  - step_desc
     *
     * Should be called before displaying the step in the UI
     */
    virtual void init()    = 0;

    /*
     * Does the main processing of the step
     * Should be called before proceeding to the next step
     */ 
    virtual void process() = 0;

};

#endif /* IMGFLSHR_STEP_HPP */
