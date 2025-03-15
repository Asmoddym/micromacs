#include "editor.h"
#include "utils.h"
#include "navigate.h"
#include "window.h"
#include "io/file.h"

void process_layout_callback() {
  switch (E.ch) {
    case 'n':
      layout_create_new_window(FALSE);
      break;
    case 'N':
      layout_create_new_window(TRUE);
      break;
    case 'd':
      layout_destroy_current_window();
      break;
    case 'o':
      CW->file_buffer = io_create_file_buffer("./src/window.c");
      break;
     case KEY_LEFT:
      layout_navigate(NAVIGATION_LEFT);
      break;
    case KEY_RIGHT:
      layout_navigate(NAVIGATION_RIGHT);
      break;
    case KEY_UP:
      layout_navigate(NAVIGATION_UP);
      break;
    case KEY_DOWN:
      layout_navigate(NAVIGATION_DOWN);
      break;
  }

  E.mode = MODE_STANDARD;
}
