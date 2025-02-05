/*
  location_parser.cpp
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#include "location_parser.h"

namespace parser {
  Location::Location (std::string file) {
    locations = new std::vector<ds::Location*>();
    motions = new std::vector<ds::Motion*>();

    load_file(file);
  }

  Location::~Location () {
    for (int i = 0; i < locations->size(); i++) delete locations->at(i);
    delete locations;
    delete current_location;

    for (int i = 0; i < motions->size(); i++) delete motions->at(i);
    delete motions;
    delete current_motion;
  }

  void Location::parse_long_descriptions (void) {
    if (is_not_current(current_location, current_id)) {
      current_location = new ds::Location(current_id);

      locations->emplace_back(current_location);
    }

    current_location->append_to_long_description(line_vect.at(1));
  }

  void Location::parse_short_descriptions (void) {
    if (is_not_current(current_location, current_id)) {
      current_location = util::get_instance(locations, current_id);
    }

    current_location->append_to_short_description(line_vect.at(1));
  }

  void Location::parse_location_mapping (void) {
    int destination_id = atoi(line_vect.at(1).c_str());
    int motion_id = atoi(line_vect.at(2).c_str());

    if (is_not_current(current_location, current_id)) {
      current_location = util::get_instance(locations, current_id);
    }

    if(is_not_current(accessible_location, destination_id)) {
      accessible_location = util::get_instance(locations, destination_id);
    }

    current_location->add_accesible_location(accessible_location);

    current_motion = util::get_instance(motions, motion_id);

    if(current_motion == NULL) {
      current_motion = new ds::Motion(motion_id);

      motions->emplace_back(current_motion);
    }

    current_location->add_motion(accessible_location, current_motion);
  }

  void Location::parseData (void) {
    switch (current_section) {
      case 1: //  Handles long descriptions for locations
        parse_long_descriptions();
        break;
      case 2:  //  Handles short descriptions for locations
        parse_short_descriptions();
        break;
      case 3:  //  Map locations to each other with motion words
        parse_location_mapping();
        break;
      case 0: //  End of data
        reset_currents();
    }
  }

  std::vector<ds::Location*>* Location::return_locations (void) {
    return locations;
  }

  std::vector<ds::Motion*>* Location::return_motions (void) {
    return motions;
  }
}