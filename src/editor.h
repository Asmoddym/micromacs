#ifndef EDITOR_H_
# define EDITOR_H_

# include "window.h"

# define MAX_WINDOWS 8
# define MESSAGE_MAX_LENGTH 100

enum e_editor_mode {
  MODE_STANDARD,
  MODE_LAYOUT,
  MODE_COUNT
};

typedef struct s_env {
  int ac;
  char **av;
} t_env;

typedef struct s_editor {
  t_env env;

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

# define CW E.current_window

#endif
