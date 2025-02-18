/*
  save_parser.h
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Save_Parser
#define Save_Parser

#include <string>
#include <vector>
#include "parser.h"
#include "data.h"
#include "player.h"
#include "location.h"
#include "utility.h"

namespace parser {
  class Save : public Parser {
    game::Data* data;
    game::Player* player;
    ds::Location* current_location;

    public:
      Save (std::string file, game::Data* d, game::Player* p);

      virtual ~Save ();

      template <typename T>
      void replace_items (T* items);

      void parse_player_data (void);

      void parse_location_data (void);

      void parse_data (void) override;
  };
}

#endif
