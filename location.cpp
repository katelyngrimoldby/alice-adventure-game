/*
  location.cpp
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#include "location.h"

namespace ds {
  Location::Location (int n) {
    visited = false;
    short_description = "";
    long_description = "";
    items = new std::vector<Item*>();
    accessible_locations = new std::vector<Location*>();
    motions = new std::vector<std::vector<Motion*>*>();
  }

  Location::~Location() {
    items->begin();
    for (int i = 0; i < items->size(); i++) delete items->at(i);
    delete items;

    for (int i = 0; i < accessible_locations->size(); i++) delete accessible_locations->at(i);
    delete accessible_locations;

    for (int i = 0; i < motions->size(); i++) {
      for (int j = 0; j < motions->at(i)->size(); j++) delete motions->at(i)->at(j);

      delete motions->at(i);
    }
    delete motions;
  };

  int Location::get_number (void) {
    return number;
  }

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

  std::vector<Item*>* Location::get_items (void) {
    return items;
  }

  bool Location::has_item (Item* item) {
      return util::has_element(items, item);
  }

  void Location::add_item (Item* item) {
    items->emplace_back(item);
  }

  void Location::remove_item (Item* item) {
    int index = util::find_index(items, item);
      if (index >= 0) {
        items->erase(items->begin() + index);
      }
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

  std::string Location::list_items (void) {
    std::string items_string = "";

    //  Exclude mushroom sides
    for (int i = 0; i < items->size(); i++) {
      if(items->at(i)->get_number() != 10 && items->at(i)->get_number() != 11) {
        items_string += (items->at(i)->get_current_description() + '\n');
      }
    }
    return items_string;
  }

  std::string Location::to_string (void) {
    std::string location_string = "";

    if(visited) {
      location_string += short_description;
    } else {
      location_string += long_description;
    }

    location_string += '\n';
    location_string += list_items();

    return location_string;
  }
}