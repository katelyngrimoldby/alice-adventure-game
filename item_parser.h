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

    ds::Item* current_item = NULL;
    ds::Location* current_location = NULL;

    public:
      Item (std::string file, std::vector<ds::Item*>* item_v, std::vector<ds::Location*>* location_v);

      virtual ~Item ();

      void parse_descriptions (void);

      void parse_locations (void);

      void parse_data (void);
  };
}

#endif