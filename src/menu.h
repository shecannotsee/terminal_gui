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
    using namespace std;
    cout << "Use arrow keys to select an option:\n";
    for (int i = 0; i < 3; ++i) {
      if (i == page_option)
        cout << "> ";
      else
        cout << "  ";
      switch (i) {
        case 0:
          cout << "Option 1\n";
          break;
        case 1:
          cout << "Option 2\n";
          break;
        case 2:
          cout << "Exit\n";
          break;
        default:
          break;
      }
    }
  }
};

#endif  // MENU_H
