/*
  data.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "data.h"

namespace game {
  Data::Data (void) {
    parser::Location location_parser ("../data/locations.txt");
    locations = location_parser.return_locations();
    motions = location_parser.return_motions();

    parser::Vocabulary vocabulary_parser ("../data/vocabulary.txt", motions);
    actions = vocabulary_parser.return_actions();
    characters = vocabulary_parser.return_characters();
    items = vocabulary_parser.return_items();
    words = vocabulary_parser.return_words();

    parser::Message message_parser ("../data/messages.txt");
    messages = message_parser.return_messages();

    parser::Character character_parser ("../data/characters.txt", characters);
    parser::Item item_parser ("../data/items.txt", items, locations);
  }

  Data::~Data () {
    for (int i = 0; i < actions->size(); i++) delete actions->at(i);
    delete actions;

    for (int i = 0; i < characters->size(); i++) delete characters->at(i);
    delete characters;

    for (int i = 0; i < items->size(); i++) delete items->at(i);
    delete items;

    for (int i = 0; i < locations->size(); i++) delete locations->at(i);
    delete locations;

    for (int i = 0; i < messages->size(); i++) delete messages->at(i);
    delete messages;

    for (int i = 0; i < motions->size(); i++) delete motions->at(i);
    delete motions;

    for (int i = 0; i < words->size(); i++) delete words->at(i);
    delete words;
  }

  ds::Action* Data::get_action (int n) {
    return util::get_instance(actions, n);
  }

  ds::Character* Data::get_character (int n){
    return util::get_instance(characters, n);
  }

  ds::Item* Data::get_item (int n){
    return util::get_instance(items, n);
  }

  ds::Location* Data::get_location (int n){
    return util::get_instance(locations, n);
  }

  ds::Message* Data::get_message (int n){
    return util::get_instance(messages, n);
  }

  ds::Motion* Data::get_motion (int n){
    return util::get_instance(motions, n);
  }

  ds::Word* Data::get_word (int n){
    return util::get_instance(words, n);
  }

  ds::Word* Data::find_word (std::string word) {
    int len = actions->size();
    for (int i = 0; i < len; i++) {
      if (actions->at(i)->has_word(word)) return actions->at(i);
    }

    len = characters->size();
    for (int i = 0; i < len; i++) {
      if (characters->at(i)->get_vocabulary()->has_word(word)) return characters->at(i)->get_vocabulary();
    }

    len = items->size();
    for (int i = 0; i < len; i++) {
      if (items->at(i)->has_word(word)) return items->at(i);
    }

    len = motions->size();
    for (int i = 0; i < len; i++) {
      if (motions->at(i)->has_word(word)) return motions->at(i);
    }

    len = words->size();
    for (int i = 0; i < len; i++) {
      if (words->at(i)->has_word(word)) return words->at(i);
    }

    return NULL;
  }

  ds::Character* Data::find_character (ds::Word* word) {
    int len = characters->size();
    for (int i = 0; i < len; i++) {
      if (characters->at(i)->get_vocabulary() == word) return characters->at(i);
    }

    return NULL;
  }
}