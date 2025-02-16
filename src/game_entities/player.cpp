/*
  player.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "player.h"

namespace game {
  Player::Player (ds::Location* init_location, ds::Item* init_item, int inventory_size) {
    current_location = init_location;

    inventory = new Inventory(inventory_size);
    inventory->add_item(init_item);

    current_size = util::Size::Normal;
  }

  Player::~Player () {
    delete current_location;
    delete inventory;
  }

  ds::Location* Player::get_current_location (void) {
    return current_location;
  }

  void Player::set_current_location (ds::Location* location) {
    current_location = location;
  }

  Inventory* Player::get_inventory (void) {
    return inventory;
  }

  util::Size Player::get_current_size (void) {
    return current_size;
  }

  void Player::set_current_size (util::Size size) {
    current_size = size;
  }
}