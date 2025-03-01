#include "editor.h"
#include "utils.h"

void navigation_create_new_window(char below) {
  t_window *window;

  if (E.window_count == MAX_WINDOWS) {
    message("NOPE");

    return ;
  }

  if (E.window_count == 0) {
    window = window_create(0, 0, E.height - 3, E.width, "coucou");

    window->next = window;
    window->prev = window;
  } else {
    int new_width = E.current_window->cols / (below ? 1 : 2);
    int new_height = E.current_window->rows / (below ? 2 : 1);
    int x, y;

    window_resize(E.current_window, new_width, new_height);

    x = E.current_window->x + (below ? 0 : new_width);
    y = E.current_window->y + (below ? new_height : 0);
    window = window_create(y, x, new_height, new_width, "bla");

    window->next = E.windows[0];
    window->prev = E.current_window;

    E.windows[0]->prev = window;
    E.current_window->next = window;
  }

  E.windows[E.window_count] = window;
  E.window_count++;
  E.current_window = window;
}

void process_navigation_callback() {
  switch (E.ch) {
    case 'n':
      navigation_create_new_window(FALSE);
      break;
    case 'N':
      navigation_create_new_window(TRUE);
      break;
    case KEY_LEFT:
      E.current_window = E.current_window->prev;
      break;
    case KEY_RIGHT:
      E.current_window = E.current_window->prev;
      break;
  }

  E.mode = MODE_STANDARD;
}
