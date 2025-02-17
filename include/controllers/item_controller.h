/*
  item_controller.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Item_Controller
#define Item_Controller

#include "controller.h"
#include "character_controller.h"
#include "data.h"
#include "player.h"
#include "action.h"
#include "item.h"
#include "character.h"
#include "location.h"

namespace controller {
  class Item : public Controller {
    bool mushroom_eaten;
    Character* character_controller;

    public:
      Item (game::Data* d, game::Player* p, Character* c);

      virtual ~Item ();

      bool is_mushroom_eaten (void);

      void change_size (int i);

      bool check_location_items (ds::Item* item, ds::Location* location);

      void pickup_item (ds::Item* item, ds::Location* location);

      void drop_item (ds::Item* item, ds::Location* location);

      bool consume_item (ds::Item* item, ds::Location* location);

      void eat_mushroom (ds::Item* item, ds::Location* location);

      bool is_door (ds::Item* item, ds::Location* location, int msg_num);

      void open_door (ds::Item* item, ds::Location* location);

      bool unlock_door (ds::Item* item, ds::Location* location, int msg_num);

      void use_fan (ds::Location* location);

      bool can_hit_hedgehog (ds::Location* location);

      bool use_flamingo (ds::Location* location);

      bool hit_hedgehog (ds::Item* item, ds::Location* location);

      bool use_inventory_items (ds::Item* item, ds::Location* location);

      bool use_item (ds::Item* item, ds::Location* location);

      void eat_item (ds::Item* item, ds::Location* location);

      void drink_item (ds::Item* item, ds::Location* location);

      void show_rose (ds::Item* item, ds::Location* location);
      
      void spread_jam (ds::Item* item, ds::Location* location);

      bool act_on_item (ds::Action* action, ds::Item* item, ds::Location* location);

      bool is_item_correct (ds::Item* item, int target_item);

      void finish_unlock_door (ds::Item* door);

      void finish_hit_hedgehog (void);

      void act_on_second_item (ds::Item* item1, ds::Item* item2);
  };
}

#endif