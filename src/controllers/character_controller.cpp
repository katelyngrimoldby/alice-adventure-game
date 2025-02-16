/*
  character_controller.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "character_controller.h"

namespace controller {
  Character::Character (game::Data* d, game::Player* p) : Controller (d, p) {
    jam_spread = false;
  }

  Character::~Character () {}

  void Character::set_jam_spread (bool status) {
    jam_spread = status;
  }

  void Character::end_of_game (void) {
    print(get_message(18));
    exit(0);
  }

  void Character::rabbit_dialog (ds::Location* location, ds::Character* rabbit) {
    print(rabbit->get_current_dialog());

    if (location->get_number() == 3 && rabbit->get_dialog_index() == 1) {
      location->get_items()->add_item(data->get_item(6));
      location->get_items()->add_item(data->get_item(7));
    } else if (location->get_number() == 4 && rabbit->get_dialog_index() == 3) {
      location->get_items()->add_item(data->get_item(9));
    }

    rabbit->increment_dialog_index();
  }

  bool Character::caterpillar_dialog (ds::Location* location, ds::Character* caterpillar) {
    if (location->get_number() == 6) {
      print(caterpillar->get_current_dialog());
      caterpillar->increment_dialog_index();
      return true;
    } else {
      return false;
    }
  }

  bool Character::duchess_dialog (ds::Location* location, ds::Character* duchess) {
    if (location->get_number() == 7) {
      print(duchess->get_current_dialog());

      if(duchess->get_dialog_index() == 1) {
        if(player->get_inventory()->is_full()) {
          //  Call out full inventory message and end function execution
          print(get_message(28));
          return true;
        }

        player->get_inventory()->add_item(data->get_item(12));
        duchess->increment_dialog_index();
        return true;
      }
    } else {
      return false;
    }
  }

  bool Character::cat_dialog (ds::Location* location, ds::Character* cat) {
    if (location->get_number() == 5) {
      ds::Character* duchess = data->get_character(3);

      if(duchess->get_dialog_index() < 1 || player->get_inventory()->has_item(data->get_item(12))) {
        return false;
      }

      print(cat->get_current_dialog());
      cat->increment_dialog_index();
      return true;
    } else {
      return false;
    }
  }

  bool Character::hare_hatter_dialog (ds::Location* location) {
    ds::Character* hare = data->get_character(6);
    ds::Character* hatter = data->get_character(5);

    if(location->get_number() != 8) {
      return false;
    }

    if(hare->get_dialog_index() == 0 || hare->get_dialog_index() == 1) {
      print(hare->get_current_dialog());
      hare->increment_dialog_index();

    } else if (hatter->get_dialog_index() == 0) {
      print(hatter->get_current_dialog());
      hatter->increment_dialog_index();

    } else if (hatter->get_dialog_index() == 1) {
      if (!jam_spread) print(hatter->get_current_dialog());

      else {
        hatter->increment_dialog_index();
        print(hare->get_current_dialog());
      }

    } else if (hatter->get_dialog_index() == 2) {
      print(hatter->get_current_dialog());
    }

    return true;
  }

  bool Character::queen_dialog (ds::Location* location, ds::Character* queen) {
    if (location->get_number() == 9) {
      if (queen->get_dialog_index() == 2 || queen->get_dialog_index() == 3) {
        // Player has to hit hedgehog or show rose to advance dialog at these points
        print("The Queen waits expectantly.");
      } else {
        print(queen->get_current_dialog());

        if (queen->get_dialog_index() != 4) {
          //  Prevent Queen's Trial Hall dialog from being outputted
          queen->increment_dialog_index();
        }
      }
    // Verify at correct location - trial hall
    } else if (location->get_number() == 11) {
      //  Increment index first so Queen's last Garden dialog isn't outputted
      queen->increment_dialog_index();
      print(queen->get_current_dialog());
      end_of_game();
    } else {
      return false;
    }
    return true;
  }

  bool Character::gryphon_dialog (ds::Location* location, ds::Character* gryphon) {
    if (location->get_number() == 10) {
      print(gryphon->get_current_dialog());
      gryphon->increment_dialog_index();
      return true;
    } else {
      return false;
    }
  }

  bool Character::act_on_character (ds::Location* location, ds::Character* character) {
    switch (character->get_number()) {
      case 2:
        return caterpillar_dialog(location, character);
      case 3:
        return duchess_dialog(location, character);
      case 4:
        return cat_dialog(location, character);
      case 5:
        return hare_hatter_dialog(location);
      case 6:
        return hare_hatter_dialog(location);
      case 7:
        return queen_dialog(location, character);
      case 8:
        return gryphon_dialog(location, character);
      default:
        return false;
    }
  }
}