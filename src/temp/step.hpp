#ifndef IMGFLSHR_STEP_H
#define IMGFLSHR_STEP_H

using namespace std;
#include <string>
class UI;

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

    virtual Step *next()   = 0;
    virtual Step *back()   = 0;

    virtual void init()    = 0;
    virtual void display(UI *ui) = 0;
    virtual void process() = 0;

};

#endif /* IMGFLSHR_STEP_H */
