#ifndef IMGFLSHR_STEP_MANAGER_HPP
#define IMGFLSHR_STEP_MANAGER_HPP

using namespace std;

#include <map>
#include <string>
class UIStep;

typedef map<std::string, UIStep*> StepMap;
typedef pair<std::string, UIStep*> StepPair;

class StepManager {
  private:
    StepMap step_map;

  public:
    StepManager();
    UIStep *getStep(std::string);

};


#endif /* IMGFLSHR_STEP_MANAGER_HPP */
