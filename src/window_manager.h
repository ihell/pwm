#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "utils.h"
#include <X11/Xlib.h>

#define MOD1_MASK Mod1Mask // ALT KEY
#define MOD4_MASK Mod4Mask // WINDOWS KEY

void handle_key_press(XKeyEvent *ev);

#endif
