#ifndef IMGFLSHR_STEP_MANAGER_HPP
#define IMGFLSHR_STEP_MANAGER_HPP

using namespace std;

#include <map>
#include <string>
class UIStep;

/*
 * StepMap
 * It is a mapping between the string id of the step and a reference to the step object
 */
typedef map<std::string, UIStep*> StepMap;

/*
 * StepPair
 * A mapping within StepMap
 */
typedef pair<std::string, UIStep*> StepPair;

/*
 * StepOrder
 * Order of the steps 
 */
typedef list<std::string> StepOrder;

/* 
 * Class StepManager
 *  - Creates a step corresponding to a string name 
 *  - Makes sure there are no duplicate steps
 *  - Keeps a record of the sequence of steps being followed
 *
 */
class StepManager {
  private:
    StepMap step_map;
    StepOrder step_order;

  public:
    StepManager();

    /* Name :getStep()
     * Returns a reference to a Step object
     * Params :
     *    step_id, string id of the step to be created 
     *    cur_step_id, id of the current step to keep track of the sequence of steps
     *
     * Creates a new step if a step with step_id doesn't already exist
     * Returns the reference to the previously created step if step_id already exists.
     *
     */
    UIStep *getStep(std::string step_id,std::string cur_step_id);

    /* Name : getPrev()
     * Returns the reference to the previous step and "" if cur_step_id doesn't have a previous step
     * Params :
     *  - cur_step_id, string id of the current step;
     *
     */
    std::string getPrev(std::string cur_step_id);

};


#endif /* IMGFLSHR_STEP_MANAGER_HPP */
