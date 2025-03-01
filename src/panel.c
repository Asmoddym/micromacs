#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <panel.h>
#include <stdlib.h>
#include "panel.h"
#include "editor.h"

t_panel_data *panel_create_data(const char *title) {
  t_panel_data *data = malloc(sizeof(t_panel_data));

  data->title = title ? strdup(title) : NULL;

  return data;
}

t_panel *panel_create(int y, int x, int rows, int cols, const char *title) {
  t_panel *panel = malloc(sizeof(t_panel));

  panel->window = newwin(rows, cols, y, x);
  panel->panel = new_panel(panel->window);
  panel->rows = rows;
  panel->cols = cols;
  panel->x = x;
  panel->y = y;
  panel->cursor_x = 0;
  panel->cursor_y = 0;
  panel->next = NULL;
  panel->prev = NULL;

  set_panel_userptr(panel->panel, panel_create_data(title));

  return panel;
}

void panel_border(t_panel *panel, unsigned int attributes) {
  wattron(panel->window, attributes);
  wborder(panel->window, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(panel->window, attributes);
}

void panel_destroy(t_panel *panel) {
  del_panel(panel->panel);
  delwin(panel->window);

  free(panel);
}

void panel_move(t_panel *panel, int offset_y, int offset_x) {
  panel->y += offset_y;
  panel->x += offset_x;

  mvderwin(panel->window, panel->y, panel->x);
}

void panel_show(t_panel *panel) {
  t_panel_data *data = (t_panel_data *)panel_userptr(panel->panel);

  box(panel->window, 0, 0);

  mvwaddch(panel->window, 2, 0, ACS_LTEE);
  mvwhline(panel->window, 2, 1, ACS_HLINE, panel->cols - 2);
  mvwaddch(panel->window, 2, panel->cols - 1, ACS_RTEE);

  if (data->title) {
    panel_print_title(panel, data->title);
  }

}

void panel_print_title(t_panel *panel, const char *string) {
  int x, y;
  char infos[8];
  unsigned int attributes = E.current_panel == panel ? A_STANDOUT : 0;

  x = panel->cols / 2 - strlen(string) / 2;
  y = 1;

  mvwchgat(panel->window, 1, 1, panel->cols - 2, attributes, 0, NULL);
  panel_print(panel, y, x, string, attributes);

  sprintf(infos, "%d,%d", panel->rows, panel->cols);
  panel_print(panel, y, panel->cols - 8, infos, attributes);
}

void panel_print(t_panel *panel, int y, int x, const char *string, chtype attributes) {
  WINDOW *win = panel->window;

  wattron(win, attributes);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, attributes);
}

void panel_resize(t_panel *panel, int new_width, int new_height) {
  // Doesn't work, I don't know why
  //
  /* WINDOW *old_win = panel_window(panel->panel); */
  /* WINDOW *new_win = newwin(new_height, new_width, panel->y, panel->x); */

  /* panel->cols = new_width; */
  /* panel->rows = new_height; */

  /* replace_panel(panel->panel, new_win); */
  /* refresh(); */
  /* delwin(old_win); */

  clear();
  wclear(panel->window);
  wresize(panel->window, new_height, new_width);

  panel->cols = new_width;
  panel->rows = new_height;
}
