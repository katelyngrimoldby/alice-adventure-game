#include "parser.h"

namespace parser {
  Parser::Parser (void) {
    current_id = -1;
    current_section = -1;
  }
  
  Parser::~Parser() {};

  void Parser::load_file (std::string file) {
    in_file.open(file);

    if(!in_file.good()) {
      std::cout << "Error opening file." << std::endl;
      exit(1);
    }

    traverse_file();

    in_file.close();
  }

  void Parser::traverse_file (void) {
    std::string line;

    while (true) {
      if(in_file.eof()) break;
      getline(in_file, line);

      line_vect = util::split(line, '\t');

      parse_file();
    }
  }

  void Parser::parse_file (void) {
    if(line_vect.at(0) == "-1") {  //  End of section
        reset_currents();
      } else if (current_section == -1) {  //  If end of section was already reached then current line must be start of next section
      current_section = atoi(line_vect.at(0).c_str());
    } else if (current_section != 0) {  //  In current section therefore will have data to parse
      current_id = atoi(line_vect.at(0).c_str());

      parse_data();
    }
  }

  void Parser::reset_currents (void) {
    current_section = -1;
    current_id = -1;
  }

  template <typename T> 
  bool is_not_current (T* instance, int num) {
    if (instance == NULL || instance->getNumber() != num) {
      return true;
    } 

    return false;
  }
}