#include "character.h"
#include "editor.h"
#include "window.h"

void process_character(unsigned char c) {
  CW->file_buffer->lines[window_current_line_index(CW)][CW->cursor_x] = c;
}
