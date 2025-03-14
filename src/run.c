#include "editor.h"
#include "io/file.h"
#include "utils.h"
#include "refresh.h"
#include "modes.h"
#include "modes/layout/layout.h"

void process_key() {
  static void (*mode_callbacks[MODE_COUNT])() = {
    process_standard_callback,
    process_layout_callback
  };

  mode_callbacks[E.mode]();
}

void run() {
  layout_create_new_window(FALSE);
  if (E.env.ac > 1) {
    CW->file_buffer = io_create_file_buffer(E.env.av[1]);
  }

  refresh_editor();

  while ((E.ch = getch())) {
    message(NULL);
    if (E.ch == 'q') break;

    switch (E.ch) {
      case 'x':
        E.mode = MODE_LAYOUT;
        message("LAYOUT MODE");
        break;
      default:
        process_key();
        break;
    }

    refresh_editor();
  }

  for (t_window **tmp = &(E.windows[0]); *tmp; tmp++) {
    window_destroy(*tmp);
  }
}
