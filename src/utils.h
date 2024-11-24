#ifndef UTILS_H
#define UTILS_H

#include <X11/Xlib.h>

void draw_borders(Window win, int focused);
void focus_window(Window win);
Window get_window_under_cursor();

#endif 
