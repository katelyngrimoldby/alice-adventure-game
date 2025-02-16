/*
  inventory.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Game_Inventory
#define Game_Inventory

#include <string>
#include <vector>
#include "item_store.h"
#include "item.h"

namespace game {
  class Inventory : public ItemStore {
    int max_size;

    public:
      Inventory (int n);

      virtual ~Inventory ();

      bool is_full (void);

      std::string list_items (void);
  };
}

#endif