#include <chrono>
#include <iostream>
#include <thread>

#include "load.h"
#include "terminal_gui.h"

int main(int argc, char** argv) {
  // drawing_board::get_instance()->draw("123");
  // drawing_board::get_instance()->draw("321");
  //
  // drawing_board::get_instance()->draw_ln("456");
  // drawing_board::get_instance()->draw_done();
  // getchar();
  clear_screen();
  using namespace std;
  for (int i = 1; i <= 100; ++i) {
    displayLoadingBar(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep for 100 milliseconds (0.1 seconds)
  }
  std::cout << std::endl;

  terminal_gui terminal;
  terminal.start();

  return 0;
}
