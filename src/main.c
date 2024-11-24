#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xatom.h>
#include "globals.h"
#include "config.h"
#include "utils.h"
#include "window_manager.h"
#include <utils.h>

Display *dpy;
Window root, win;
GC gc;
Atom wm_delete;

int main() {
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);

    root = DefaultRootWindow(dpy);
    win = XCreateSimpleWindow(dpy, root, 100, 100, 800, 600, 0, 0, 0);

    XWindowAttributes win_attr;
    XGetWindowAttributes(dpy, win, &win_attr);

    XSetWindowBackgroundPixmap(dpy, win, None); 
    XClearWindow(dpy, win);

    gc = XCreateGC(dpy, win, 0, NULL);

    XSetForeground(dpy, gc, WhitePixel(dpy, DefaultScreen(dpy)));
    XFillRectangle(dpy, win, gc, 100, 100, 600, 400);
    XMapWindow(dpy, win);

    XFlush(dpy);

    launch();
    handle_events();
    kill_window(win);

    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}

