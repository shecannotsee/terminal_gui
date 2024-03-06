//
// Created by shecannotsee on 24-3-6.
//

#ifndef LOAD_H
#define LOAD_H

#include <iostream>

#include "cursor_move.h"

inline void displayLoadingBar(int percentage) {
  cursor_move::to_line_start();
  std::cout << "[";

  int numChars = percentage / 2;
  for (int i = 0; i < 50; ++i) {
    if (i < numChars) {
      std::cout << "=";
    } else {
      std::cout << " ";
    }
  }

  std::cout << "] " << percentage << "%";
  std::cout.flush();
}

#endif  // LOAD_H
