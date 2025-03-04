#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "io/file.h"

void move_cursor(int y_delta, int x_delta) {
  E.current_window->cursor_x += x_delta;
  E.current_window->cursor_y += y_delta;
}

void process_standard_callback() {
  switch (E.ch) {
    case 'o':
      E.current_window->file_buffer = io_create_file_buffer("./src/window.c");
      break;
    case KEY_UP:
      move_cursor(-1, 0);
      break;
    case KEY_DOWN:
      move_cursor(1, 0);
      break;
    case KEY_LEFT:
      move_cursor(0, -1);
      break;
    case KEY_RIGHT:
      move_cursor(0, 1);
      break;
  }
}
