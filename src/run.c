#include "editor.h"
#include "utils.h"
#include "refresh.h"
#include "modes.h"
#include "modes/navigation.h"

void process_key() {
  static void (*mode_callbacks[MODE_COUNT])() = {
    process_standard_callback,
    process_navigation_callback
  };

  mode_callbacks[E.mode]();
}

void run() {
  navigation_create_new_panel(FALSE);
  refresh_editor();

  while ((E.ch = getch())) {
    message(NULL);
    if (E.ch == 'q') break;

    switch (E.ch) {
      case ctrl('x'):
        E.mode = MODE_NAVIGATION;
        message("NAVIGATION MODE");
        break;
      default:
        process_key();
        break;
    }

    refresh_editor();
  }

  for (int i = 0; i < E.panel_count; i++) {
    panel_destroy(E.panels[i]);
  }
}
