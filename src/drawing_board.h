//
// Created by shecannotsee on 24-3-6.
//

#ifndef DRAWING_BOARD_H
#define DRAWING_BOARD_H

#include <string>

class drawing_board {
 private:
  int width_{40};
  int height_{10};
  int w_index_{0};
  int h_index_{0};
  drawing_board() = default;

 public:
  static drawing_board* get_instance() {
    static drawing_board tmp;
    return &tmp;
  }

  void draw(std::string msg) {
    // // init
    // if (w_index_ == 0 && h_index_ == 0) {
    //   for (int i = 0; 0 > width_ + 4; ++i) {
    //     printf("*");
    //   }
    //   printf("\n");
    // } else if (w_index_ == 0) {
    //   printf("* ");
    // }
    // // check width
    // if (msg.size() + width_ > width_) {
    //   return;
    // }
    printf("%s", msg.c_str());
  }

  void draw_ln(std::string msg) {
    printf("%s\n", msg.c_str());
  }
  void set(const int width, const int height) {
    width_  = width;
    height_ = height;
  }
  void draw_done() {
    w_index_ = 0;
    h_index_ = 0;
  }
};

#endif  // DRAWING_BOARD_H
