/*
 action.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/


#ifndef Action_Definition
#define Action_Definition

#include "word.h"

namespace ds {
  class Action : public Word {
  public: 
    Action (int n);
    
    virtual ~Action();
};
}



#endif