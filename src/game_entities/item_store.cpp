/*
  item_store.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "item_store.h"

namespace game {
  ItemStore::ItemStore (void) {
    items = new std::vector<ds::Item*>();
  }

  ItemStore::~ItemStore () {
    for (int i = 0; i < items->size(); i++) delete items->at(i);
    delete items;
  }

  std::vector<ds::Item*>* ItemStore::get_items (void) {
    return items;
  }

  bool ItemStore::has_item (ds::Item* item) {
    return util::has_element(items, item);
  }

  void ItemStore::add_item (ds::Item* item) {
    items->emplace_back(item);
  }

  void ItemStore::remove_item (ds::Item* item) {
    int i = util::find_index(items, item);

    if(i >= 0) items->erase(items->begin() + i);
  }

  std::string ItemStore::list_items (void) {
    std::string str = "";
    int len = items->size();

    //  Exclude mushroom sides
    for (int i = 0; i < len; i++) {
      if(items->at(i)->get_number() != 10 && items->at(i)->get_number() != 11) {
        str += (items->at(i)->get_current_description() + '\n');
      }
    }

    return str;
  }
}