#include <vector>
#pragma once
#ifndef SELECT_EGA_H
#define SELECT_EGA_H

int im_blue (int);
int is_green (int);
int is_red (int);
int is_white (int);

int color_ega_format (bool, bool, bool, bool);
int ega_color_format (int color[16], int l);
void change_ega_pixel (int, int, std::vector<unsigned char>*, const char*, int, int, int, int, int);
int ega_format (int[4], int[4], int[4], int[4], int);
int ega_mono_format (int[8], int);
int ega_color_mono (int color[32], int l);
void change_ega_mono (int, int, std::vector<unsigned char>*, const char*, int, int, int, int, int);
int ega_color_town (int[16], int);
int ega_town_format(int[4], int[4], int[4], int[4], int);
void change_ega_town(int, int, std::vector<unsigned char>*, const char*, int, int, int, int, int);

#endif
