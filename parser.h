/*
 parser.h
 Description: DataParser class
 Date: May 14, 2024
 Author: Katelyn Grimoldby
 Version: 1.0
 Copyright: 2024 Katelyn Grimoldby
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
  };
}

#endif