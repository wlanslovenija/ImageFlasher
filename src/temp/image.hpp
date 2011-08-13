using namespace std;

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include "ui_step.hpp"
#include "ui_input.hpp"
#include "step.hpp"
#include <string>

class ImageStep : public UIInput {

  protected:
  public:
    ImageStep();

    std::string getNext();
    std::string getPrev();

    void init();
    void process();

};
#endif /* GUI_IMAGE_HPP */
