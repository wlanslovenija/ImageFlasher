#include "step.hpp"

using namespace std;

std::string Step::getName(){
  return step_name;
}

void Step::setName(std::string name){
  step_name = name;
}

std::string Step::getDesc(){
  return step_desc;
}

void Step::setDesc(std::string desc){
  step_desc = desc;
}

std::string Step::getID(){
  return step_id;
}
