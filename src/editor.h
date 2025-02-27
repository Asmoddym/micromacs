#ifndef EDITOR_H_
# define EDITOR_H_

# include "panel.h"

# define MAX_PANELS 8

typedef struct s_editor {
  t_panel *ui_bottom;

  t_panel *panels[MAX_PANELS];
  t_panel *current_panel;
  int panel_count;

  int height;
  int width;

  char message[256];

  char ch;
} t_editor;

extern t_editor E;

#endif
