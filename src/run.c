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

    E.current_panel->right_panel = below ? NULL : panel;
    E.current_panel->bottom_panel = below ? panel : NULL;
    panel->top_panel = below ? E.current_panel : NULL;
    panel->left_panel = below ? NULL : E.current_panel;
  }

  E.panels[E.panel_count] = panel;
  E.panel_count++;
  E.current_panel = panel;
}

void run() {
  create_new_panel(FALSE);
  refresh_editor();

  while ((E.ch = getch())) {
    message(NULL);
    if (E.ch == 'q') break;

    switch (E.ch) {
      case ctrl('x'):
        E.mode = MODE_X;
        message("X MODE");
        break;

      case KEY_RIGHT:
        if (E.mode == MODE_X) {
          if (E.current_panel->right_panel) {
            E.current_panel = E.current_panel->right_panel;
          }
          E.mode = MODE_NONE;
        } else {
          create_new_panel(FALSE);
        }
        break;
      case KEY_DOWN:
        if (E.mode == MODE_X) {
          if (E.current_panel->bottom_panel) {
            E.current_panel = E.current_panel->bottom_panel;
          }
          E.mode = MODE_NONE;
        } else {
          create_new_panel(TRUE);
        }
        break;
      case KEY_UP:
        if (E.mode == MODE_X) {
          message("OK");
          if (E.current_panel->top_panel) {
            E.current_panel = E.current_panel->top_panel;
          }
          E.mode = MODE_NONE;
        }
        break;
      case KEY_LEFT:
        if (E.mode == MODE_X) {
          if (E.current_panel->left_panel) {
            E.current_panel = E.current_panel->left_panel;
          }
          E.mode = MODE_NONE;
        }
        break;
    }

    refresh_editor();
  }

  for (int i = 0; i < E.panel_count; i++) {
    panel_destroy(E.panels[i]);
  }
}
