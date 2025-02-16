/*
 message.h
 Date: February 16, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Message_Definition
#define Message_Definition

#include <string>
#include "structure.h"

namespace ds {
  class Message : public Structure {
    std::string content;

    public:
      Message (int n);

      virtual ~Message ();

      std::string get_content (void);

      void append_to_content (std::string msg);
  };
}

#endif