using namespace std;

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include "ui_step.hpp"
#include "ui_input.hpp"
#include "step.hpp"
#include <string>

class ImageStep : public UIInput {

  protected:
    UIStep *nextStep;
    UIStep *backStep;

  public:
    ImageStep(Step *step);

    UIStep *next();
    UIStep *back();

    void init();
    void process();

};
#endif /* GUI_IMAGE_HPP */
