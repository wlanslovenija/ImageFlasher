using namespace std;
#ifndef IMGFLSHR_STEP_HPP
#define IMGFLSHR_STEP_HPP


#include <string>
class UI;
class UI_Step;

class Step {
  protected:
    UI *ui;

    std::string stepName;
    std::string stepDesc;

    void set_name(std::string name);

    void set_desc(std::string name);

  public:

    std::string get_name();
    std::string get_desc();

    virtual UI_Step *next()   = 0;
    virtual UI_Step *back()   = 0;

    virtual void init()    = 0;
    virtual void process() = 0;

};

#endif /* IMGFLSHR_STEP_HPP */
