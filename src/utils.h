#ifndef UTILS_H_
# define UTILS_H_

# define ctrl(x) ((x) & 0x1f)
# define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
# define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
    ((byte) & 0x01 ? '1' : '0')

void message(const char *s);

#endif
