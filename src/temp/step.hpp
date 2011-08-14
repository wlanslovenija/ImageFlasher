using namespace std;
#ifndef IMGFLSHR_STEP_HPP
#define IMGFLSHR_STEP_HPP


#include <string>
class UI;
class UIStep;

class Step {
  protected:
    UI *ui;

    std::string next_step;
    std::string step_id;

    std::string step_name;
    std::string step_desc;

    void setName(std::string name);

    void setDesc(std::string name);

  public:

    std::string getName();
    std::string getDesc();
    std::string getID();

    virtual std::string getNext()   = 0;

    virtual void init()    = 0;
    virtual void process() = 0;

};

#endif /* IMGFLSHR_STEP_HPP */
