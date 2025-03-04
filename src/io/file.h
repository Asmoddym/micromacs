#ifndef IO_FILE_H_
# define IO_FILE_H_

typedef struct s_file_data {
  char *path;
} t_file_data;

typedef struct s_file_buffer {
  t_file_data file_data;
  char **lines;
  int lines_number;
  int start_index;
} t_file_buffer;

t_file_buffer *io_create_file_buffer(const char *path);

#endif
