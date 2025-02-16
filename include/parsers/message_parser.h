/*
  message_parser.h
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Message_Parser
#define Message_Parser

#include <vector>
#include <string>
#include "message.h"
#include "parser.h"

namespace parser {
  class Message : public Parser {
    std::vector<ds::Message*>* messages;
    ds::Message* current_message;
    
    public:
      Message (std::string file);

      virtual ~Message ();

      void parse_data (void) override;

      std::vector<ds::Message*>* return_messages (void);
  };
}


#endif