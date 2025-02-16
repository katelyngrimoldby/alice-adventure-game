/*
  message.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "message.h"

namespace ds {
  Message::Message (int n) : Structure(n) {
    content = "";
  }

  Message::~Message () {};


  std::string Message::get_content (void) {
    return content;
  }

  void Message::append_to_content (std::string msg) {
    content += (msg += '\n');
  }
}