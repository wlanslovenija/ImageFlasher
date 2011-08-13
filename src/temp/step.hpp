using namespace std;
#ifndef IMGFLSHR_STEP_HPP
#define IMGFLSHR_STEP_HPP


#include <string>
class UI;
class UIStep;

class Step {
  protected:
    UI *ui;

    std::string stepName;
    std::string stepDesc;

    void setName(std::string name);

    void setDesc(std::string name);

  public:

    std::string get_name();
    std::string get_desc();

    virtual UIStep *next()   = 0;
    virtual UIStep *back()   = 0;

    virtual void init()    = 0;
    virtual void process() = 0;

};

#endif /* IMGFLSHR_STEP_HPP */
