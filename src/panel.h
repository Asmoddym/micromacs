#ifndef PANEL_H_
# define PANEL_H_

# include <ncurses.h>

typedef struct s_panel {
  WINDOW *handle;
  int rows;
  int cols;
  int x;
  int y;
  int cursor_x;
  int cursor_y;
} t_panel;

t_panel *panel_create(int y, int x, int rows, int cols);
void panel_border(t_panel *panel, unsigned int attributes);
void panel_destroy(t_panel *panel);
void panel_move(t_panel *panel, int offset_y, int offset_x);

#endif
