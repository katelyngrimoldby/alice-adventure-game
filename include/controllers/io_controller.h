/*
  io_controller.h
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#ifndef IO_Controller
#define IO_Controller

#include <iostream>
#include <vector>
#include <string>
#include "controller.h"
#include "data.h"
#include "player.h"
#include "character_controller.h"
#include "item_controller.h"
#include "motion_controller.h"
#include "special_controller.h"
#include "utility.h"

namespace controller {
  template <typename T>
  class IO : public Controller {
    std::vector<T*> commands;
    Character* character_controller;
    Item* item_controller;
    Motion* motion_controller;
    Special* special_controller;

    public:
      IO (game::Data* d, game::Player* p);

      virtual ~IO ();

      void reset_cin (void);

      void clear_commands (void);

      std::string to_lower (std::string s);

      void bad_input (void);

      std::string get_input (bool secondary);

      void to_command (std::string input);

      void handle_command (bool secondary = false);

      void start_of_game (void);
  };
}

#endif
