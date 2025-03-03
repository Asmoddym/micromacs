#include <string.h>
#include <stdio.h>
#include "editor.h"

void message(const char *s) {
  static char str[MESSAGE_MAX_LENGTH];
  int s_len = s ? strlen(s) : 0;

  for (int i = 0; i < MESSAGE_MAX_LENGTH - 1; i++) {
    str[i] = i < s_len ? s[i] : ' ';
  }

  str[MESSAGE_MAX_LENGTH - 1] = 0;
  snprintf(E.message, MESSAGE_MAX_LENGTH, "%s", str);
}

int abs(int n) {
  return n < 0 ? -n : n;
}
