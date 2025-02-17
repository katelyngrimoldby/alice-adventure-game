/*
  motion_controller.cpp
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#include "motion_controller.h"

namespace controller {
  Motion::Motion (game::Data* d, game::Player* p, Character* c, Item* i) : Controller (d, p) {
    character_controller = c;
    item_controller = i;

    key_generated = false;
  }

  Motion::~Motion () {
    delete character_controller;
    delete item_controller;
  };

  void Motion::invalid_movement (void) {
    print(get_message(1));
  }

  bool Motion::check_size (void) {
    if (player->get_current_size() != util::Size::Normal) {
      invalid_movement();
      return false;
    }

    return true;
  }

  bool Motion::check_door (ds::Motion* motion) {
    if (motion->get_number() == 9) {
      ds::Item* door = data->get_item(16);

      if(door->get_prop_value() != 2) {
        print(door->get_current_description());
        return false;
      }
    }
    return true;
  }

  bool Motion::check_landing_room_conds (ds::Motion* motion, ds::Location* location) {
    ds::Character* hatter = data->get_character(5);
    if(motion->get_number() == 9) {  //  To check if coming from tea party
      //  Verify hatter's been spoken with enough
      if (hatter->get_dialog_index() == 2) {
        //  Generate key if not already done
        if(!key_generated) {
          location->get_items()->add_item(data->get_item(1));
          key_generated = true;
          print(get_message(17));
        }
      } else {
        invalid_movement();
        return false;
      }
    }

    //  Set door to locked before going through
    ds::Item* door = data->get_item(16);
    door->set_prop_value(0);

    return true;
  }

  bool Motion::check_rabbit_house_conds (void) {
    ds::Character* rabbit = data->get_character(1);
    //  Verify player can leave landing room
    if(rabbit->get_dialog_index() < 2) {
      invalid_movement();
      return false;
    }
    return true;
  }

  bool Motion::check_forest_conds (ds::Location* location) {
    if (location->get_number() == 4) {
      //  Has the player consumed the unlabeled bottle?
      if (player->get_inventory()->has_item(data->get_item(9)) || location->get_items()->has_item(data->get_item(9))) {
        invalid_movement();
        return false;
      }
    }
    return true;
  }

  bool Motion::check_duchess_house_conds (void) {
    //  Verify player has found house
    if (!item_controller->is_mushroom_eaten()) {
      invalid_movement();
      return false;
    }
    return true;
  }

  bool Motion::check_tea_party_conds (void) {
    ds::Character* cat = data->get_character(4);
    //  Verify cat has shown player to tea party
    if (cat->get_dialog_index() < 1) {
      invalid_movement();
      return false;
    }

    //  Set door to unlocked before moving
    ds::Item* door = data->get_item(16);
    door->set_prop_value(1);
    return true;
  }

  bool Motion::check_castle_conds (ds::Location* location) {
    ds::Character* queen = data->get_character(7);
    //  Verify queen has announced trial or player not already in trial
    if (queen->get_dialog_index() < 4 || location->get_number() == 11) {
      invalid_movement();
      return false;
    }
    return true;
  }

  bool Motion::check_location_conds (ds::Motion* motion, ds::Location* new_location, ds::Location* old_location) {
    switch (new_location->get_number()) {
      case 3:  //  Landing room
        return check_landing_room_conds(motion, new_location);
      case 4:  //  White Rabbit's house
        return check_rabbit_house_conds();
      case 5:  //  Forest
        return check_forest_conds(old_location);
      case 7:  //  Duchess' house
        return check_duchess_house_conds();
      case 8:  //  Tea party
        return check_tea_party_conds();
      case 10:  //  Castle
        return check_castle_conds(old_location);
      default:
        return true;
    }
  }

  void Motion::dialog_when_entering (ds::Location* location) {
    if (location->get_number() == 10) { // Trigger gryphon's dialogue when entering castle for first time
        character_controller->gryphon_dialog(location, data->get_character(8));
      } else if (location->get_number() == 11) {
        character_controller->rabbit_dialog(location, data->get_character(1));
      }
  }

  void Motion::move (ds::Motion* motion, ds::Location* location) {
    ds::Location* new_location = location->location_to_go(motion);

    if (new_location != NULL) {
      if(!check_size()) return;

      if(!check_door(motion)) return;

      if (!check_location_conds(motion, new_location, location)) return;
      

      player->set_current_location(new_location);
      print(new_location->to_string());
      if (!new_location->is_visited()) {
        dialog_when_entering(new_location);
        new_location->set_visited(true);
      }
    } else {
      invalid_movement();
    }
  }
}