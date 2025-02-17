/*
  motion_controller.h
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Motion_Controller
#define Motion_Controller

#include "controller.h"
#include "character_controller.h"
#include "item_controller.h"
#include "motion.h"
#include "item.h"
#include "location.h"
#include "character.h"

namespace controller {
  class Motion : public Controller {
    Item* item_controller;
    Character* character_controller;
    bool key_generated;

    public:
      Motion (game::Data* d, game::Player* p, Character* c, Item* i);

      virtual ~Motion ();

      void invalid_movement (void);

      bool check_size (void);

      bool check_door (ds::Motion* motion);

      bool check_landing_room_conds (ds::Motion* motion, ds::Location* location);

      bool check_rabbit_house_conds (void);

      bool check_forest_conds (ds::Location* location);

      bool check_duchess_house_conds (void);

      bool check_tea_party_conds (void);

      bool check_castle_conds (ds::Location* location);

      bool check_location_conds (ds::Motion* motion, ds::Location* new_location, ds::Location* old_location);

      void dialog_when_entering (ds::Location* location);

      void move (ds::Motion* motion, ds::Location* location);
  };
}

#endif