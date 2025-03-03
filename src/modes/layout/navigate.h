#ifndef LAYOUT_NAVIGATE_H_
# define LAYOUT_NAVIGATE_H_

enum e_navigation {
  NAVIGATION_UP,
  NAVIGATION_DOWN,
  NAVIGATION_LEFT,
  NAVIGATION_RIGHT,
};

void layout_navigate(enum e_navigation direction);

#endif
