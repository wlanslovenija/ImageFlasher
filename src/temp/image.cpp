using namespace std;

#include <string>
#include <pcap.h>
#include "ui.hpp"
#include "image.hpp"
#include "routertype.hpp"

class UIStep;

ImageStep::ImageStep()
{
  step_id = "image";
  next_step = "router";
}

std::string ImageStep::getNext() {
  return next_step;
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
