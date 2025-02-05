/*
 word.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/

#ifndef Word_Definition
#define Word_Definition

#include <string>  // Stream declarations
#include <vector>
#include "utility.h"

namespace ds {
  class Word {
    int number;
    std::vector<std::string> words;

    public:
      Word (int n);

      virtual ~Word();

      int get_number (void);

      std::vector<std::string> get_words (void);

      void add_word (std::string word);

      bool has_word (std::string word);
  };
}



#endif