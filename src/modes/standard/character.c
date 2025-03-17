#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "editor.h"
#include "cursor.h"
#include "window.h"
#include "utils.h"

void remove_character_from_line(char **line, int c) {
  int line_len = strlen(*line);

  for (int i = CW->cursor_x - 1; i < line_len; i++) {
    (*line)[i] = (*line)[i + 1];
  }
  (*line)[line_len - 1] = 0;

  move_cursor(0, -1);
}

void append_character_to_line(char **line, int c) {
  int line_len = strlen(*line);
  int new_line_len = line_len + 2;

  // This is done for the future buffer reallocation (but it will surely change)
  if (new_line_len != line_len) {
    *line = realloc(*line, new_line_len);
  }

  for (int i = line_len; i > CW->cursor_x; i--) {
    (*line)[i] = (*line)[i - 1];
  }
  (*line)[CW->cursor_x] = c;
  (*line)[line_len + 1] = 0;

  move_cursor(0, 1);
}

int process_special_character(char **line, int c) {
  switch (c) {
    case KEY_BACKSPACE:
      remove_character_from_line(line, c);

      return 1;
    default:
        return 0;
  }
}

void process_character(int c) {
  char **line = &(CW->file_buffer->lines[window_current_line_index(CW)]);

  if (process_special_character(line, c)) return ;

  append_character_to_line(line, c);
}
