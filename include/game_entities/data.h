/*
  data.h
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Game_Data
#define Game_Data

#include <vector>
#include <string>
#include "action.h"
#include "character.h"
#include "item.h"
#include "location.h"
#include "message.h"
#include "motion.h"
#include "word.h"
#include "character_parser.h"
#include "item_parser.h"
#include "location_parser.h"
#include "message_parser.h"
#include "vocabulary_parser.h"
#include "utility.h"

namespace game {
  class Data {
    std::vector<ds::Action*>* actions;
    std::vector<ds::Character*>* characters;
    std::vector<ds::Item*>* items;
    std::vector<ds::Location*>* locations;
    std::vector<ds::Message*>* messages;
    std::vector<ds::Motion*>* motions;
    std::vector<ds::Word*>* words;

    public:
      Data (void);

      virtual ~Data ();

      ds::Action* get_action (int n);

      ds::Character* get_character (int n);

      ds::Item* get_item (int n);

      ds::Location* get_location (int n);

      ds::Message* get_message (int n);

      ds::Motion* get_motion (int n);

      ds::Word* get_word (int n);

      util::Command* find_word (std::string word);

      std::vector<ds::Character*>* get_characters (void);

      std::vector<ds::Location*>* get_locations (void);
  };
}

#endif