
#include "utils.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>

void kill_window(Display *dpy, Window window) {
    XEvent ev;
    ev.xclient.type = ClientMessage;
    ev.xclient.message_type = XInternAtom(dpy, "WM_PROTOCOLS", False);
    ev.xclient.display = dpy;
    ev.xclient.window = window;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    ev.xclient.data.l[1] = CurrentTime;

    XSendEvent(dpy, window, False, NoEventMask, &ev);
    XFlush(dpy);
}

void handle_events(Display *dpy, Window win) {
    XEvent ev;
    while (1) {
        XNextEvent(dpy, &ev);
        
        if (ev.type == KeyPress) {
            if (ev.xkey.keycode == XKeysymToKeycode(dpy, XK_q) && (ev.xkey.state & Mod4Mask)) {
                kill_window(dpy, win);
                break;
            }
        }
    }
}

