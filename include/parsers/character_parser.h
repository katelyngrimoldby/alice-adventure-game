/*
  character_parser.h
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Character_Parser
#define Character_Parser

#include <vector>
#include <string>
#include "character.h"
#include "parser.h"
#include "utility.h"

namespace parser {
  class Character: public Parser {
    std::vector<ds::Character*>* characters;

    ds::Character* current_character;

    public:
      Character (std::string file, std::vector<ds::Character*>* char_v);

      virtual ~Character ();

      void parse_data (void) override;
  };
}

#endif