#include "editor.h"
#include "utils.h"
#include <curses.h>
#include "refresh.h"

void create_new_panel(char below) {
  t_panel *panel;

  if (E.panel_count == MAX_PANELS) {
    message("NOPE");

    return ;
  }

  if (E.panel_count == 0) {
    panel = panel_create(0, 0, E.height - 3, E.width, "coucou");
  } else {
    int new_width = E.current_panel->cols / (below ? 1 : 2);
    int new_height = E.current_panel->rows / (below ? 2 : 1);
    int x, y;

    panel_resize(E.current_panel, new_width, new_height);

    x = E.current_panel->x + (below ? 0 : new_width);
    y = E.current_panel->y + (below ? new_height : 0);
    panel = panel_create(y, x, new_height, new_width, "bla");
  }

  E.panels[E.panel_count] = panel;
  E.panel_count++;
  E.current_panel = panel;
}

void run() {
  create_new_panel(FALSE);
  refresh_editor();

  while ((E.ch = getch())) {
    if (E.ch == 'q') break;

    switch (E.ch) {
      case 49: //ctrl arrow right
        create_new_panel(FALSE);
        break;
      case 14: // ctrl arrow down
        create_new_panel(TRUE);
    }

    refresh_editor();
  }

  for (int i = 0; i < E.panel_count; i++) {
    panel_destroy(E.panels[i]);
  }
}
