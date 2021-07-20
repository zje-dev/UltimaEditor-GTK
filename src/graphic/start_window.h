#include <gtk/gtk.h>

#pragma once
#ifndef START_WINDOW_H
#define START_WINDOW_H

//int cga_current_color = 0;

void draw_editor();
void select_tile();
void select_color();
void run_ultima ();
void run_ultima_window ();
void open_ultima ();
void ultima_set_path (GtkEntry *entry);
void select_ultima_folder ();
void tile_editor ();
void tile_castle ();
void tile_map ();
void change_tile ();

void convert_xpm (int, int, std::string, int, int, int, int, int, bool, bool);
void castle_xpm (int, std::string);
void map_xpm (const char*);

#endif
