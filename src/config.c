#include "config.h"
#include "globals.h"
#include <X11/cursorfont.h>

Display *dpy = NULL;
Window root = 0;

void show_cursor() {
  Cursor cursor = XCreateFontCursor(dpy, XC_arrow);
  XDefineCursor(dpy, root, cursor);
  XFlush(dpy);
}

void init_display() {
  dpy = XOpenDisplay(NULL);
  if (!dpy) {
    fprintf(stderr, "Error: Unable to open display.\n");
    exit(EXIT_FAILURE);
  }
  root = DefaultRootWindow(dpy);
  XSelectInput(dpy, root, KeyPressMask | ButtonPressMask);
  show_cursor();
}
