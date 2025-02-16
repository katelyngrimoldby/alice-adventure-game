/*
  location.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "location.h"

namespace ds {
  Location::Location (int n) : Structure(n) {
    visited = false;
    short_description = "";
    long_description = "";
    items = new game::ItemStore();
    accessible_locations = new std::vector<Location*>();
    motions = new std::vector<std::vector<Motion*>*>();
  }

  Location::~Location() {
    delete items;

    for (int i = 0; i < accessible_locations->size(); i++) delete accessible_locations->at(i);
    delete accessible_locations;

    for (int i = 0; i < motions->size(); i++) {
      for (int j = 0; j < motions->at(i)->size(); j++) delete motions->at(i)->at(j);

      delete motions->at(i);
    }
    delete motions;
  };

  bool Location::is_visited (void) {
    return visited;
  }

  void Location::set_visited (bool visited) {
    visited = visited;
  }

  std::string Location::get_long_description (void) {
    return long_description;
  }

  void Location::append_to_long_description (std::string line) {
    long_description += (line + '\n');
  }

  std::string Location::get_short_description (void) {
    return short_description;
  }

  void Location::append_to_short_description (std::string line) {
    short_description += (line + '\n');
  }

  game::ItemStore* Location::get_items (void) {
    return items;
  }

  std::vector<Location*>* Location::get_accessible_locations (void) {
    return accessible_locations;
  }

  int Location::get_index (Location* location) {
    return util::find_index(accessible_locations, location);
  }

  void Location::add_accesible_location (Location* location) {
    accessible_locations->emplace_back(location);
    motions->emplace_back(new std::vector<Motion*>());
  }

  std::vector<std::vector<Motion*>*>* Location::get_motions (void) {
    return motions;
  }

  void Location::add_motion (Location* location, Motion* motion) {
    int index = get_index(location);
    motions->at(index)->emplace_back(motion);
  }

  Location* Location::location_to_go (Motion* motion) {
    for (int i = 0; i < motions->size(); i++) {
      if(util::has_element(motions->at(i), motion)) {
        return accessible_locations->at(i);
      }
    }

    return NULL;
  }

  std::string Location::to_string (void) {
    std::string location_string = "";

    if(visited) {
      location_string += short_description;
    } else {
      location_string += long_description;
    }

    location_string += '\n';
    location_string += items->list_items();

    return location_string;
  }
}