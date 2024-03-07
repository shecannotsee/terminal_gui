//
// Created by shecannotsee on 24-3-6.
//

#ifndef TERMINAL_OPERATION_H
#define TERMINAL_OPERATION_H
#include <termios.h>
#include <unistd.h>

#include <iostream>

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
    buffer->draw_info("Welcome to the terminal_gui program.");
    menu main_menu;
    while (true) {
      cursor_move::to_terminal_start();
      static auto now_page        = page::homepage;
      static auto now_page_option = page_opt::option1;
      buffer->draw_debug(":" + std::string(magic_enum::enum_name(now_page)) + ":" +
                         std::string(magic_enum::enum_name(now_page_option)));
      try {
        main_menu.display(now_page, now_page_option);
      } catch (...) {
        clear_screen();
        printf("Exit program terminal_gui\n");
        break;
      }
      const auto status = get_keyboard_events();
      buffer->draw_echo("[" + std::string(magic_enum::enum_name(status)) + "]");
      switch (status) {
        case keyboard_events::step_into: {
          if (now_page == page::homepage) {
            if (now_page_option == page_opt::option1) {
              now_page        = page::option1;
              now_page_option = page_opt::null;
            } else if (now_page_option == page_opt::option2) {
              now_page        = page::option2;
              now_page_option = page_opt::null;
            } else if (now_page_option == page_opt::exit) {
              now_page        = page::exit;
              now_page_option = page_opt::null;
            }
          }
          break;
        }
        case keyboard_events::step_out: {
          if (now_page != page::homepage) {
            if (now_page == page::option1) {
              now_page        = page::homepage;
              now_page_option = page_opt::option1;
            } else if (now_page == page::option2) {
              now_page        = page::homepage;
              now_page_option = page_opt::option2;
            }
          }
          break;
        }
        case keyboard_events::select_up: {
          if (now_page == page::homepage) {
            if (now_page_option == page_opt::option2) {
              now_page_option = page_opt::option1;
            } else if (now_page_option == page_opt::exit) {
              now_page_option = page_opt::option2;
            }
          }
          break;
        }
        case keyboard_events::select_down: {
          if (now_page == page::homepage) {
            if (now_page_option == page_opt::option1) {
              now_page_option = page_opt::option2;
            } else if (now_page_option == page_opt::option2) {
              now_page_option = page_opt::exit;
            }
          }
          break;
        }
        case keyboard_events::quit: {
          return;
          break;
        }
        case keyboard_events::invalid_key: {
          buffer->draw_info("Invalid key");
          break;
        }
        default: {
          break;
        }
      }
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
