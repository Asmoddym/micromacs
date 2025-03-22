#include "editor.h"
#include "file.h"
#include "modes/standard/character.h"
#include "utils.h"
#include "refresh.h"
#include "modes.h"
#include "modes/layout/layout.h"

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void process_key() {
  static void (*mode_callbacks[MODE_COUNT])() = {
    process_standard_callback,
    process_layout_callback
  };

  mode_callbacks[E.mode]();
}

int get_key() {
  static int fd = STDIN_FILENO;

  int nread;
  char c, seq[3];
  while ((nread = read(fd,&c,1)) == 0);
  if (nread == -1) exit(1);

//  while(1) {
    switch(c) {
      case ESC:    /* escape sequence */
        /* If this is just an ESC, we'll timeout here. */
        if (read(fd,seq,1) == 0) return ESC;
        if (read(fd,seq+1,1) == 0) return ESC;

        /* ESC [ sequences. */
        if (seq[0] == '[') {
          if (seq[1] >= '0' && seq[1] <= '9') {
            /* Extended escape, read additional byte. */
            if (read(fd,seq+2,1) == 0) return ESC;
            if (seq[2] == '~') {
              switch(seq[1]) {
                case '3': return DEL_KEY;
                case '5': return PAGE_UP;
                case '6': return PAGE_DOWN;
              }
            }
          } else {
            switch(seq[1]) {
              case 'A': return ARROW_UP;
              case 'B': return ARROW_DOWN;
              case 'C': return ARROW_RIGHT;
              case 'D': return ARROW_LEFT;
              case 'H': return HOME_KEY;
              case 'F': return END_KEY;
            }
          }
        }

        /* ESC O sequences. */
        else if (seq[0] == 'O') {
          switch(seq[1]) {
            case 'H': return HOME_KEY;
            case 'F': return END_KEY;
          }
        }
        break;
      default:
        return c;
    }
  }
//}

void run() {
  layout_create_new_window(FALSE);
  if (E.env.ac > 1) {
    CW->file_buffer = file_create_file_buffer(E.env.av[1]);
  }

  refresh_editor();

  while ((E.ch = getch())) { //get_key())) {
    message(NULL);

    if (E.ch == -1 || E.ch == 'q') break;

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

  window_destroy(E.ui_bottom);
}
