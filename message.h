/*
 message.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Message_Definition
#define Message_Definition

#include <string>

namespace ds {
  class Message {
    int number;
    std::string content;

    public:
      Message (int n);

      virtual ~Message ();

      int get_number (void);

      std::string get_content (void);

      void append_to_content (std::string msg);
  };
}

#endif