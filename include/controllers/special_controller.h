/*
  special_controller.h
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Special_Controller
#define Special_Controller

#include <fstream>
#include <iostream>
#include "controller.h"
#include "save_parser.h"
#include "word.h"
#include "utility.h"

namespace controller {
  class Special : public Controller {
    public:
      Special (game::Data* d, game::Player* p);

      virtual ~Special ();

      void load_save (void);

      void write_save (void);

      void act_on_command (ds::Word* word);
  };
}

#endif
