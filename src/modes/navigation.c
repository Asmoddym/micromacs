#include "editor.h"
#include "utils.h"
#include "window.h"
#include <panel.h>

void navigation_create_new_window(char below) {
  t_window *window;

  if (window_count() == MAX_WINDOWS) {
    message("NOPE");

    return ;
  }

  if (window_count() == 0) {
    window = window_create(0, 0, E.height - 3, E.width, "coucou");
  } else {
    int new_width = E.current_window->cols / (below ? 1 : 2);
    int new_height = E.current_window->rows / (below ? 2 : 1);
    int x, y;

    window_resize(E.current_window, new_width, new_height);

    x = E.current_window->x + (below ? 0 : new_width);
    y = E.current_window->y + (below ? new_height : 0);

    char title[8];
    sprintf(title, "bla %d", window_count());
    window = window_create(y, x, new_height, new_width, title);
  }

  E.current_window = window;
  E.windows[window_count()] = window;
}

void navigation_destroy_current_window() {
  t_window *current = E.current_window;
  int position = window_position(current);

  E.windows[position] = NULL;

  for (int i = position; i < MAX_WINDOWS - 1; i++) {
    E.windows[i] = E.windows[i + 1];
  }

  window_destroy(current);
}

int abs(int n) {
  return n < 0 ? -n : n;
}

void navigation_go_to_left_window() {
  t_window *candidate = NULL;

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    int tmp_end = (*tmp)->x + (*tmp)->cols;
    int candidate_end = candidate ? candidate->x + candidate->cols : 0;
    int candidate_y_delta = candidate ? abs(E.current_window->y - candidate->y) : COLS;
    int tmp_y_delta = abs(E.current_window->y - (*tmp)->y);

    if (tmp_end <= E.current_window->x && tmp_end >= candidate_end && tmp_y_delta <= candidate_y_delta) {
      candidate = *tmp;
    }
  }

  E.current_window = candidate ? candidate : E.current_window;
}

void navigation_go_to_above_window() {
  t_window *candidate = NULL;

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    int tmp_end = (*tmp)->y + (*tmp)->rows;
    int candidate_end = candidate ? candidate->y + candidate->rows : 0;
    int candidate_x_delta = candidate ? abs(E.current_window->x - candidate->x) : LINES;
    int tmp_x_delta = abs(E.current_window->x - (*tmp)->x);

    if (tmp_end <= E.current_window->y && tmp_end >= candidate_end && tmp_x_delta <= candidate_x_delta) {
      candidate = *tmp;
    }
  }

  E.current_window = candidate ? candidate : E.current_window;
}

void navigation_go_to_right_window() {
  t_window *candidate = NULL;

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    int tmp_end = (*tmp)->x + (*tmp)->cols;
    int candidate_end = candidate ? candidate->x + candidate->cols : COLS;
    int candidate_y_delta = candidate ? abs(E.current_window->y - candidate->y) : COLS;
    int tmp_y_delta = abs(E.current_window->y - (*tmp)->y);

    if (tmp_end > E.current_window->x + E.current_window->cols && tmp_end <= candidate_end && tmp_y_delta <= candidate_y_delta) {
      candidate = *tmp;
    }
  }

  message(candidate ? window_get_title(candidate) : "nope");
  E.current_window = candidate ? candidate : E.current_window;
}

void navigation_go_to_below_window() {
  t_window *candidate = NULL;

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    int tmp_end = (*tmp)->y + (*tmp)->rows;
    int candidate_end = candidate ? candidate->y + candidate->rows : COLS;
    int candidate_x_delta = candidate ? abs(E.current_window->x - candidate->x) : LINES;
    int tmp_x_delta = abs(E.current_window->x - (*tmp)->x);

    if (tmp_end > E.current_window->y + E.current_window->rows && tmp_end <= candidate_end && tmp_x_delta <= candidate_x_delta) {
      candidate = *tmp;
    }
  }

  message(candidate ? window_get_title(candidate) : "nope");
  E.current_window = candidate ? candidate : E.current_window;}

void process_navigation_callback() {
  switch (E.ch) {
    case 'n':
      navigation_create_new_window(FALSE);
      break;
    case 'N':
      navigation_create_new_window(TRUE);
      break;
    case 'd':
      navigation_destroy_current_window();
      break;
    case KEY_LEFT:
      navigation_go_to_left_window();
      break;
    case KEY_RIGHT:
      navigation_go_to_right_window();
      break;
    case KEY_UP:
      navigation_go_to_above_window();
      break;
    case KEY_DOWN:
      navigation_go_to_below_window();
      break;
  }

  E.mode = MODE_STANDARD;
}
