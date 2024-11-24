#include "config.h"
#include "globals.h"
#include "utils.h"
#include "window_manager.h"

int main() {
  init_display();

  system("feh --bg-scale /home/rafii/Pictures/wallpaper/sA2Q8iC.jpeg &");

  XEvent ev;
  while (1) {
    XNextEvent(dpy, &ev);

    switch (ev.type) {
    case KeyPress:
      printf("Key Pressed: %d, state: 0x%x\n", ev.xkey.keycode, ev.xkey.state);
      handle_key_press(&ev.xkey);
      break;

    case ButtonPress:
      if (ev.xbutton.subwindow != None) {
        focus_window(ev.xbutton.subwindow);
      } else {
        printf("Button clicked on the root window, no subwindow.\n");
      }
      break;

    default:
      break;
    }
  }

  XCloseDisplay(dpy);
  return 0;
}
