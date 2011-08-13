#include "step.hpp"

using namespace std;

std::string Step::get_name(){
  return stepName;
}

void Step::setName(std::string name){
  stepName = name;
}

std::string Step::get_desc(){
  return stepDesc;
}

void Step::setDesc(std::string desc){
  stepDesc = desc;
}

