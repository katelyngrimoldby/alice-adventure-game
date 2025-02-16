/*
  character.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "character.h"

namespace ds {
  Character::Character(int n) : Structure(n) {
    dialog_index = 0;
  }

  Character::~Character() {
    delete vocabulary;
  }

  std::string Character::getName (void) {
    return name;
  }

  void Character::set_name (std::string s) {
    name = s;
  }

  Word* Character::get_vocabulary (void) {
    return vocabulary;
  }

  std::vector<std::string> Character::get_dialog (void) {
    return dialog;
  }

  void Character::add_dialog (std::string msg) {
    dialog.emplace_back(msg + '\n');
  }

  void Character::append_to_dialog(int index, std::string msg) {
    dialog.at(index) += (msg + '\n');
  }

  std::string Character::get_current_dialog (void) {
    return dialog.at(dialog_index);
  }

  int Character::get_dialog_index (void) {
    return dialog_index;
  }

  void Character::set_dialog_index (int num) {
    if(num < dialog.size()) {
      dialog_index = num;
    } 
  }

  void Character::increment_dialog_index (void) {
    if(dialog_index >= dialog.size() - 1) {
      return;
    }

    dialog_index++;
  }
}
  