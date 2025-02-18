/*
  special_controller.cpp
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#include "special_controller.h"

namespace controller {
  Special::Special (game::Data* d, game::Player* p) : Controller(d, p) {}

  Special::~Special () {}

  void Special::load_save (void) {
    // Check file exists
    std::ifstream save_file("save.txt");
    if(!save_file.good()) {
      std::cout << "No save exists" << std::endl;
      save_file.close();
      return;
    }
    save_file.close();

    // Parse save data
    parser::Save save_parser("save.txt", data, player);
    save_parser.parse_data();
  }

  void Special::write_save (void) {
    std::ofstream save_file("save.txt");

    // Write player data
    save_file << "1\n";

    // Size
    save_file << "1\t";
    if (player->get_current_size() == util::Size::Large) save_file << "Large\n";
    else if (player->get_current_size() == util::Size::Normal) save_file << "Normal\n";
    else save_file << "Small\n";

    // Current Location
    save_file << "2\t" << player->get_current_location()->get_number() << "\n";

    // Inventory contents
    save_file << "3";
    auto inventory_v = player->get_inventory()->get_items();
    int len = inventory_v->size();

    for (int i = 0; i < len; i++) save_file << "\t" << inventory_v->at(i)->get_number();
    save_file << "\n-1\n";

    // Locations
    save_file << "2\n";

    auto locations = data->get_locations();
    len = locations->size();

    for (int i = 0; i < len; i++) {
      auto location = locations->at(i);
      save_file << location->get_number() << "\t";

      // Visited flag
      if (location->is_visited()) save_file << "true\n";
      else save_file << "false\n";

      save_file << "000";

      // Items
      auto items = location->get_items()->get_items();
      int len2 = items->size();

      for (int j = 0; j < len2; j++) save_file << "\t" << items->at(j)->get_number();
      save_file << "\n";
    }

    save_file << "-1\n";

    // Characters - dialog index
    save_file << "3\n";

    auto characters = data->get_characters();
    len = characters->size();

    for (int i = 0; i < len; i++) {
      auto character = characters->at(i);

      save_file << character->get_number() << "\t" << character->get_dialog_index() << "\n";
    }

    save_file << "-1\n0";
  }

  void Special::act_on_command (ds::Word* word) {
    switch (word->get_number()) {
      case 401: //  401: help
          print(get_message(21));
          break;
        case 402: //  402: quit
          print("Thanks for playing!");
          exit(0);
          break;
        case 403: // 403: inventory
          print(player->get_inventory()->list_items());
          break;
        case 404: // 404: save
          write_save();
          break;
        default:
          print(get_message(2));
    }
  }
}