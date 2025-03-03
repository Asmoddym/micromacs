#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

char **io_read_file(const char *path) {
  FILE *file = fopen(path, "r");
  char **lines = malloc(sizeof(char **));
  lines[0] = NULL;

  int lines_number = 0;
  size_t size = 0;
  int read;

  while ((read = getline(&lines[lines_number], &size, file)) != -1) {
    lines[lines_number][read - 1] = 0;
    lines_number++;
    lines = realloc(lines, sizeof(char *) * (lines_number + 1));
    lines[lines_number] = NULL;
  }

  lines[lines_number] = NULL;
  fclose(file);

  return lines;
}

t_file_buffer *io_create_file_buffer(const char *path) {
  t_file_buffer *buffer = malloc(sizeof(t_file_buffer));

  buffer->file_data.path = strdup(path);
  buffer->lines = io_read_file(path);

  return buffer;
}
