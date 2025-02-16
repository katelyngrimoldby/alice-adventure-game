/*
  player.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Game_Player
#define Game_player

#include <string>
#include "inventory.h"
#include "location.h"
#include "utility.h"

namespace game {
  class Player {
    util::Size current_size;
    ds::Location* current_location;
    Inventory* inventory;

    public:
      Player (ds::Location* init_location, ds::Item* init_item, int inventory_size);

      virtual ~Player ();

      ds::Location* get_current_location (void);

      void set_current_location (ds::Location* location);

      Inventory* get_inventory (void);

      util::Size get_current_size (void);

      void set_current_size(util::Size size);
  };
}

#endif