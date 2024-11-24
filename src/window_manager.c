#include "window_manager.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>

extern Display *dpy;
extern Window root, win;
extern GC gc;
extern Atom wm_delete;

void handle_client_message(XEvent *event) {
    if ((long)event->xclient.data.l[0] == (long)wm_delete) {
        XDestroyWindow(dpy, event->xclient.window);
    }
}

void handle_events() {
    XEvent event;
    while (1) {
        XNextEvent(dpy, &event);
        if (event.type == ClientMessage) {
            handle_client_message(&event);
        }
    }
}

