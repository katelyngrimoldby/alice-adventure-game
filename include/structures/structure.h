/*
  structure.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Structure_Base
#define Structure_Base

namespace ds {
  class Structure {
    int number;

    public:
      Structure (int n);

      virtual ~Structure ();

      int get_number (void);
      
      virtual void nil (void) = 0;
  };
}

#endif