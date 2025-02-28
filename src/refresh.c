#include "utils.h"
#include "editor.h"

void redraw_panels() {
  for (int i = 0; i < E.panel_count; i++) {
    panel_show(E.panels[i]);
  }

  update_panels();
  doupdate();
}

void redraw_ui() {
  box(E.ui_bottom->window, 0, 0);

  mvwprintw(E.ui_bottom->window, 1, 2, "%s", E.message);
  mvwprintw(E.ui_bottom->window, 1, E.ui_bottom->cols - 40, "Last key: %d (%s) "BYTE_TO_BINARY_PATTERN, E.ch, keyname(E.ch), BYTE_TO_BINARY(E.ch));
}

void refresh_editor() {
  redraw_ui();
  redraw_panels();

  refresh();
  update_panels();
  doupdate();
}
