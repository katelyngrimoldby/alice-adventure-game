/*
  item_store.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Item_Store
#define Item_Store

#include <vector>
#include <string>
#include "item.h"
#include "utility.h"

namespace game {
  class ItemStore {
    std::vector<ds::Item*>* items;

    public:
      ItemStore (void);

      virtual ~ItemStore ();

      std::vector<ds::Item*>* get_items (void);

      bool has_item (ds::Item* item);

      void add_item (ds::Item* item);

      void remove_item (ds::Item* item);

      std::string list_items (void);
  };
}

#endif