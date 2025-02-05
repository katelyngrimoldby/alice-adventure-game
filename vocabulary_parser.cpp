#include "vocabulary_parser.h"

namespace parser {
  Vocabulary::Vocabulary (std::string file, std::vector<ds::Motion*>* motion_v) {
    actions = new std::vector<ds::Action*>();
    characters = new std::vector<ds::Character*>();
    items = new std::vector<ds::Item*>();
    motions = motion_v;
    words = new std::vector<ds::Word*>();

    load_file(file);
  }

  Vocabulary::~Vocabulary () {
    for (int i = 0; i < actions->size(); i++) delete actions->at(i);
    delete actions;
    delete current_action;

    for (int i = 0; i < characters->size(); i++) delete characters->at(i);
    delete characters;
    delete current_character;

    for (int i = 0; i < items->size(); i++) delete items->at(i);
    delete items;
    delete current_item;

    for (int i = 0; i < motions->size(); i++) delete motions->at(i);
    delete motions;
    delete current_motion;

    for (int i = 0; i < words->size(); i++) delete words->at(i);
    delete words;
    delete current_word;
  }

  void Vocabulary::parse_actions (void) {
    if(is_not_current(current_action, current_id - 200)) {
      current_action = new ds::Action(current_id - 200);

      actions->emplace_back(current_action);
    }

    current_action->add_word(line_vect.at(1));
  }

  void Vocabulary::parse_characters (void) {
    //  Characters only have one vocabulary word each, so is_not_current is not necessary
    current_character = new ds::Character(current_id - 300);

    characters->emplace_back(current_character);

    current_character->get_vocabulary()->add_word(line_vect.at(1));
  }

  void Vocabulary::parse_items (void) {
    //  Items only have one vocabulary word each, so is_not_current is not necessary
    current_item = new ds::Item(current_id - 100);

    items->emplace_back(current_item);

    current_item->add_word(line_vect.at(1));
  }

  void Vocabulary::parse_motions (void) {
    current_motion = util::get_instance(motions, current_id);

    if(current_motion == NULL) {
      current_motion = new ds::Motion(current_id);

      motions->emplace_back(current_motion);
    }

    current_motion->add_word(line_vect.at(1));
  }

  void Vocabulary::parse_words (void) {
    if(is_not_current(current_word, current_id)) {
      current_word = new ds::Word(current_id);

      words->emplace_back(current_word);
    }

    current_word->add_word(line_vect.at(1));
  }

  void Vocabulary::parse_data (void) {
    if (current_section == 1) {
      switch (current_id / 100) {
        case 0:  //  Motions
          parse_motions();
          break;
        case 1: //  Items
          parse_items();
          break;
        case 2:  //  Actions
          parse_actions();
          break;
        case 3:  //  Characters
          parse_characters();
          break;
        case 4:  //  Other words
          parse_words();
      }
    } else reset_currents();
  }

  std::vector<ds::Action*>* Vocabulary::return_actions (void) {
    return actions;
  }

  std::vector<ds::Character*>* Vocabulary::return_characters (void) {
    return characters;
  }

  std::vector<ds::Item*>* Vocabulary::return_items (void) {
    return items;
  }

  std::vector<ds::Word*>* Vocabulary::return_words (void) {
    return words;
  }
}