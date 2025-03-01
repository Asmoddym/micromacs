#include "utils.h"
#include "editor.h"

void redraw_windows() {
  for (int i = 0; i < MAX_WINDOWS; i++) {
    if (E.windows[i]) {
      window_show(E.windows[i]);
    }
  }
}

void redraw_ui() {
  box(E.ui_bottom->handle, 0, 0);

  mvwprintw(E.ui_bottom->handle, 1, 2, "%s", E.message);
  mvwprintw(E.ui_bottom->handle, 1, E.ui_bottom->cols - 40, "Last key: %d (%s) "BYTE_TO_BINARY_PATTERN, E.ch, keyname(E.ch), BYTE_TO_BINARY(E.ch));
}

void refresh_editor() {
  redraw_ui();
  redraw_windows();

  // ncurses/libpanel calls
  refresh();
  update_panels();
  doupdate();
}
