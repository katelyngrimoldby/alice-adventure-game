/*
 motion.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Motion_Definition
#define Motion_Definition

#include "word.h"

namespace ds {
  class Motion : public Word {
    public: 
      Motion (int n);

      virtual ~Motion ();
  };
}



#endif