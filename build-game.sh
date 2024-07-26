#!/bin/bash

gcc main.c -I/opt/homebrew/opt/raylib/include -L/opt/homebrew/opt/raylib/lib -lraylib \
    -framework OpenGL \
    -framework Cocoa \
    -framework IOKit \
    -o PongRaylibC