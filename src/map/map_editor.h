#include <string>
#include <vector>
#include <GL/glut.h>
#include <iostream>

#pragma once
#ifndef START_TILES_EDITOR_H
#define START_TILES_EDITOR_H

static void on_resize ();
static bool on_render ();
void draw_tile_on_bmp (std::vector<unsigned char> *buf, int color, int pos, bool ot, int *e);
void change_tile_map (int x, int y, int o_or_t, std::vector<unsigned char> *buffer, int color);
void castle_map ();
void tiles_editor ();
void add_rem_castle (int b, int s, int x, int y);

#endif
