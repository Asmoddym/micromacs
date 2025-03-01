#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <window.h>
#include <stdlib.h>
#include "window.h"
#include "editor.h"

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

  set_panel_userptr(window->panel, window_create_data(title));

  return window;
}

void window_border(t_window *window, unsigned int attributes) {
  wattron(window->handle, attributes);
  wborder(window->handle, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(window->handle, attributes);
}

void window_destroy(t_window *window) {
  del_panel(window->panel);
  delwin(window->handle);

  free(window);
}

void window_move(t_window *window, int offset_y, int offset_x) {
  window->y += offset_y;
  window->x += offset_x;

  mvderwin(window->handle, window->y, window->x);
}

void window_show(t_window *window) {
  t_window_data *data = (t_window_data *)panel_userptr(window->panel);

  box(window->handle, 0, 0);

  mvwaddch(window->handle, 2, 0, ACS_LTEE);
  mvwhline(window->handle, 2, 1, ACS_HLINE, window->cols - 2);
  mvwaddch(window->handle, 2, window->cols - 1, ACS_RTEE);

  if (data->title) {
    window_print_title(window, data->title);
  }

}

void window_print_title(t_window *window, const char *string) {
  int x, y;
  char infos[8];
  unsigned int attributes = E.current_window == window ? A_STANDOUT : 0;

  x = window->cols / 2 - strlen(string) / 2;
  y = 1;

  mvwchgat(window->handle, 1, 1, window->cols - 2, attributes, 0, NULL);
  window_print(window, y, x, string, attributes);

  sprintf(infos, "%d,%d", window->rows, window->cols);
  window_print(window, y, window->cols - 8, infos, attributes);
}

void window_print(t_window *window, int y, int x, const char *string, chtype attributes) {
  WINDOW *win = window->handle;

  wattron(win, attributes);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, attributes);
}

void window_resize(t_window *window, int new_width, int new_height) {
  // Doesn't work, I don't know why
  //
  /* WINDOW *old_win = window_window(window->handle); */
  /* WINDOW *new_win = newwin(new_height, new_width, window->y, window->x); */

  /* window->cols = new_width; */
  /* window->rows = new_height; */

  /* replace_window(window->handle, new_win); */
  /* refresh(); */
  /* delwin(old_win); */

  clear();
  wclear(window->handle);
  wresize(window->handle, new_height, new_width);

  window->cols = new_width;
  window->rows = new_height;
}

int window_count() {
  int count = 0;

  for (int i = 0; i < MAX_WINDOWS; i++) {
    if (E.windows[i]) {
      count++;
    }
  }

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
