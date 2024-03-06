//
// Created by shecannotsee on 24-3-6.
//

#ifndef DRAWING_BOARD_H
#define DRAWING_BOARD_H

#include <string>
#include <vector>

class drawing_board {
 private:
  int width_{40};
  int height_{10};
  int w_index_{0};
  int h_index_{0};
  std::vector<std::string> buffer_;
  drawing_board() : buffer_(height_, std::string(width_, ' ')) {
  }

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
    buffer_.resize(height_, std::string(width_, ' '));
  }

  void draw_done() const {
    for (const auto& e : buffer_) {
      printf("%s\n", e.c_str());
    }
  }
};

#endif  // DRAWING_BOARD_H
