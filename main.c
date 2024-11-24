#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Display *dpy;
Window root;
Window win;
GC gc;

void handle_keypress(XEvent *e) {
    XKeyEvent *kevent = &e->xkey;
    KeySym key = XkbKeycodeToKeysym(dpy, kevent->keycode, 0, 0);

    // Cek apakah ALT + ENTER ditekan
    if ((kevent->state & Mod1Mask) && key == XK_Return) {
        // Jika ALT + ENTER, jalankan perintah untuk membuka Alacritty
        printf("ALT + ENTER pressed, launching Alacritty...\n");

        // Fork dan exec untuk membuka Alacritty
        if (fork() == 0) {
            execlp("alacritty", "alacritty", NULL);  // Jalankan alacritty
            perror("Failed to launch Alacritty");   // Jika execlp gagal
            exit(1);
        }
    }
}

void handle_client_message(XEvent *e) {
    XClientMessageEvent *cevent = &e->xclient;

    if (cevent->message_type == XInternAtom(dpy, "WM_PROTOCOLS", False)) {
        Atom wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
        if (cevent->data.l[0] == wm_delete) {
            XDestroyWindow(dpy, cevent->window);  // Close window
        }
    }
}

int main() {
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Unable to open X display\n");
        exit(1);
    }

    root = DefaultRootWindow(dpy);

    // Membuat sebuah window baru
    win = XCreateSimpleWindow(dpy, root, 100, 100, 400, 300, 1,
                              BlackPixel(dpy, 0), WhitePixel(dpy, 0));
    XStoreName(dpy, win, "Simple Window Manager");

    // Membuat Graphics Context (GC) untuk menggambar pada window
    gc = XCreateGC(dpy, win, 0, NULL);

    // Menghitung waktu untuk update display
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);

    // Menampilkan window
    XMapWindow(dpy, win);

    // Main event loop
    while (1) {
        XEvent e;
        XNextEvent(dpy, &e);

        switch (e.type) {
            case Expose:
                // Ketika window diekspos, gambar sesuatu di dalamnya
                XDrawString(dpy, win, gc, 20, 20, "Press ALT + ENTER to open Alacritty", 34);
                break;
            case KeyPress:
                handle_keypress(&e);
                break;
            case ClientMessage:
                handle_client_message(&e);
                break;
            default:
                break;
        }
    }

    return 0;
}

