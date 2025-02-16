/*
  vocabulary_parser.h
  Date: February 4, 2025
  Author: Katelyn Grimoldby
*/

#ifndef Vocabulary_Parser
#define Vocabulary_Parser

#include <vector>
#include <string>
#include "parser.h"
#include "action.h"
#include "character.h"
#include "item.h"
#include "motion.h"
#include "word.h"
#include "utility.h"

namespace parser {
  class Vocabulary : public Parser {
    std::vector<ds::Action*>* actions;
    std::vector<ds::Character*>* characters;
    std::vector<ds::Item*>* items;
    std::vector<ds::Motion*>* motions;
    std::vector<ds::Word*>* words;

    ds::Action* current_action;
    ds::Character* current_character;
    ds::Item* current_item;
    ds::Motion* current_motion;
    ds::Word* current_word;

    public:
      Vocabulary (std::string file, std::vector<ds::Motion*>* motion_v);

      virtual ~Vocabulary ();

      void parse_actions (void);

      void parse_characters (void);

      void parse_items (void);

      void parse_motions (void);

      void parse_words (void);

      void parse_data (void);

      std::vector<ds::Action*>* return_actions (void);

      std::vector<ds::Character*>* return_characters (void);

      std::vector<ds::Item*>* return_items (void);

      std::vector<ds::Word*>* return_words (void);
    };  
}

#endif