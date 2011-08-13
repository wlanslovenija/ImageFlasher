#include "step.hpp"

using namespace std;

std::string Step::get_name(){
  return step_name;
}

void Step::setName(std::string name){
  step_name = name;
}

std::string Step::get_desc(){
  return step_desc;
}

void Step::setDesc(std::string desc){
  step_desc = desc;
}

