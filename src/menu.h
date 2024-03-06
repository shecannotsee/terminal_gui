//
// Created by shecannotsee on 24-3-6.
//

#ifndef MENU_H
#define MENU_H

class menu {
 private:
  int page{0};

 public:
  void display(const int page, const int page_option) {
    switch (page) {
      case 0: {
        homepage(page_option);
        break;
      }
      default: {
        drawing_board::get_instance()->draw_ln("no page to show");
        break;
      }
    }
  }

  void homepage(const int page_option) {
    auto buffer = drawing_board::get_instance();
    using namespace std;
    buffer->draw_ln("Use arrow keys to select an option:");
    for (int i = 0; i < 3; ++i) {
      if (i == page_option)
        buffer->draw("> ");
      else
        buffer->draw("  ");

      switch (i) {
        case 0:
          buffer->draw_ln("Option 1");
          break;
        case 1:
          buffer->draw_ln("Option 2");
          break;
        case 2:
          buffer->draw_ln("Exit");
          break;
        default:
          break;
      }
    }
  }
};

#endif  // MENU_H
