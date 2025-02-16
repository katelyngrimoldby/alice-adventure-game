/*
 character.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/
#ifndef Character_Definition
#define Character_Definition

#include <string>
#include <vector>
#include "word.h"

namespace ds {
  class Character {
    int number;
    std::string name;
    Word* vocabulary;
    int dialog_index;
    std::vector<std::string> dialog;

    public:
      Character(int n);

      virtual ~Character();

      int get_number (void);

      std::string getName (void);

      void set_name (std::string s);

      Word* get_vocabulary (void);

      std::vector<std::string> get_dialog (void);

      void add_dialog (std::string msg);

      void append_to_dialog(int index, std::string msg);

      std::string get_current_dialog (void);

      int get_dialog_index (void);

      void set_dialog_index (int num);

      void increment_dialog_index (void);
  };
}



#endif