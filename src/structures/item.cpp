/*
  item.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "item.h"

namespace ds {
  Item::Item(int n) : Word(n) {
    prop_value = 0;
    inventory_message = "";
    movable = true;
  };

  Item::~Item() {};

  int Item::get_prop_value (void) {
    return prop_value;
  }

  void Item::set_prop_value (int val) {
    prop_value = val;
  }

  std::string Item::get_inventory_message (void) {
    return inventory_message;
  }

  void Item::set_inventory_message (std::string msg) {
    inventory_message = msg;
  }

  std::vector<std::string> Item::get_descriptions (void) {
    return descriptions;
  }

  void Item::add_description (std::string desc) {
    descriptions.emplace_back(desc);
  }

  std::string Item::get_current_description (void) {
    return descriptions.at(prop_value);
  }

  bool Item::is_movable (void) {
    return movable;
  }

  void Item::set_movable (bool mov) {
    movable = mov;
  }
}