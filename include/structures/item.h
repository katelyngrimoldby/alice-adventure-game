/*
 item.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Item_Definition
#define Item_Definition

#include <vector>
#include <string>
#include "word.h"

namespace ds {
  class Item : public Word {
    int prop_value = 0;
    std::string inventory_message = "";
    std::vector<std::string> descriptions;

    bool movable = true;

    public:
      Item(int n);

      virtual ~Item();

      int get_prop_value (void);

      void set_prop_value (int val);

      std::string get_inventory_message (void);

      void set_inventory_message (std::string msg);

      std::vector<std::string> get_descriptions (void);

      void add_description (std::string desc);

      std::string get_current_description (void);

      bool is_movable (void);

      void set_movable (bool mov);
  };
}

#endif