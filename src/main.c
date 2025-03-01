#include "editor.h"
#include "run.h"

t_editor E;

void init_editor() {
  E.ui_bottom = window_create(LINES - 3, 0, 3, COLS, NULL);

  getmaxyx(stdscr, E.height, E.width);
  E.mode = MODE_STANDARD;
  for (int i = 0; i < MAX_WINDOWS; i++) {
    E.windows[i] = NULL;
  }
}

int main() {
  initscr();
  start_color();
  raw();
  keypad(stdscr, TRUE);
  meta(stdscr, FALSE);
  nonl();
  noecho();

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  init_editor();
  run();

  endwin();

  return 0;
}
