#include "character.h"
#include "editor.h"
#include "window.h"

void process_character(unsigned char c) {
  CW->file_buffer->lines[CW->cursor_y][CW->cursor_x] = c;
}
