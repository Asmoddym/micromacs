#include "editor.h"
#include "window.h"
#include "cursor.h"
#include "character.h"

void process_standard_callback() {
  if (!CW->file_buffer) {
    return;
  }

  switch (E.ch) {
    case KEY_UP:
      move_cursor(-1, 0);
      break;
    case KEY_DOWN:
      move_cursor(1, 0);
      break;
    case KEY_LEFT:
      move_cursor(0, -1);
      break;
    case KEY_RIGHT:
      move_cursor(0, 1);
      break;
    default:
      process_character(E.ch);
      break;
  }
}
