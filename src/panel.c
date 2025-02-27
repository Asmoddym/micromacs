#include <curses.h>
#include <stdlib.h>
#include "panel.h"

t_panel *panel_create(int y, int x, int rows, int cols) {
  t_panel *panel = malloc(sizeof(t_panel));

  panel->handle = derwin(stdscr, rows, cols, y, x);
  panel->rows = rows;
  panel->cols = cols;
  panel->x = x;
  panel->y = y;
  panel->cursor_x = 0;
  panel->cursor_y = 0;

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

void panel_move(t_panel *panel, int offset_y, int offset_x) {
  panel->y += offset_y;
  panel->x += offset_x;

 mvderwin(panel->handle, panel->y, panel->x);
}
