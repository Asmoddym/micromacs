#include "utils.h"
#include "editor.h"
#include "navigate.h"

char condition_to_navigate_left(t_window *candidate, t_window *item) {
  int tmp_end = item->x + item->cols;
  int candidate_end = candidate ? candidate->x + candidate->cols : 0;
  int candidate_y_delta = candidate ? abs(CW->y - candidate->y) : COLS;
  int tmp_y_delta = abs(CW->y - item->y);

  return tmp_end <= CW->x && tmp_end >= candidate_end && tmp_y_delta <= candidate_y_delta;
}

char condition_to_navigate_up(t_window *candidate, t_window *item) {
  int tmp_end = item->y + item->rows;
  int candidate_end = candidate ? candidate->y + candidate->rows : 0;
  int candidate_x_delta = candidate ? abs(CW->x - candidate->x) : LINES;
  int tmp_x_delta = abs(CW->x - item->x);

  return tmp_end <= CW->y && tmp_end >= candidate_end && tmp_x_delta <= candidate_x_delta;
}

char condition_to_navigate_right(t_window *candidate, t_window *item) {
  int tmp_end = item->x + item->cols;
  int candidate_end = candidate ? candidate->x + candidate->cols : COLS;
  int candidate_y_delta = candidate ? abs(CW->y - candidate->y) : COLS;
  int tmp_y_delta = abs(CW->y - item->y);

  return tmp_end > CW->x + CW->cols && tmp_end <= candidate_end && tmp_y_delta <= candidate_y_delta;
}

char condition_to_navigate_down(t_window *candidate, t_window *item) {
  int tmp_end = item->y + item->rows;
  int candidate_end = candidate ? candidate->y + candidate->rows : COLS;
  int candidate_x_delta = candidate ? abs(CW->x - candidate->x) : LINES;
  int tmp_x_delta = abs(CW->x - item->x);

  return tmp_end > CW->y + CW->rows && tmp_end <= candidate_end && tmp_x_delta <= candidate_x_delta;
}

void navigate_using_callback(char (*condition)(t_window *candidate, t_window *item)) {
  t_window *candidate = NULL;

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    if (condition(candidate, *tmp)) {
      candidate = *tmp;
    }
  }

  message(candidate ? window_get_title(candidate) : "No window candidate found");
  CW = candidate ? candidate : CW;
}

void layout_navigate(enum e_navigation direction) {
  switch (direction) {
    case NAVIGATION_UP:
      navigate_using_callback(condition_to_navigate_up);
      break;
    case NAVIGATION_DOWN:
      navigate_using_callback(condition_to_navigate_down);
      break;
    case NAVIGATION_LEFT:
      navigate_using_callback(condition_to_navigate_left);
      break;
    case NAVIGATION_RIGHT:
      navigate_using_callback(condition_to_navigate_right);
      break;
 }
}
