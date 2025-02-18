/*
  save_parser.cpp
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#include "save_parser.h"

namespace parser {
  Save::Save (std::string file, game::Data* d, game::Player* p) {
    data = d;
    player = p;
    current_location = NULL;

    load_file(file);
  }

  Save::~Save () {
    delete data;
    delete player;
  }

  template <typename T>
  void Save::replace_items (T* items) {
    items->get_items()->clear();
    int len = line_vect.size();

    for (int i = 1; i < len; i++) items->add_item(data->get_item(atoi(line_vect.at(i).c_str())));
  }

  void Save::parse_player_data (void) {
    if (current_id == 1) { // Size
      if (line_vect.at(1) == "Large") player->set_current_size(util::Size::Large);
      else if (line_vect.at(1) == "Normal") player->set_current_size(util::Size::Normal);
      else player->set_current_size(util::Size::Small);

    } else if (current_id == 2) { // Location
      player->set_current_location(data->get_location(atoi(line_vect.at(1).c_str())));

    } else replace_items(player->get_inventory());
  }

  void Save::parse_location_data (void) {
    // Ids of 000 denote items at location
    if (current_id > 0) {
      current_location = data->get_location(current_id);

      if (line_vect.at(1) == "true") current_location->set_visited(true);
      else current_location->set_visited(false);
    } else replace_items(current_location->get_items());
  }

  void Save::parse_data (void) {
    switch (current_section) {
      case 1:
        parse_player_data();
        break;
      case 2:
        parse_location_data();
        break;
      case 3:
        data->get_character(current_id)->set_dialog_index(atoi(line_vect.at(1).c_str()));
      case 0:
        reset_currents();
    }
  }
}