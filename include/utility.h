/*
 utility.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Utility
#define Utility

#include <string>
#include <sstream>
#include <vector>
#include "action.h"
#include "character.h"
#include "item.h"
#include "motion.h"
#include "word.h"

namespace util {

  struct Command {
    ds::Action* action = NULL;
    ds::Character* character = NULL;
    ds::Item* item = NULL;
    ds:: Motion* motion = NULL;
    ds::Word* word = NULL;
  };

  enum class Size {Small, Normal, Large};

  // Non-pointer functions
  template <typename T>
  int find_index (std::vector<T> v, T element);

  template <typename T>
  bool has_element (std::vector<T> v, T element);

  std::vector<std::string> split(std::string text, char delim);

  // Pointer functions
  template <typename T>
  int find_index (std::vector<T*>* v, T* element);

  template <typename T>
  bool has_element (std::vector<T*>* v, T* element);

  template <typename T>
  T get_instance (std::vector<T>* v, int n);
}



#endif