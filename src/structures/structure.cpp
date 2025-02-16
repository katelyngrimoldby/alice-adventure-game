/*
  structure.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "structure.h"

namespace ds {
  Structure::Structure (int n) {
    number = n;
  }

  Structure::~Structure () {}

  int Structure::get_number (void) {
    return number;
  }
}