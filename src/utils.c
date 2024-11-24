#include "utils.h"
#include "globals.h"
#include "config.h"

void draw_borders(Window win, int focused) {
    XSetWindowBorderWidth(dpy, win, BORDER_WIDTH);
    XSetWindowBorder(dpy, win, focused ? FOCUS_COLOR : UNFOCUS_COLOR);
}

void focus_window(Window win) {
    if (win == None) {
        return;
    }

    XRaiseWindow(dpy, win);
    XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
    XFlush(dpy);
}



Window get_window_under_cursor() {
    Window ret_win = None, child_win;
    int x, y;
    unsigned int mask;

    if (XQueryPointer(dpy, root, &ret_win, &child_win, &x, &y, &x, &y, &mask)) {
        return child_win;
    }
    return None;
}

