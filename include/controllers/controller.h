/*
  controller.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Controller_Base
#define Controller_Base

#include <iostream>
#include <string>
#include "data.h"
#include "player.h"

namespace controller {
  class Controller {
    protected:
      game::Data* data;
      game::Player* player;

    public:
      Controller (game::Data* d, game::Player* p);
      
      virtual ~Controller ();

      void print (std::string msg);

      std::string get_message (int n);
  };
}

#endif