#ifndef MODES_STANDARD_CURSOR_H_
# define MODES_STANDARD_CURSOR_H_

# include "window.h"

void move_cursor(int y_delta, int x_delta);

void move_x_cursor(t_window *win, int x_delta);
void move_y_cursor(t_window *win, int y_delta);

#endif
