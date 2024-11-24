#include "window_manager.h"
#include "globals.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <unistd.h>

Window get_new_window() {
    Window root_return, parent_return;
    Window *children_return;
    unsigned int nchildren;

    XQueryTree(dpy, root, &root_return, &parent_return, &children_return, &nchildren);
    Window new_window = None;

    usleep(500000);

    for (unsigned int i = 0; i < nchildren; i++) {
        char *name = NULL;
        XFetchName(dpy, children_return[i], &name);

        if (name != NULL) {
            new_window = children_return[i];
            XFree(name);
            break;
        }
        XFree(name);
    }

    XFree(children_return);
    return new_window;
}

Window get_window_by_name(const char *window_name) {
    Window root_return, parent_return;
    Window *children_return;
    unsigned int nchildren;
    XQueryTree(dpy, root, &root_return, &parent_return, &children_return, &nchildren);
    Window target_window = None;

    for (unsigned int i = 0; i < nchildren; i++) {
        char *name = NULL;
        XFetchName(dpy, children_return[i], &name);

        if (name != NULL) {
            if (strcmp(name, window_name) == 0) {
                target_window = children_return[i];
                XFree(name);
                break;
            }
            XFree(name);
        }
    }

    XFree(children_return);
    return target_window;
}

void handle_key_press(XKeyEvent *ev) {
    if (ev->state & MOD4_MASK) {
        if (ev->keycode == XKeysymToKeycode(dpy, XK_q)) {
            XCloseDisplay(dpy);
            exit(0);
        }
    }

    if (ev->state & MOD1_MASK) {
        if (ev->keycode == XKeysymToKeycode(dpy, XK_Return)) {
            system("alacritty &");

            usleep(500000);

            Window alacritty_window = get_window_by_name("Alacritty");
            if (alacritty_window != None) {
                focus_window(alacritty_window);
            } else {
                printf("Failed to find Alacritty window\n");
            }
        }

        if (ev->keycode == XKeysymToKeycode(dpy, XK_m)) {
            system("dmenu_run &");

            usleep(500000);

            Window dmenu_window = get_new_window();
            if (dmenu_window != None) {
                focus_window(dmenu_window);
            } else {
                printf("Failed to find a valid window for dmenu\n");
            }
        }
    }
}

