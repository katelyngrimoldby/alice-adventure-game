/*
  utility.cpp
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#include "utility.h"

namespace util {
  // Non-Pointer functions

  template <typename T>
  int find_index (std::vector<T> v, T element) {
    for(int i = 0; i < v.size(); i++) {
      if(v.at(i) == element) {
        return i;
      }
    }

    return -1;
  }

  template <typename T>
  bool has_element (std::vector<T> v, T element) {
    for(int i = 0; i < v.size(); i++) {
      if(v.at(i) == element) {
        return true;
      }
    }

    return false;
  }

  // Code from roach's answer on StackOverflow (https://stackoverflow.com/a/65075284)
  std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> v;
    std::stringstream ss(text);

    while(getline(ss, line, delim)) {
        v.push_back(line);
    }
    return v;
  }

  // Pointer functions

  template <typename T>
  int find_index (std::vector<T*>* v, T* element) {
    for(int i = 0; i < v->size(); i++) {
      if(v->at(i) == element) {
        return i;
      }
    }

    return -1;
  }

  template <typename T>
  bool has_element (std::vector<T*>* v, T* element) {
    for(int i = 0; i < v->size(); i++) {
      if(v->at(i) == element) {
        return true;
      }
    }

    return false;
  }

  template <typename T>
  T get_instance (std::vector<T>* v, int n) {
    for(int i = 0; i < v->size(); i++) {
      if(v->at(i)->getNumber() == n) {      
        return v->at(i);
      }
    }

    return NULL;
  }
}