using namespace std;

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include "ui_step.hpp"
#include "ui_input.hpp"
#include "step.hpp"
#include <string>

class ImageStep : public UI_Input {

  protected:
    UI_Step *nextStep;
    UI_Step *backStep;

  public:
    ImageStep(Step *step);

    UI_Step *next();
    UI_Step *back();

    void init();
    void process();

};
#endif /* GUI_IMAGE_HPP */
