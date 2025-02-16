/*
  character_controller.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Character_Controller
#define Character_Controller

#include "controller.h"
#include "data.h"
#include "player.h"
#include "character.h"
#include "location.h"

namespace controller {
  class Character : public Controller {
    bool jam_spread;

    public:
      Character (game::Data* d, game::Player* p);

      virtual ~Character ();

      void set_jam_spread (bool status);

      void end_of_game (void);

      void rabbit_dialog (ds::Location* location, ds::Character* rabbit);

      bool caterpillar_dialog (ds::Location* location, ds::Character* caterpillar);

      bool duchess_dialog (ds::Location* location, ds::Character* duchess);

      bool cat_dialog (ds::Location* location, ds::Character* cat);

      bool hare_hatter_dialog (ds::Location* location);

      bool queen_dialog (ds::Location* location, ds::Character* queen);

      bool gryphon_dialog (ds::Location* location, ds::Character* gryphon);

      bool act_on_character (ds::Location* location, ds::Character* character);
  };
}

#endif