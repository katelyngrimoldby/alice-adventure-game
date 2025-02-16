/*
  location_parser.h
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Location_Parser
#define Location_Parser

#include <vector>
#include <string>
#include "location.h"
#include "motion.h"
#include "parser.h"
#include "utility.h"

namespace parser {
  class Location : public Parser {
    std::vector<ds::Location*>* locations;
    std::vector<ds::Motion*>* motions;
    ds::Location* current_location;
    ds::Location* accessible_location;
    ds::Motion* current_motion;

    public:
      Location (std::string file);

      virtual ~Location ();

      void parse_long_descriptions (void);

      void parse_short_descriptions (void);

      void parse_location_mapping (void);

      void parseData (void);

      std::vector<ds::Location*>* return_locations (void);

      std::vector<ds::Motion*>* return_motions (void);
    };
}

#endif