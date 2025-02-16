/*
 parser.h
 Date: February 4, 2025
 Author: Katelyn Grimoldby
*/
#ifndef Parser_Base
#define Parser_Base

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "utility.h"

namespace parser {
  class Parser {
    std::ifstream in_file;

    protected: 
      std::vector<std::string> line_vect;
      int current_section;
      int current_id;

    public:
      Parser (void);
      
      virtual ~Parser();

      void load_file (std::string file);

      virtual void parse_data (void) = 0;

      void traverse_file (void);

      void parse_file (void);

      void reset_currents (void);

      bool is_not_current (auto* instance, int num);
  };
}

#endif