/*
  item_parser.h
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Item_Parser
#define Item_Parser

#include <vector>
#include <string>
#include "item.h"
#include "location.h"
#include "parser.h"
#include "utility.h"

namespace parser {
  class Item : public Parser {
    std::vector<ds::Item*>* items;
    std::vector<ds::Location*>* locations;
    ds::Item* current_item;
    ds::Location* current_location;

    public:
      Item (std::string file, std::vector<ds::Item*>* item_v, std::vector<ds::Location*>* location_v);

      virtual ~Item ();

      void parse_descriptions (void);

      void parse_locations (void);

      void parse_data (void) override;
  };
}

#endif