//
// Created by shecannotsee on 24-3-6.
//

#ifndef CURSOR_MOVE_H
#define CURSOR_MOVE_H

#include <iostream>

inline void clear_screen() {
  std::cout << "\033[2J\033[1;1H";
}

namespace cursor_move {

inline void to_line_start() noexcept {
  std::cout << "\r";
}

inline void to_terminal_start() noexcept {
  std::cout << "\033[H";
}

}  // namespace cursor_move

#endif  // CURSOR_MOVE_H
