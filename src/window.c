#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <window.h>
#include <stdlib.h>
#include "window.h"
#include "editor.h"
#include "utils.h"
#include "file.h"

t_window_data *window_create_data(const char *title) {
  t_window_data *data = malloc(sizeof(t_window_data));

  data->title = title ? strdup(title) : NULL;

  return data;
}

t_window_data *window_data(t_window *win) {
  return (t_window_data *)panel_userptr(win->panel);
}

t_window *window_create(int y, int x, int rows, int cols, const char *title) {
  t_window *window = malloc(sizeof(t_window));

  window->handle = newwin(rows, cols, y, x);
  window->panel = new_panel(window->handle);
  window->rows = rows;
  window->cols = cols;
  window->x = x;
  window->y = y;
  window->cursor_x = 0;
  window->cursor_y = 0;
  window->file_buffer = NULL;

  set_panel_userptr(window->panel, window_create_data(title));

  return window;
}

void window_border(t_window *window, unsigned int attributes) {
  wattron(window->handle, attributes);
  wborder(window->handle, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(window->handle, attributes);
}

void window_destroy(t_window *window) {
  t_window_data *data = window_data(window);

  del_panel(window->panel);
  delwin(window->handle);

  if (window->file_buffer) {
    file_destroy_file_buffer(window->file_buffer);
  }

  free(data->title);
  free(data);

  free(window);
}

void window_move(t_window *window, int offset_y, int offset_x) {
  window->y += offset_y;
  window->x += offset_x;

  mvderwin(window->handle, window->y, window->x);
}

void window_show(t_window *window) {
  t_window_data *data = (t_window_data *)panel_userptr(window->panel);

  if (window->file_buffer) {
    window_print_file_buffer(window);
  }

  box(window->handle, 0, 0);

  mvwaddch(window->handle, 2, 0, ACS_LTEE);
  mvwhline(window->handle, 2, 1, ACS_HLINE, window->cols - 2);
  mvwaddch(window->handle, 2, window->cols - 1, ACS_RTEE);

  if (data->title) {
    window_print_title(window, data->title);
  }
}

void window_print_file_buffer(t_window *window) {
   window_print_file_buffer_lines(window, window->file_buffer->lines);
}

void window_print_file_buffer_lines(t_window *window, char **lines) {
  int tmp_y, tmp_x;

  getyx(window->handle, tmp_y, tmp_x);

  for (int idx_y = 0; idx_y < window->rows - WINDOW_HEADER_ROWS - WINDOW_FOOTER_ROWS; idx_y++) {
    int idx_lines = window->file_buffer->start_index + idx_y;
    int len = strlen(lines[idx_lines]);

    wmove(window->handle, idx_y + WINDOW_MIN_Y, 0);

    for (int idx_x = 0; idx_x < window->cols - 1; idx_x++) {
      unsigned int c = idx_x >= len ? ' ' : lines[idx_lines][idx_x];
      unsigned int attributes = 0;
      int cursor_x = idx_x + 1;
      int cursor_y = idx_y + WINDOW_MIN_Y;

      if (CW == window && window->cursor_x == idx_x && window->cursor_y == idx_y) {
        attributes |= A_STANDOUT;

        if (len == 0) {
          cursor_x = 1;
        }
      }

      mvwaddch(window->handle, cursor_y, cursor_x, (chtype)(c | attributes));
    }
  }

  move(tmp_y, tmp_x);
}

void window_print_title(t_window *window, const char *string) {
  int x, y;
  char infos[20];
  unsigned int attributes = CW == window ? A_STANDOUT : 0;

  x = window->cols / 2 - strlen(string) / 2;
  y = 1;

  mvwchgat(window->handle, 1, 1, window->cols - 2, attributes, 0, NULL);
  window_print_line(window, y, x, string, attributes);

  sprintf(infos, "%d,%d (%d,%d)", window->rows, window->cols, window->cursor_y, window->cursor_x);
  window_print_line(window, y, window->cols - 16, infos, attributes);
}

void window_print_line(t_window *window, int y, int x, const char *string, chtype attributes) {
  WINDOW *win = window->handle;

  wattron(win, attributes);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, attributes);
}

void window_resize(t_window *window, int new_width, int new_height) {
  clear();
  wclear(window->handle);
  wresize(window->handle, new_height, new_width);

  window->cols = new_width;
  window->rows = new_height;
}

int window_count() {
  int count = 0;

  for (; count < MAX_WINDOWS && E.windows[count]; count++);

  return count;
}

int window_position(t_window *win) {
  for (int i = 0; i < MAX_WINDOWS; i++) {
    if (E.windows[i] == win) {
      return i;
    }
  }

  return -1;
}

const char *window_get_title(t_window *win) {
  return window_data(win)->title;
}


int window_current_line_index(t_window *win) {
  return win->file_buffer->start_index + win->cursor_y;
}
