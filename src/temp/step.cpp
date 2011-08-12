#include "step.hpp"

using namespace std;

std::string Step::get_name(){
  return stepName;
}

void Step::set_name(std::string name){
  stepName = name;
}

std::string Step::get_desc(){
  return stepDesc;
}

void Step::set_desc(std::string desc){
  stepDesc = desc;
}

