#ifndef CONFIG_H
#define CONFIG_H

#include "utils.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

#define BORDER_WIDTH 2
#define FOCUS_COLOR 0xFF0000   // Red
#define UNFOCUS_COLOR 0xFFFFFF // White

void init_display();

#endif
