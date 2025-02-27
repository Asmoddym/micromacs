
/*   move(3, 3); */

  //  curs_set(0);
  /* raw(); */
  /* nonl(); */

/*   wbkgd(panel2->window, COLOR_PAIR(2)); */
/*   panel_border(panel2, 0); */

/*   wbkgd(panel->handle, COLOR_PAIR(1)); */
/*   panel_border(panel, 0); */


/*   char cc; */

/*   while ((cc = getch())) { */
/* //    clear(); */
/* //    wclear(panel->handle); */
/* //    wclear(panel2->window); */
/*     if (cc == 'q') break; */

/*     switch (cc) { */
/*     case 'a': */
/* //      panel_move(panel, 0, 1); */
/*       break; */
/*       case 'z': */
/*         panel_move(panel, 0, -1); */
/*     } */

/*     werase(panel->window); */
/*     wprintw(panel->window, "bla"); */
/*     /\* wnoutrefresh(panel2->panel); *\/ */

/*     /\* wprintw(panel->window, "coucou"); *\/ */
/*     /\* wnoutrefresh(panel->window); *\/ */

/*     refresh(); */
/*   } */
/* //  getch(); */

/*   panel_destroy(panel); */
/*   endwin(); */

/*   return 0; */

/*   /\* WINDOW *boite; *\/ */

/*   /\*   initscr(); *\/ */
/*   /\*   boite= subwin(stdscr, 10, 10, LINES / 2, COLS /2); *\/ */

/*   /\*   cbreak(); *\/ */
/*   /\*   noecho(); *\/ */


/*   /\*   box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut *\/ */
/*   /\*   refresh(); *\/ */

/*   /\*   getch(); *\/ */

/*   /\*   endwin(); *\/ */
/*   /\*   free(boite); *\/ */

/*   /\*   return 0; *\/ */

/*   WINDOW *boite; */


/*   initscr(); */
/*   start_color(); */
/*   init_pair(1, COLOR_BLUE, COLOR_RED); */
/*   init_pair(2, COLOR_BLUE, COLOR_GREEN); */

/*   int maxx, maxy; */
/*   getmaxyx(stdscr, maxy, maxx); */

/*   int sizex = maxx * 4/5; */
/*   int sizey = maxy * 4/5; */

/*  boite = subwin(stdscr, sizey, sizex, LINES / 2 - sizey / 2, COLS / 2 - sizex / 2); */


/*   FILE *file = fopen("src/main.c", "r"); */

/*   char **lines = malloc(sizeof(char *) * 1000); */

/*   int lines_number = 0; */

/*   size_t size = 0; */
/*   size_t read; */

/*   while ((read = getline(&lines[lines_number], &size, file)) != -1) { */
/*     lines[lines_number][read - 1] = 0; */
/*     lines_number++; */
/*   } */

/*   lines[lines_number] = NULL; */



/*   /\* while (fgets(buffer, sizeof(buffer), file)) { *\/ */
/*   /\*   lines[i] = strdup(buffer); *\/ */
/*   /\*   i++; *\/ */
/*   /\* } *\/ */

/*     fclose(file); */

/* //    wbkgd(boite, COLOR_PAIR(1)); */
/*     wattron(boite,COLOR_PAIR(2)); */
/*     wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+'); */

/*   wattroff(boite,COLOR_PAIR(2)); */
/*     wrefresh(boite); */

/* //    getch(); */

/*   /\*   return 0; *\/ */

/*   /\*   initscr(); *\/ */

/*   /\* printw("coucou"); *\/ */
/*   /\* refresh(); *\/ */
/*   raw(); */
/*   nonl(); */
/* keypad(stdscr, TRUE); */
/* char c; */

/* /\* for (int i = 0; i < 10; i++) { *\/ */
/* /\*     mvwprintw(boite, i, 0, "%s", lines[x + i]); *\/ */
/* /\*   } *\/ */

/* int cursorx = 3; */
/* int cursory = 40; */

/* while ((c = getch())) { */

/*   if (c == 'q') break; */
/* //        printw("\nkey: ctrl j "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(c)); */
/*   switch (c) { */
/*     case 2: */
/*       cursory = cursory == lines_number ? cursory : cursory + 1; */
/*       break; */
/*     case 3: */
/*       cursory = cursory == 1 ? 1 : cursory - 1; */
/*       break; */
/*     case 4: */
/*       cursorx = cursorx == 1 ? 1 : cursorx - 1; */
/*       break; */
/*     case 5: */
/*       cursorx = cursorx == sizex ? cursorx : cursorx + 1; */
/*       break; */
/* //      wprintw(boite, "\nkey: ctrl j "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(c)); */
/* //      wrefresh(boite); */
/*       break; */
/*     case 14: */
/*     default: */
/*       printw("\%d %s\n", c, keyname(c)); */

/*       if (c == 14 && cursory + 1 <= lines_number) { */
/*         int jump_down_of = cursory + 1; */

/*         while (lines[jump_down_of] != NULL && strlen(lines[jump_down_of]) != 0) { */
/*           jump_down_of++; */
/*         } */

/*         cursory = jump_down_of; */
/*       } */

/* //      lines[cursory][cursorx] = c; */
/* //        cursorx++; */
/*       break; */
/*   } */

/*   int offset = cursory - sizey + 2; */

/*   if (offset > 0) { */
/* //    clear(); */
/* //    wclear(boite); */
/*     mvwin(boite, 1, 2); */
/*     clear(); */
/*     refresh(); */
/*   //  refresh(); */
/*  //wrefresh(boite); */
/*     // */
/*   } */

/*       for (int i = 1; i < sizey - 1; i++) { */
/*         int line_idx = i + (offset > 0 ? offset : 0); */
/*         int len = strlen(lines[line_idx]); */

/*         mvwprintw(boite, i, 1, "%d|", line_idx); */
/*         for (int j = 0; j < sizex - 2 - 5; j++) { */
/*           unsigned char cc = j >= len ? ' ' : lines[line_idx][j]; */

/*           char cursor_on_x = cursorx == j; */
/*           char cursor_on_y = cursory - (offset > 0 ? offset : 0) == i; */

/*           unsigned int attributes = 0; */

/*           if (cursor_on_x && cursor_on_y) { */
/*             attributes |= COLOR_PAIR(1); */
/*             attributes |= A_BLINK; */
/*           } */

/*           mvwaddch(boite, i, 5 + j, (chtype)(cc | attributes)); */
/*         } */
/* //      printw("<%c>", lines[i + x][0]); */
/* //    mvwaddchstr(boite, i, 1, lines[i + x]); */
/*       } */
/*       wrefresh(boite); */
/* } */
/* delwin(boite); */
/* endwin(); */


/* return 0; */
//}
