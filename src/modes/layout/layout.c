#include "editor.h"
#include "utils.h"
#include "navigate.h"

void layout_create_new_window(char below) {
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

void layout_destroy_current_window() {
  t_window *current = E.current_window;
  int position = window_position(current);

  E.windows[position] = NULL;

  for (int i = position; i < MAX_WINDOWS - 1; i++) {
    E.windows[i] = E.windows[i + 1];
  }

  window_destroy(current);
}

void process_layout_callback() {
  switch (E.ch) {
    case 'n':
      layout_create_new_window(FALSE);
      break;
    case 'N':
      layout_create_new_window(TRUE);
      break;
    case 'd':
      layout_destroy_current_window();
      break;
     case KEY_LEFT:
      layout_navigate(NAVIGATION_LEFT);
      break;
    case KEY_RIGHT:
      layout_navigate(NAVIGATION_RIGHT);
      break;
    case KEY_UP:
      layout_navigate(NAVIGATION_UP);
      break;
    case KEY_DOWN:
      layout_navigate(NAVIGATION_DOWN);
      break;
  }

  E.mode = MODE_STANDARD;
}
