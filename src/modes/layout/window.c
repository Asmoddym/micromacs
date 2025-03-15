#include "editor.h"
#include "utils.h"

void layout_create_new_window(char below) {
  t_window *window;

  if (window_count() == MAX_WINDOWS) {
    message("NOPE");

    return ;
  }

  if (window_count() == 0) {
    window = window_create(0, 0, E.height - 3, E.width, "coucou");
  } else {
    int new_width = CW->cols / (below ? 1 : 2);
    int new_height = CW->rows / (below ? 2 : 1);
    int x, y;

    window_resize(CW, new_width, new_height);

    x = CW->x + (below ? 0 : new_width);
    y = CW->y + (below ? new_height : 0);

    char title[8];
    sprintf(title, "bla %d", window_count());
    window = window_create(y, x, new_height, new_width, title);
  }

  CW = window;
  E.windows[window_count()] = window;
}

void layout_destroy_current_window() {
  t_window *current = CW;
  int position = window_position(current);

  E.windows[position] = NULL;

  for (int i = position; i < MAX_WINDOWS - 1; i++) {
    E.windows[i] = E.windows[i + 1];
  }

  window_destroy(current);
}
