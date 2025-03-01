#ifndef EDITOR_H_
# define EDITOR_H_

# include "panel.h"

# define MAX_PANELS 8
# define MESSAGE_MAX_LENGTH 100

enum e_editor_mode {
  MODE_STANDARD,
  MODE_NAVIGATION,
  MODE_COUNT
};

typedef struct s_editor {
  t_panel *ui_bottom;

  t_panel *panels[MAX_PANELS];
  t_panel *current_panel;
  int panel_count;

  int height;
  int width;

  char message[MESSAGE_MAX_LENGTH];

  enum e_editor_mode mode;
  int ch;
} t_editor;

extern t_editor E;

#endif
