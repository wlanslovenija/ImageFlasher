using namespace std;
#include <map>
#include <string>
#include "welcome.hpp"
#include "netiface.hpp"
#include "image.hpp"
#include "routertype.hpp"
class UIStep;

StepManager::StepManager() {}

UIStep* StepManager::getStep(std::string step_name, std::string curr_step){
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

  StepOrder::iterator order_itr = step_order.begin();

  while(order_itr != step_order.end()){
    if(*order_itr == curr_step){
      step_order.erase(step_order.begin(), order_itr); 
      step_order.push_front(step_name);
    }
    
    order_itr++;
  }

  step_map.insert(StepPair(step_name, uistep));

  return uistep;

}

std::string StepManager::getPrev(std::string curr_step){
  UIStep *uistep;

  StepOrder::iterator order_itr = step_order.begin();

  while(order_itr != step_order.end()){
    if(*order_itr == curr_step){
      order_itr++;
      return *order_itr;
    }
    order_itr++;
  }
  return "";
}

