using namespace std;

#include <string>


class Step {

  protected:
    string stepName;
    string stepDesc;

    string get_name();
    void set_name(string name);

    string get_desc();
    void set_desc(string name);

    virtual Step *next()   = 0;
    virtual Step *back()   = 0;

    virtual void init()    = 0;
    virtual void display() = 0;
    virtual void process() = 0;

}

string Step::get_name(){
  return stepName;
}

void Step::set_name(string name){
  stepName = name;
}


