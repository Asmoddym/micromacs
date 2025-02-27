#include <curses.h>
#include <stdlib.h>
#include "panel.h"

t_panel *panel_create(int y, int x, int rows, int cols) {
  t_panel *panel = malloc(sizeof(t_panel));

  panel->handle = subwin(stdscr, rows, cols, y, x);
  panel->rows = rows;
  panel->cols = cols;
  panel->cursor_x = 0;
  panel->cursor_y = 0;
  wrefresh(panel->handle);

  return panel;
}

void panel_border(t_panel *panel, unsigned int attributes) {
  wattron(panel->handle, attributes);
  wborder(panel->handle, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(panel->handle, attributes);
}

void panel_destroy(t_panel *panel) {
  delwin(panel->handle);
  free(panel);
}
