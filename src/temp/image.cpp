using namespace std;

#include <string>
#include <pcap.h>
#include "ui.hpp"
#include "image.hpp"
#include "routertype.hpp"

class UI_Step;

ImageStep::ImageStep(Step *step)
{
  backStep = dynamic_cast<UI_Step*>(step);
  nextStep = NULL;
}

UI_Step* ImageStep::next() {
  if(nextStep == NULL)
    nextStep = new RouterStep((Step *)this);

  return nextStep;
}


UI_Step* ImageStep::back() {
  return backStep;
}

void ImageStep::init()
{
  std::string inputMessage;

  set_name("Firmware Image");
  set_desc("Please choose the firmware image file that you want to use for flashing");

  setPrompt("Path to the image file :");  
}

void ImageStep::process()
{
  cout << getInput();
}
