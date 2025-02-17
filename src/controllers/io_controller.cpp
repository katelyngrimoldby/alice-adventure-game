/*
  io_controller.cpp
  Date: February 17, 2025
  Author: Katelyn Grimoldby
*/

#include "io_controller.h"

namespace controller {
  template <typename T>
  IO<T>::IO (game::Data* d, game::Player* p) : Controller (d, p) {
    character_controller = new Character(d, p);
    item_controller = new Item(d, p, character_controller);
    motion_controller = new Motion(d, p, character_controller, item_controller);
    commands = new vector<T*>();
  }

  template <typename T>
  IO<T>::~IO () {
    delete character_controller;
    delete item_controller;
    delete motion_controller;

    clear_commands();
  };

  template <typename T>
  void IO<T>::reset_cin (void) {
    std::cin.clear();
    std::cin.sync();
  }

  template <typename T>
  void IO<T>::clear_commands (void) {
    int len = commands.size();
    for (int i = 0; i < len; i ++) delete commands.at(i);
    commands.clear();
  }

  template <typename T>
  std::string IO<T>::to_lower (std::string s) {
    std::string lower = "";
    int len = s.size();

    for (int i = 0; i < len; i++) lower += std::tolower(s[i]);

    return lower;
  }

  template <typename T>
  void IO<T>::bad_input (void) {
    print(get_message(2))
    get_input()
  }

  template <typename T>
  std::string IO<T>::get_input (bool secondary) {
    if (!secondary) clear_commands();

    reset_cin();

    std::string input;
    std::getline(std::cin, input);

    return input;
  }

  template <typename T>
  void IO<T>::to_command (std::string input) {
    std::string lower = convertToLower(input);
    std::vector<std::string> v = util::split(lower, ' ');
    
    if(v.size() > 2 || v.size() < 1) {
      return bad_input();
    } else {
      for (int i = 0; i < v.size(); i++) {
        if(data->find_word(v.at(i)) != NULL) {
          commands.emplace_back(data->find_word(v.at(i)));
        } else {
          return bad_input();
        }
      }
    }
  }

  template <typename T>
  void IO<T>::handle_command (bool secondary = false) {
    std::string input = get_input(secondary)
    to_command(input);

    if (commands.size() > 0) {
      auto location = player->get_current_location();

      // One word: Motion (0-99) or Special (400-499)
      if (commands.size() == 1) {
        if (commands.at(0)->motion != NULL) {  //  Check if word is Motion
          auto motion = commands.at(0)->motion
          motion_controller->move(motion, location);

          handle_command();
        } else if (commands.at(0)->getNumber() / 100 == 4) {  // Check if word is special word (number > 400)
          // TO CREATE CONTROLLER FOR

        } else  bad_input();

      } else if (commands.size() == 2) {  //  Two words: Action and Motion/Character/Item
        if(commands.at(0)->action != NULL) {  // Check if first word is Action
          auto action = commands.at(0)->action;

          //  Action Motion
          if(commands.at(1)->motion != NULL) {  //  Check if second word is Motion
            //  Only valid Action is #3: go
            if (action->getNumber() != 3) return bad_input();

            auto motion = commands.at(1)->motion;
            motion_controller->move(motion, location);

            handle_command();

          //  Action Item
          } else if (commands.at(1)->item != NULL) {  //  Check if second word is Item
            auto item = commands.at(1)->item;
            //  act_on_item returns true if it needs a third word and false if it does not
            if (item_controller->act_on_item(action, item, location)) handle_command(true);

            else handle_command();

          //  Action Character
          } else if (commands.at(1)->character != NULL) {  //  Check if second word is present in any Characters
            auto character = commands.at(1)->character;

            //  Only vaid action is #12: talk
            if(action->get_number() != 12) return bad_input();
            
            //  act_on_character returns true if dialog was successfully outputted, returns false if not
            if (character_controller->act_on_character(location, character)) handle_command();
            else bad_input();

          } else bad_input();  //  No other options for second word
        } else bad_input();  //  No other options for first word
      } else if (commands.size() == 3) {  //  Only runs in case of continuance - should always have item in 2nd index
          if(commands.at(2)->item != NULL) {  //  Check if third word is Item

            auto item1 = commands.at(1)->item;
            auto item2 = commands.at(2)->item;

            item_controller->act_on_second_item(item1, item2);
            handle_command();
          } else bad_input();
      }  //  Impossible to have more than 3 elements
    } else bad_input();
  }

  template <typename T>
  void IO<T>::start_of_game (void) {
    //  Intro message
    print(get_message(20));

    //  Location description and items
    print(player->get_current_location()->to_string());

    //  Set starting location as visited - done after output 
    //  to prevent short description from being read
    player->get_current_location()->set_visited(true);

    //  Output White Rabbit's initial message
    character_controller->rabbit_dialog(player->get_current_location(), data->get_character(1));
    
    promptInput();
  }
}