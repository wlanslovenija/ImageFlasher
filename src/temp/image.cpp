using namespace std;

#include <string>
#include <pcap.h>
#include "ui.hpp"
#include "image.hpp"
#include "routertype.hpp"

class UIStep;

ImageStep::ImageStep(Step *step)
{
  backStep = dynamic_cast<UIStep*>(step);
  nextStep = NULL;
}

UIStep* ImageStep::next() {
  if(nextStep == NULL)
    nextStep = new RouterStep((Step *)this);

  return nextStep;
}


UIStep* ImageStep::back() {
  return backStep;
}

void ImageStep::init()
{
  std::string inputMessage;

  setName("Firmware Image");
  setDesc("Please choose the firmware image file that you want to use for flashing");

  setPrompt("Path to the image file :");  
}

void ImageStep::process()
{
  cout << getInput();
}
