#ifndef FILE_H_
# define FILE_H_

typedef struct s_file_data {
  char *path;
} t_file_data;

typedef struct s_file_buffer {
  t_file_data file_data;
  char **lines;
  int lines_number;
  int start_index;
} t_file_buffer;

t_file_buffer *file_create_file_buffer(const char *path);

void file_destroy_file_buffer(t_file_buffer *b);

#endif
