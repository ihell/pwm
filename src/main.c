#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "globals.h"
#include "config.h"
#include "window_manager.h"

Display *dpy;
Window root;
Window win;
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
    win = XCreateSimpleWindow(dpy, root, 0, 0, 800, 600, 0, 0, 0);
    gc = XCreateGC(dpy, win, 0, NULL);
    XMapWindow(dpy, win);

    launch();

    handle_events();

    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}

