/*
  controller.cpp
  Date: February 16, 2025
  Author: Katelyn Grimoldby
*/

#include "controller.h"

namespace controller {
  Controller::Controller (game::Data* d, game::Player* p) {
    data = d;
    player = p;
  }

  Controller::~Controller () {
    delete data;
    delete player;
  }

  void Controller::print (std::string msg) {
    std::cout << msg << std::endl;
  }

  std::string Controller::get_message (int n) {
    return data->get_message(n)->get_content();
  }
}