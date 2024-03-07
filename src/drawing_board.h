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
  int w_index_{0};  // [2,width]
  int h_index_{0};  // [1,height_-2]
  std::vector<std::string> buffer_;
  std::string info_;
  std::string echo_;
  std::string debug_;
  drawing_board()
      : buffer_(height_ + 2, std::string(width_ + 4, ' ')),
        info_(width_ + 4, ' '),
        echo_(width_ + 4, ' '),
        debug_(width_ + 4, ' ') {
    initialize_border();
  }

 public:
  static drawing_board* get_instance() {
    static drawing_board tmp;
    return &tmp;
  }

  void draw(std::string msg) {
    // Check if the index is out of range

    // draw
    for (const auto& e : msg) {
      buffer_[real_h_index()][real_w_index()] = e;
      w_index_++;
    }
  }

  void draw_ln(std::string msg) {
    // Check if the index is out of range

    // draw
    for (const auto& e : msg) {
      buffer_[real_h_index()][real_w_index()] = e;
      w_index_++;
    }
    h_index_++;
    w_index_ = 0;
  }

  void draw_info(const std::string& info) {
    // clear
    std::fill(info_.begin(), info_.end(), ' ');
    // draw
    for (int i = 0; i < info.size(); ++i) {
      info_[i] = info[i];
    }
  }

  void draw_echo(const std::string& echo) {
    // clear
    std::fill(echo_.begin(), echo_.end(), ' ');
    // draw
    for (int i = 0; i < echo.size(); ++i) {
      echo_[i] = echo[i];
    }
  }

  void draw_debug(const std::string& debug) {
    // clear
    std::fill(debug_.begin(), debug_.end(), ' ');
    // draw
    for (int i = 0; i < debug.size(); ++i) {
      debug_[i] = debug[i];
    }
  }

  void set(const int width, const int height) {
    width_  = width;
    height_ = height;
    buffer_.resize(height_ + 2, std::string(width_ + 4, ' '));
    initialize_border();
  }

  void draw_done() {
    printf("%s\n", info_.c_str());
    for (auto& e : buffer_) {
      printf("%s\n", e.c_str());
      // init
      std::fill(e.begin(), e.end(), ' ');
    }
    printf("%s\n", echo_.c_str());
    printf("%s\n", debug_.c_str());

    // init
    initialize_border();
    h_index_ = 0;
    w_index_ = 0;
  }

 private:
  void initialize_border() {
    constexpr char horizontal_border = '*';
    constexpr char vertical_border   = '*';
    // draw
    for (auto& e : buffer_[0]) {
      e = horizontal_border;
    }
    for (auto& e : buffer_[height_ + 1]) {
      e = horizontal_border;
    }
    for (int i = 1; i < height_ + 1; ++i) {
      buffer_[i][0]          = vertical_border;
      buffer_[i][width_ + 3] = vertical_border;
    }
  }

  constexpr int real_h_index() const {
    return h_index_ + 1;
  }
  constexpr int real_w_index() const {
    return w_index_ + 2;
  }
};

#endif  // DRAWING_BOARD_H
