#include <stdio.h>
#include "editor.h"

void message(const char *s) {
  sprintf(E.message, "%s", s);
}
