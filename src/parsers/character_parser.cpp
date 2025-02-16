/*
  character_parser.cpp
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#include "character_parser.h"

namespace parser {
  Character::Character (std::string file, std::vector<ds::Character*>* char_v) {
    characters = char_v;

    load_file(file);
  }

  Character::~Character () {
    delete current_character;
  }

  void Character::parse_data (void) {
    if(current_section == 1) {
      /*
      ID GUIDE

      single-digit ids (eg 1, 2, 3)  mark when a NEW character is being worked on and 
      will always contain that character's name.

      triple-digit ids (eg 000, 100, 200) mark dialog for the character currently being 
      worked on. the id/100 matches the index of the dialog within the vector. Therefore, 
      if the last index in the dialog vector is 1 and the next line of data to be assigned 
      has an id of 100, then it is a continuation of the current dialog and must be appended
      */
      if(current_character == NULL || (current_id >= 1 && current_id < 100)) {
        current_character = util::get_instance(characters, current_id);

        current_character->set_name(line_vect.at(1));
      } else {
        if(current_id / 100 == current_character->get_dialog().size() - 1) {
          current_character->append_to_dialog(current_id / 100, line_vect.at(1));
        } else {
          current_character->add_dialog(line_vect.at(1));
        }
      }
    } else reset_currents();
  }
}