#include <stdio.h>
#include "editor.h"

void message(const char *s) {
  if (s == NULL) {
    for (int i = 0; i < MESSAGE_MAX_LENGTH - 1; i++) {
      E.message[i] = ' ';
    }
    E.message[MESSAGE_MAX_LENGTH - 1] = 0;
  } else {
    snprintf(E.message, MESSAGE_MAX_LENGTH, "%s", s);
  }
}
