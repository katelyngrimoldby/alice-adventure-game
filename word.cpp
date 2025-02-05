#include "word.h"

namespace ds {
  Word::Word(int n) {
    number = n;
  }

  Word::~Word() {}

  int Word::get_number (void) {
    return number;
  }

  std::vector<std::string> Word::get_words (void) {
    return words;
  }

  void Word::add_word (std::string word) {
    words.emplace_back(word);
  }

  bool Word::has_word (std::string word) {
    return util::has_element(words, word);
  }
}