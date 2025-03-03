#include "editor.h"
#include "utils.h"
#include "refresh.h"
#include "modes.h"
#include "modes/navigation/navigation.h"

void process_key() {
  static void (*mode_callbacks[MODE_COUNT])() = {
    process_standard_callback,
    process_navigation_callback
  };

  mode_callbacks[E.mode]();
}

void run() {
  navigation_create_new_window(FALSE);
  refresh_editor();

  while ((E.ch = getch())) {
    message(NULL);
    if (E.ch == 'q') break;

    switch (E.ch) {
      case 'x':
        E.mode = MODE_NAVIGATION;
        message("NAVIGATION MODE");
        break;
      default:
        process_key();
        break;
    }

    refresh_editor();
  }

  for (int i = 0; i < MAX_WINDOWS; i++) {
    if (E.windows[i]) {
      window_destroy(E.windows[i]);
    }
  }
}
