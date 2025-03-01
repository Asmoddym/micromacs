#ifndef EDITOR_H_
# define EDITOR_H_

# include "window.h"

# define MAX_WINDOWS 8
# define MESSAGE_MAX_LENGTH 100

enum e_editor_mode {
  MODE_STANDARD,
  MODE_NAVIGATION,
  MODE_COUNT
};

typedef struct s_editor {
  t_window *ui_bottom;

  t_window *windows[MAX_WINDOWS + 1];
  t_window *current_window;

  int height;
  int width;

  char message[MESSAGE_MAX_LENGTH];

  enum e_editor_mode mode;
  int ch;
} t_editor;

extern t_editor E;

#endif
