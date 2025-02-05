/*
  message.cpp
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#include "message.h"

namespace ds {
  Message::Message (int n) {
    content = "";
    number = n;
  }

  Message::~Message () {};

  int Message::get_number (void) {
    return number;
  }

  std::string Message::get_content (void) {
    return content;
  }

  void Message::append_to_content (std::string msg) {
    content += (msg += '\n');
  }
}