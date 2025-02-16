/*
 location.h
 Date: February 16, 2025
 Author: Katelyn Grimoldby
*/


#ifndef Location_Definition
#define Location_Definition

#include <vector>
#include <string>
#include "structure.h"
#include "utility.h"
#include "item.h"
#include "motion.h"

namespace ds {
  class Location : public Structure {
    bool visited;
    std::string short_description;
    std::string long_description;
    std::vector<Item*>* items;
    std::vector<Location*>* accessible_locations;
    std::vector<std::vector<Motion*>*>* motions;

    public:
      Location (int n);

      virtual ~Location();

      bool is_visited (void);

      void set_visited (bool visited);

      std::string get_long_description (void);

      void append_to_long_description (std::string line);

      std::string get_short_description (void);

      void append_to_short_description (std::string line);

      std::vector<Item*>* get_items (void);

      bool has_item (Item* item);

      void add_item (Item* item);

      void remove_item (Item* item);

      std::vector<Location*>* get_accessible_locations (void);

      int get_index (Location* location);

      void add_accesible_location (Location* location);
      std::vector<std::vector<Motion*>*>* get_motions (void);

      void add_motion (Location* location, Motion* motion);

      Location* location_to_go (Motion* motion);

      std::string list_items (void);

      std::string to_string (void);
  };
}

#endif