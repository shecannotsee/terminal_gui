//
// Created by shecannotsee on 24-3-6.
//

#ifndef MENU_H
#define MENU_H

enum class page : unsigned char { homepage, option1, option2, exit };
enum class page_opt : unsigned char { null, option1, option2, exit };

class menu {
 public:
  void display(const page select_page, page_opt page_option) {
    switch (select_page) {
      case page::homepage: {
        this->homepage(page_option);
        break;
      }
      case page::option1: {
        this->page1();
        break;
      }
      case page::option2: {
        this->page2();
        break;
      }
      case page::exit: {
        this->exit();
        break;
      }
      default: {
        drawing_board::get_instance()->draw_info("no page to show");
        break;
      }
    }
    drawing_board::get_instance()->draw_done();
  }

 private:
  void homepage(page_opt page_option) {
    auto buffer = drawing_board::get_instance();
    buffer->draw_ln("Use arrow keys to select an option:");

    if (page_option == page_opt::option1) {
      buffer->draw_ln("> Option 1");
    } else {
      buffer->draw_ln("  Option 1");
    }
    if (page_option == page_opt::option2) {
      buffer->draw_ln("> Option 2");
    } else {
      buffer->draw_ln("  Option 2");
    }
    if (page_option == page_opt::exit) {
      buffer->draw_ln("> Exit");
    } else {
      buffer->draw_ln("  Exit");
    }
  }

  void page1() {
    auto buffer = drawing_board::get_instance();
    buffer->draw_ln("You have selected option 1");
  }

  void page2() {
    auto buffer = drawing_board::get_instance();
    buffer->draw_ln("You have selected option 2");
  }

  void exit() {
    auto buffer = drawing_board::get_instance();
    buffer->draw_ln("Exiting......");
    throw std::runtime_error("exit...");
  }
};

#endif  // MENU_H
