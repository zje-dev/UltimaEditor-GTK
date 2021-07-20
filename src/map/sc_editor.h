#include <string>
#include <vector>
#include <GL/glut.h>
#include <iostream>

#pragma once
#ifndef START_SC_EDITOR_H
#define START_SC_EDITOR_H

int vga_to_ega (int v);
std::vector<int> get_color_ega_sc (int v);
std::vector<std::vector<int>> get_color_sc (bool ec, int v);
static void on_resize_sc ();
static bool on_render_sc ();
void change_pixel ();
void castle_view ();
std::vector<std::vector<int>> get_color_sc (bool, int);
void add_rem_sc (int b, int s, int x, int y);

#endif
