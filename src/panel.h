#ifndef PANEL_H_
# define PANEL_H_

# include <panel.h>
# include <ncurses.h>

typedef struct s_panel {
  WINDOW *window;
  PANEL *panel;
  int rows;
  int cols;
  int x;
  int y;
  int cursor_x;
  int cursor_y;
} t_panel;

typedef struct s_panel_data {
  char *title;
} t_panel_data;

t_panel_data *panel_create_data(const char *str);

t_panel *panel_create(int y, int x, int rows, int cols, const char *title);
void panel_destroy(t_panel *panel);

void panel_border(t_panel *panel, unsigned int attributes);
void panel_move(t_panel *panel, int offset_y, int offset_x);
void panel_show(t_panel *panel);

void panel_print_title(t_panel *panel, const char *string);
void panel_print(t_panel *panel, int y, int x, const char *string, chtype attributes);
void panel_resize(t_panel *panel, int new_width, int new_height);

#endif
