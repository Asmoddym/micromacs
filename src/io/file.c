#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

int io_read_file(char ***ptr, const char *path) {
  FILE *file = fopen(path, "r");
  *ptr = malloc(sizeof(char **));
  *ptr[0] = NULL;

  int lines_number = 0;
  size_t size = 0;
  int read;

  while ((read = getline(&(*ptr)[lines_number], &size, file)) != -1) {
    (*ptr)[lines_number][read - 1] = 0;
    lines_number++;
    *ptr = realloc(*ptr, sizeof(char *) * (lines_number + 1));
    (*ptr)[lines_number] = NULL;
  }

  (*ptr)[lines_number] = NULL;
  fclose(file);

  return lines_number;
}

t_file_buffer *io_create_file_buffer(const char *path) {
  t_file_buffer *buffer = malloc(sizeof(t_file_buffer));

  buffer->file_data.path = strdup(path);
  buffer->lines_number = io_read_file(&buffer->lines, path);
  buffer->start_index = 0;

  return buffer;
}
