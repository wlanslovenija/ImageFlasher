using namespace std;
#include <map>
#include <string>
#include "welcome.hpp"
#include "netiface.hpp"
#include "image.hpp"
#include "routertype.hpp"
class UIStep;

StepManager::StepManager() {}

UIStep* StepManager::getStep(std::string step_name){
  UIStep *uistep;  

  StepMap::iterator map_itr = step_map.find(step_name);

  if(!(map_itr == step_map.end()))
    return map_itr->second;

  if(step_name == "welcome"){
    uistep = new Welcome();
  }else if(step_name == "netif"){
    uistep = new NetifStep();
  }else if(step_name == "router"){
    uistep = new RouterStep();
  }else if(step_name == "image"){
    uistep = new ImageStep();
  }else{
    uistep = NULL;
  }

  step_map.insert(StepPair(step_name, uistep));

  return uistep;

}
