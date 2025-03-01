#include "editor.h"
#include "utils.h"

void create_new_panel(char below) {
  t_panel *panel;

  if (E.panel_count == MAX_PANELS) {
    message("NOPE");

    return ;
  }

  if (E.panel_count == 0) {
    panel = panel_create(0, 0, E.height - 3, E.width, "coucou");

    panel->next = panel;
    panel->prev = panel;
  } else {
    int new_width = E.current_panel->cols / (below ? 1 : 2);
    int new_height = E.current_panel->rows / (below ? 2 : 1);
    int x, y;

    panel_resize(E.current_panel, new_width, new_height);

    x = E.current_panel->x + (below ? 0 : new_width);
    y = E.current_panel->y + (below ? new_height : 0);
    panel = panel_create(y, x, new_height, new_width, "bla");

    panel->next = E.panels[0];
    panel->prev = E.current_panel;

    E.panels[0]->prev = panel;
    E.current_panel->next = panel;
  }

  E.panels[E.panel_count] = panel;
  E.panel_count++;
  E.current_panel = panel;
}

void process_navigation_callback() {
  switch (E.ch) {
    case 'n':
      create_new_panel(FALSE);
      break;
    case 'N':
      create_new_panel(TRUE);
      break;
    case KEY_LEFT:
      E.current_panel = E.current_panel->prev;
      break;
    case KEY_RIGHT:
      E.current_panel = E.current_panel->prev;
      break;
  }

  E.mode = MODE_STANDARD;
}
