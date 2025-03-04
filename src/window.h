#ifndef WINDOW_H_
# define WINDOW_H_

# include <panel.h>
# include <ncurses.h>
# include "io/file.h"

typedef struct s_window {
  WINDOW *handle;
  PANEL *panel;
  int rows;
  int cols;
  int x;
  int y;
  int cursor_x;
  int cursor_y;

  t_file_buffer *file_buffer;
} t_window;

typedef struct s_window_data {
  char *title;
} t_window_data;

t_window_data *window_create_data(const char *str);
t_window_data *window_data(t_window *win);

t_window *window_create(int y, int x, int rows, int cols, const char *title);
void window_destroy(t_window *win);

void window_border(t_window *win, unsigned int attributes);
void window_move(t_window *win, int offset_y, int offset_x);
void window_show(t_window *win);

void window_print_cursor(t_window *win);
void window_print_title(t_window *win, const char *string);
void window_print_line(t_window *win, int y, int x, const char *string, chtype attributes);

void window_print_file_buffer(t_window *win);
void window_print_file_buffer_lines(t_window *win, char **lines);

void window_resize(t_window *win, int new_width, int new_height);

int window_count();
int window_position(t_window *window);

const char *window_get_title(t_window *win);

#endif
