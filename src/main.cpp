/*
  main.cpp
  Date: February 18, 2025
  Author: Katelyn Grimoldby
*/

#include "utility.h"
#include "data.h"
#include "player.h"
#include "io_controller.h"

int main (void) {
  game::Data* data = new game::Data();
  game::Player* player = new game::Player(data->get_location(1), data->get_item(2), 3);
  controller::IO<util::Command> io_controller(data, player);

  io_controller.start_of_game();
}