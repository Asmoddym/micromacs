#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "io/file.h"

void process_standard_callback() {
  switch (E.ch) {
    case 'o':
      E.current_window->file_buffer = io_create_file_buffer("./src/window.c");
      break;
  }
}
