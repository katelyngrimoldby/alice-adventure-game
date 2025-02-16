/*
  inventory.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "inventory.h"

namespace game {
  Inventory::Inventory (int n) {
    max_size = n;
  }

  Inventory::~Inventory () {}

  bool Inventory::is_full (void) {
    return (get_items()->size() >= max_size);
  }

  std::string Inventory::list_items (void) {
    std::vector<ds::Item*>* items = get_items();
    int len = items->size();
    std::string str = "";

    for (int i = 0; i < len; i++) str += (items->at(i)->get_inventory_message() + "\n");
  }
}