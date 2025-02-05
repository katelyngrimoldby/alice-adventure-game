#include "item_parser.h"

namespace parser {
  Item::Item (std::string file, std::vector<ds::Item*>* item_v, std::vector<ds::Location*>* location_v) {
    items = item_v;
    locations = location_v;

    load_file(file);
  }

  Item::~Item () {
    delete current_item;
    delete current_location;
  }

  void Item::parse_descriptions (void) {
    /*
      ID GUIDE

      single-digit ids (eg 1, 2, 3)  mark when a NEW item is being worked on and 
      will always contain that item's inventory description.

      triple-digit ids (eg 000, 100, 200) mark special property dialog for the item. 
      The id / 100 corresponds to the item's prop_value. "##" signals no description
    */
    if(current_item == NULL || (current_id >= 1 && current_id < 100)) {
      current_item = util::get_instance(items, current_id);

      current_item->set_inventory_message(line_vect.at(1));
    } else {
      // 
      if(line_vect.at(1) != "##") current_item->add_description(line_vect.at(1));
    }
  }

  void Item::parse_locations (void) {
    if(is_not_current(current_item, current_id)) {
      current_item = util::get_instance(items, current_id);
    }

    if(line_vect.at(1) != "0") {  //  0 means the item is in no location to start
      current_location = util::get_instance(locations, atoi(line_vect.at(1).c_str()));

      current_location->add_item(current_item);

      if(line_vect.size() > 2) {
        current_item->set_movable(false);

        if(line_vect.at(2) != "-1") {  //  -1 just means the item is static, while any other number is a second location and the location is static
          current_location = util::get_instance(locations, atoi(line_vect.at(2).c_str()));

          current_location->add_item(current_item);
        }
      }
    }
  }

  void Item::parse_data (void) {
    switch(current_section) {
      case 1:  //  Item descriptions
        parse_descriptions();
        break;
      case 2:  //  Item locations
        parse_locations();
        break;
      case 0:  //  End of file
        reset_currents();
    }
  }
}