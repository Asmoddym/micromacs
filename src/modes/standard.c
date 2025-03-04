#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "io/file.h"
#include "window.h"

void move_cursor(int y_delta, int x_delta) {
  t_window *win = E.current_window;

  // future cursor is in visible buffer
  if (win->cursor_y + y_delta >= WINDOW_HEADER_ROWS && win->cursor_y + y_delta < WINDOW_MAX_Y(win)) {
    win->cursor_y += y_delta;

    return ;
  }

  if (y_delta == 1) {
    char cursor_would_be_below = win->cursor_y + 1 == WINDOW_MAX_Y(win);
    char cursor_is_in_lines_number = win->file_buffer->start_index + WINDOW_MAX_Y(win) < win->file_buffer->lines_number;

    if (cursor_would_be_below && cursor_is_in_lines_number) {
      win->file_buffer->start_index += y_delta;
    }
  }

  if (y_delta == -1) {
    char cursor_would_be_above = win->cursor_y == WINDOW_MIN_Y;

    if (cursor_would_be_above && win->file_buffer->start_index > 0) {
      win->file_buffer->start_index += y_delta;
    }
  }
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
