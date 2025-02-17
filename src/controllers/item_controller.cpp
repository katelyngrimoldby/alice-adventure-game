/*
  item_controller.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "item_controller.h"

namespace controller {
  Item::Item (game::Data* d, game::Player* p, Character* c) : Controller (d, p) {
    mushroom_eaten = false;
    character_controller = c;
  }

  Item::~Item () {
    delete character_controller;
  }

  bool Item::is_mushroom_eaten (void) {
    return mushroom_eaten;
  }

  void Item::change_size (int i) {
    util::Size size = player->get_current_size();

    if (size == util::Size::Small) {
      if (i == -1) print(get_message(32));
      else {
        print(get_message(13));
        player->set_current_size(util::Size::Normal);
      }
    } else if (size == util::Size::Large) {
      if (i == 1) print(get_message(32));
      else {
        print(get_message(13));
        player->set_current_size(util::Size::Normal);
      }
    } else {
      if (i == -1) {
        print(get_message(11));
        player->set_current_size(util::Size::Small);
      } else {
        print(get_message(12));
        player->set_current_size(util::Size::Large);
      }
    }
  }

  bool Item::check_location_items (ds::Item* item, ds::Location* location) {
    if (location->get_items()->has_item(item)) {
      if (item->get_number() == 16) print(get_message(25));
      else print(get_message(31));

      return true;
    }

    return false;
  }

  void Item::pickup_item (ds::Item* item, ds::Location* location) {
    // Verify location has item
    if (!location->get_items()->has_item(item)) {
      print(get_message(29));
      return;
    }
    
    // Verify item can be moved
    if (!item->is_movable()) {
      print(get_message(27));
      return;
    }

    // Verify inventory is not full
    if (player->get_inventory()->is_full()) {
      print(get_message(28));
      return;
    }

    player->get_inventory()->add_item(item);
    location->get_items()->remove_item(item);
    print(get_message(23) + item->get_inventory_message());
    return;
  }

  void Item::drop_item (ds::Item* item, ds::Location* location) {
    //  Verify player has item
    if (!player->get_inventory()->has_item(item)) {
      print(get_message(29));
      return;
    }

    player->get_inventory()->remove_item(item);

    //  special case for piglet in forest
    if (item->get_number() == 12 && location->get_number() == 5) {
      print(get_message(14));
      character_controller->cat_dialog(location, data->get_character(4));

    } else {
      location->get_items()->add_item(item);
      print(get_message(24) + item->get_inventory_message());
      return;
    }
  }

  bool Item::consume_item (ds::Item* item, ds::Location* location) {
    ds::Character* rabbit = data->get_character(1);
    ds::Character* hare = data->get_character(6);
    ds::Character* hatter = data->get_character(5);

    switch (item->get_number()) {
      case 3:  //  Jam jar
        //  Verify at correct point in story
        if (location->get_number() == 8 && hatter->get_dialog_index() == 1) {
          print(get_message(16));
          character_controller->set_jam_spread(true);

          //  Advance story
          character_controller->hare_hatter_dialog(location);
        } else {
          print(get_message(25));
        }
        break;
      case 4:  //  Drink me
        print(get_message(5));
        change_size(1);
        change_size(1);

        character_controller->rabbit_dialog(location, rabbit);

        break;
      case 5:  //  Eat Me
        {
          print(get_message(6));
          change_size(-1);

          //  Add "Drink Me" to environment
          ds::Item* bottle = data->get_item(4);
          location->get_items()->add_item(bottle);
          print(bottle->get_current_description());
        }
        break;
      case 8:  //  Bottle
        print(get_message(5));
        change_size(1);

        character_controller->rabbit_dialog(location, rabbit);

        break;
      case 9:  //  Cake
        print(get_message(6));
        change_size(-1);

        break;
      default:
        return false;
    }

    player->get_inventory()->remove_item(item);
    return true;
  }

  void Item::eat_mushroom (ds::Item* item, ds::Location* location) {
    if(!location->get_items()->has_item(item)) {
      print(get_message(29));
      return;
    }

    //  Check if at correct point in story
    if(data->get_character(2)->get_dialog_index() < 2) {
      print(get_message(25));
      return;
    }

    if (item->get_number() == 10) {  //  Right side
      print(get_message(9));
      change_size(1);
      if(!mushroom_eaten && player->get_current_size() == util::Size::Large) {  //  Player is large in forest for first time
        mushroom_eaten = true;
        print(get_message(37));
      }
    } else if (item->get_number() == 11) {  //  Left side
      print(get_message(10));
      change_size(-1);
    }
  }

  bool Item::is_door (ds::Item* item, ds::Location* location, int msg_num) {
    //  Verify item is a door
    if (item->get_number() != 16) {
      print(get_message(25));
      return false;
    }

    //  Verify door is in this location
    if (!location->get_items()->has_item(item)) {
      print(get_message(msg_num));
      return false;
    }

    return true;
  }

  void Item::open_door (ds::Item* item, ds::Location* location) {
    if(!is_door(item, location, 30)) {
      return;
    }

    //  Verify door can be opened
    if (item->get_prop_value() == 1) {
      item->set_prop_value(2);
      print(item->get_current_description());
      return;
    }

    //  This will run if door is locked or open
    print(item->get_current_description());
    return;
  }

  bool Item::unlock_door (ds::Item* item, ds::Location* location, int msg_num) {
    if(!is_door(item, location, 4)) {
      return false;
    }

    // Verify if player has key
    if (!player->get_inventory()->has_item(data->get_item(1))) {
      print(get_message(22));
      return false;
    }

    // Verify door can be unlocked
    if (item->get_prop_value() == 0) {
      print(get_message(msg_num));
      return true;
    } else {  // Only runs if door is unlocked or open
      print(item->get_current_description());
      return false;
    }
  }

  void Item::use_fan (ds::Location* location) {
    if (location->get_number() == 3 && player->get_current_size() == util::Size::Large) {
      ds::Character* rabbit = data->get_character(1);
      print(get_message(8));
      change_size(-1);
      character_controller->rabbit_dialog(location, rabbit);
      return;
    } else {
      print(get_message(25));
      return;
    }
  }

  bool Item::can_hit_hedgehog (ds::Location* location) {
    //  Verify in garden
    if (location->get_number() != 9) {
      print(get_message(36));
      return false;
    }

    //  Verify at correct point in story
    if (data->get_character(7)->get_dialog_index() == 0) {
      print(get_message(25));
      return false;
    }

    //  Verify hedgehog in garden
    if (!location->get_items()->has_item(data->get_item(15))) {
      print(get_message(36));
      return false;
    }

    //  Verify player has flamingo
    if (!player->get_inventory()->has_item(data->get_item(13))) {
      print(get_message(22));
      return false;
    }

    return true;
  }

  bool Item::use_flamingo (ds::Location* location) {
    if(can_hit_hedgehog(location)) {
      print(get_message(33));
      return true;
    }
    return false;
  }

  bool Item::hit_hedgehog (ds::Item* item, ds::Location* location) {
    if (item->get_number() != 15) {
        print(get_message(25));
        return false;
      }

      if(can_hit_hedgehog(location)) {
        print(get_message(35));
        return true;
      }
      return false;
  }

  bool Item::use_inventory_items (ds::Item* item, ds::Location* location) {
    if (player->get_inventory()->has_item(item)) {
      if(consume_item(item, location)) return false;

      //  Handle rest of items
      switch (item->get_number()) {
        case 1:  // Key
          {
            ds::Item* door = data->get_item(16);

            return unlock_door(door, location, 34);
          }
          break;
        case 7: // Fan
          use_fan(location);
          break;
        case 13:  // Flamingo
          return use_flamingo(location);
          break;
        default: // All other items
          print(get_message(25));
      }
    } else {
      print(get_message(29));
    }
    return false;
  }

  bool Item::use_item (ds::Item* item, ds::Location* location) {
    //  Handle Mushroom
    if(item->get_number() == 10 || item->get_number() == 11) {
      eat_mushroom(item, location);
      return false;
    }
    
    //  All other items in location
    if (check_location_items(item, location)) return false;

    //  Items in inventory
    return use_inventory_items(item, location);
  }

  void Item::eat_item (ds::Item* item, ds::Location* location) {
    //  Handle Mushroom
    if (item->get_number() == 10 || item->get_number() == 11) {
      eat_mushroom(item, location);
      return;
    }

    //  Check if item can be picked up
    if (check_location_items(item, location)) return;

    //  Verify item in inventory
    if (!player->get_inventory()->has_item(item)) {
      print(get_message(29));
      return;
    }

    //  Verify item is eatable
    if (item->get_number() == 5 || item->get_number() == 9) {
      consume_item(item, location);
      return;
    }

    //  All other items
    print(get_message(25));
  }

  void Item::drink_item (ds::Item* item, ds::Location* location) {
    //  Check if item can be picked up
    if (check_location_items(item, location)) return;

    //  Verify item in inventory
    if (!player->get_inventory()->has_item(item)) {
      print(get_message(29));
      return;
    }

    //  Verify item is drinkable
    if (item->get_number() == 4 || item->get_number() == 8) {
      consume_item(item, location);
      return;
    }

    //  All other items
    print(get_message(25));
  }

  void Item::show_rose (ds::Item* item, ds::Location* location) {
    //  Check if item in location
    if (check_location_items(item, location)) return;

    //  Verify item in inventory
    if (!player->get_inventory()->has_item(item)) {
      print(get_message(29));
      return;
    }

      //  Verify item is rose
      if (item->get_number() != 14) {
        print(get_message(25));
        return;
      }

      ds::Character* queen = data->get_character(7);

      // Verify if rose can be shown
      if(location->get_number() != 9 && queen->get_dialog_index() != 2) {
        print(get_message(25));
        return;
      }

      print(get_message(26));
      print(queen->get_current_dialog());
      queen->increment_dialog_index();
  }
  
  void Item::spread_jam (ds::Item* item, ds::Location* location) {
    //  Check if item can be picked up
    if (check_location_items(item, location)) return;

    //  Verify item in inventory
    if (!player->get_inventory()->has_item(item)) {
      print(get_message(29));
      return;
    }

    //  Verify item is jam jar
    if(item->get_number() == 3) {
      consume_item(item, location);
      return;
    }

    //  All other items
    print(get_message(25));
  }

  bool Item::act_on_item (ds::Action* action, ds::Item* item, ds::Location* location) {
    switch(action->get_number()) {
      case 1:  //  Pick up item
        pickup_item (item, location);
        break;
      case 2:  //  Drop item
        drop_item(item, location);
        break;
      case 4: // Open
        open_door(item, location);
        break;
      case 5: // Unlock
        return unlock_door(item, location, 3);
      case 6:  //  Use
        return use_item(item, location);
      case 7: //  Eat
        eat_item(item, location);
        break;
      case 8: //  Drink
        drink_item(item, location);
        break;
      case 9: //  Hit
        return hit_hedgehog(item, location);
      case 10: // Show
        show_rose(item, location);
        break;
      case 11: // spread
        spread_jam(item, location);
        break;
      default:
        print(get_message(2));
    }
    return false;
  }

  bool Item::is_item_correct (ds::Item* item, int target_item) {
    if (item->get_number() != target_item) {
      print(get_message(25));
      return false;
    }
    return true;
  }

  void Item::finish_unlock_door (ds::Item* door) {
    door->set_prop_value(1);
    print(door->get_current_description());
  }

  void Item::finish_hit_hedgehog (void) {
    ds::Character* queen = data->get_character(7);
    queen->set_dialog_index(2);

    print(get_message(15));
    print(queen->get_current_dialog());
    queen->increment_dialog_index();
  }

  void Item::act_on_second_item (ds::Item* item1, ds::Item* item2) {
    switch(item2->get_number()) {
      case 1: // Key - used with door
        //  Verification would be done when saying "unlock door"
        //  just need to make sure key was said in correct context
        if (is_item_correct(item1, 16)) {
          finish_unlock_door(item1);
        }
        break;
      case 13: //  Flamingo
        //  Verifcation would be done when saying "hit hedgehog"
        //  Just need to make sure flamingo was said in correct context
        if (is_item_correct(item1, 15)) {
          finish_hit_hedgehog();
        }
      break;
      case 15:  //  Hedgehog
      {
        //  Verifcation would be done when saying "use flamingo"
        //  Just need to make sure hedgehog was said in correct context
        if (is_item_correct(item1, 13)) {
          finish_hit_hedgehog();
        }
      }
        break;
      case 16:  //  Door
        //  Verification done when saying "use key"
        //  Just need to make sure door was said in correct context
        if (is_item_correct(item1, 1)) {
          finish_unlock_door(item2);
        }
        break;
      default: 
        print(get_message(25));
    }
  }
}