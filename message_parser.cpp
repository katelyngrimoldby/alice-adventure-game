#include "message_parser.h"

namespace parser {
  Message::Message (std::string file) {
    messages = new std::vector<ds::Message*>();

    load_file(file);
  }

  Message::~Message () {
    for (int i = 0; i < messages->size(); i++) delete messages->at(i);
    delete messages;
  }

  void Message::parse_data (void) {
    if(current_section == 1) {
      if(is_not_current(current_message, current_id)) {
        current_message = new ds::Message(current_id);
        messages->emplace_back(current_message);
      }

      current_message->append_to_content(line_vect.at(1));
    } else reset_currents();
  }

  std::vector<ds::Message*>* Message::return_messages (void) {
    return messages;
  }
}