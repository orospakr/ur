#!/bin/sh

g++ ur.cpp ur_layer.cpp ur_menu.cpp ur_sprite.cpp ur_font.cpp ur_map.cpp ur_object.cpp ur_titlescreen.cpp `sdl-config --cflags --libs` -g -o ur -Wall -Wno-deprecated