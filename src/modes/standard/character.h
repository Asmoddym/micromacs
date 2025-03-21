#ifndef MODES_STANDARD_CHARACTER_H_
# define MODES_STANDARD_CHARACTER_H_

// Shamefully stolen from antirez's kilo

enum e_additional_keys {
KEY_NULL = 0,       /* NULL */
CTRL_C = 3,         /* Ctrl-c */
CTRL_D = 4,         /* Ctrl-d */
CTRL_F = 6,         /* Ctrl-f */
CTRL_H = 8,         /* Ctrl-h */
TAB = 9,            /* Tab */
CTRL_L = 12,        /* Ctrl+l */
ENTER = 13,         /* Enter */
CTRL_Q = 17,        /* Ctrl-q */
CTRL_S = 19,        /* Ctrl-s */
CTRL_U = 21,        /* Ctrl-u */
ESC = 27,           /* Escape */
BACKSPACE =  127,   /* Backspace */
};

void process_character(int c);

#endif
