#ifndef IMGFLSHR_STEP_MANAGER_HPP
#define IMGFLSHR_STEP_MANAGER_HPP

using namespace std;

#include <map>
#include <string>
class UIStep;

typedef map<std::string, UIStep*> StepMap;
typedef pair<std::string, UIStep*> StepPair;
typedef list<std::string> StepOrder;

class StepManager {
  private:
    StepMap step_map;
    StepOrder step_order;

  public:
    StepManager();
    UIStep *getStep(std::string step_name,std::string cur_step_id);
    std::string getPrev(std::string cur_step_id);

};


#endif /* IMGFLSHR_STEP_MANAGER_HPP */
