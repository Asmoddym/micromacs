#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "window.h"

int relative_y(int y) {
  return y + WINDOW_MIN_Y;
}

int relative_x(int x) {
  return x + 1;
}

void move_y_cursor(t_window *win, int y_delta) {
  int rel_y = relative_y(win->cursor_y);

  // future cursor is in visible buffer
  if (win->cursor_y + y_delta >= 0 && rel_y + y_delta < WINDOW_MAX_Y(win)) {
    win->cursor_y += y_delta;

    return ;
  }

  if (y_delta == 1) {
    char cursor_would_be_below = rel_y + 1 == WINDOW_MAX_Y(win);
    char cursor_is_in_lines_number = win->file_buffer->start_index + WINDOW_MAX_Y(win) < win->file_buffer->lines_number;

    if (cursor_would_be_below && cursor_is_in_lines_number) {
      win->file_buffer->start_index += y_delta;
    }
  }

  if (y_delta == -1) {
    char cursor_would_be_above = rel_y == WINDOW_MIN_Y;

    if (cursor_would_be_above && win->file_buffer->start_index > 0) {
      win->file_buffer->start_index += y_delta;
    }
  }
}

void move_x_cursor(t_window *win, int x_delta) {
  char **lines = win->file_buffer->lines;
  int current_line_len = (int)strlen(lines[window_current_line_index(win)]);

  if (win->cursor_x + x_delta == -1 || (current_line_len == 0 && x_delta == -1)) {
    if (win->cursor_y - 1 >= 0) {
      move_y_cursor(win, -1);

      // recalculating len
      win->cursor_x = strlen(lines[window_current_line_index(win)]);
    }
  } else {
    win->cursor_x += x_delta;
  }

  if (win->cursor_x + x_delta == current_line_len + 2 || (current_line_len == 0 && x_delta == 1)) {
    move_y_cursor(win, 1);
    win->cursor_x = 0;
  }
}

void move_cursor(int y_delta, int x_delta) {
  if (y_delta != 0) {
    move_y_cursor(CW, y_delta);
  } else {
    move_x_cursor(CW, x_delta);
  }
}
