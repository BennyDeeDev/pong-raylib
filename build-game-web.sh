#!/bin/bash

path_to_raylib="../raylib/src"

emcc -o web/pong.html main.c -Os -Wall $path_to_raylib/libraylib.a \
    -I. -I$path_to_raylib \
    -L. -L$path_to_raylib \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    --shell-file $path_to_raylib/minshell.html \
    -DPLATFORM_WEB