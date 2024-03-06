//
// Created by shecannotsee on 24-3-6.
//

#ifndef TERMINAL_OPERATION_H
#define TERMINAL_OPERATION_H
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <thread>

#include "cursor_move.h"
#include "drawing_board.h"
#include "magic_enum-0.9.5/magic_enum.hpp"
#include "menu.h"

enum class keyboard_events : unsigned char {
  step_into,
  step_out,
  select_up,
  select_down,
  quit,
  invalid_key,
  placeholder
};

class terminal_gui {
  static constexpr int UP_ARROW    = 65;
  static constexpr int DOWN_ARROW  = 66;
  static constexpr int RIGHT_ARROW = 67;
  static constexpr int LEFT_ARROW  = 68;

 public:
  terminal_gui() {
    auto enable_arrow_keys = []() {
      struct termios oldattr, newattr;
      tcgetattr(STDIN_FILENO, &oldattr);
      newattr = oldattr;
      newattr.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    };
    enable_arrow_keys();
  }
  ~terminal_gui() {
    auto restore_terminal = []() {
      struct termios oldattr;
      tcgetattr(STDIN_FILENO, &oldattr);
      oldattr.c_lflag |= (ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    };
    restore_terminal();
  }

  void start() {
    clear_screen();
    auto buffer = drawing_board::get_instance();
    buffer->draw_ln("Welcome to the terminal_gui program.");
    menu main_menu;
    while (true) {
      static int page        = 0;
      static int page_option = 0;
      main_menu.display(page, page_option);
      auto status     = get_keyboard_events();
      auto status_str = magic_enum::enum_name(status);
      std::cout << status_str << std::endl;
    }
  }

 private:
  static keyboard_events get_keyboard_events() {
    int ch = getchar();
    switch (ch) {
      case 27: {
        ch = getchar();
        if (ch == 27) {
          return keyboard_events::quit;
        }
        switch (getchar()) {
          case UP_ARROW: {
            return keyboard_events::select_up;
          }
          case DOWN_ARROW: {
            return keyboard_events::select_down;
          }
          case RIGHT_ARROW:
            return keyboard_events::step_into;
          case LEFT_ARROW:
            return keyboard_events::step_out;
            break;
          default:
            return keyboard_events::invalid_key;
        }
      }
      case '\n': {
        return keyboard_events::step_into;
      }
      case 'q':
      case 'Q': {
        ch = getchar();
        if (ch == '\n') {
          return keyboard_events::quit;
        }
        return keyboard_events::invalid_key;
      }
      default: {
        return keyboard_events::invalid_key;
      }
    }
  }
};

#endif  // TERMINAL_OPERATION_H
