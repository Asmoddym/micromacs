#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "editor.h"
#include "cursor.h"
#include "utils.h"

void append_character_to_line(char **line, int x, int c) {
  int line_len = strlen(*line);
  int new_line_len = line_len + 2;

  // This is done for the future buffer reallocation (but it will surely change)
  if (new_line_len != line_len) {
    *line = realloc(*line, new_line_len);
  }

  for (int i = line_len; i > x; i--) {
    (*line)[i] = (*line)[i - 1];
  }
  (*line)[x] = c;
  (*line)[line_len + 1] = 0;

  move_x_cursor(CW, 1);
}

void concat_line_with_previous(char **line) {
  int line_len = strlen(*line);
  char **previous_line = &(CW->file_buffer->lines[window_current_line_index(CW) - 1]);
  int previous_line_len = strlen(*previous_line);

  for (int x = 0; x < line_len; x++) {
    append_character_to_line(previous_line, previous_line_len + x, (*line)[x]);
  }

  for (int y = window_current_line_index(CW); y < CW->file_buffer->lines_number; y++) {
    CW->file_buffer->lines[y] = CW->file_buffer->lines[y + 1];
  }
  CW->file_buffer->lines_number--;

  move_y_cursor(CW, -1);
  CW->cursor_x = previous_line_len;
}

void remove_character_from_line(char **line) {
  int line_len = strlen(*line);

  if (CW->cursor_x > 0) {
    move_x_cursor(CW, -1);

    for (int i = CW->cursor_x; i < line_len; i++) {
      (*line)[i] = (*line)[i + 1];
    }
    (*line)[line_len - 1] = 0;
  } else {
    if (CW->cursor_y > 0) {
      concat_line_with_previous(line);
    }
  }
}

int process_special_character(char **line, int c) {
  switch (c) {
    case KEY_BACKSPACE:
      remove_character_from_line(line);
      break;
    default:
      return 0;
  }

  return 1;
}

void process_character(int c) {
  char **line = &(CW->file_buffer->lines[window_current_line_index(CW)]);

  if (process_special_character(line, c)) return ;

  append_character_to_line(line, CW->cursor_x, c);
}
