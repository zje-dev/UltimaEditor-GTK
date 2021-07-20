#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <iostream>

#include "files.h"
#include "./graphic/start_window.h"
#include "./graphic/error.h"
#include "./map/map_editor.h"
#include "./map/sc_editor.h"
#include "./cga/select_cga.h"
#include "./ega/select_ega.h"
#include "./t1k/Select_Tandy.h"

int palette = 0;
int tiles = 0;
int tile_file = 0;
int color = 0;
bool castle = true;
int a0, a1, a2, a3, a4;

void change_image (GtkImage *img) {
		switch(tile_file) {
			case 3:
				gtk_image_set_from_file(img, "./img/fight_normal.bmp");
				break;
			case 1:
				gtk_image_set_from_file(img, "./img/tiles_normal.bmp");
				break;
			case 2:
				gtk_image_set_from_file(img, "./img/space_normal.bmp");
				break;
			case 0:
				gtk_image_set_from_file(img, "./img/tiles_normal.bmp");
				break;
			case 4:
				gtk_image_set_from_file(img, "./img/town_normal.bmp");
				break;
		};
}

static gboolean scale_image(GtkWidget *image) {
	GdkPixbuf *pix = gtk_image_get_pixbuf(GTK_IMAGE(image));
	GtkAllocation *allocation = g_new0 (GtkAllocation, 1);
	gtk_widget_get_allocation(GTK_WIDGET(image), allocation);
	int h(0), w(0);
	if (castle) {
		switch (tile_file) {
			case 3:
				h = 19;
				w = 24;
				break;
			case 1:
				h = 16;
				w = 16;
				break;
			case 2:
				h = 19;
				w = 32;
				break;
			case 0:
				h = 16;
				w = 16;
				break;
			case 4:
				h = 8;
				w = 8;
				break;
		};
	} else {
		w = 88;
		h = 58;
	}
	pix = gdk_pixbuf_scale_simple(
		pix,
		w * 8,
		h * 8,
		GDK_INTERP_NEAREST
	);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), pix);
	return false;
}

void change_palette (GtkWidget *wid, GtkWidget *img) {
	if (std::string(gtk_widget_get_name(wid)) == "palette")
		palette = gtk_combo_box_get_active(GTK_COMBO_BOX(wid));
	else if (std::string(gtk_widget_get_name(wid)) == "tile")
		tile_file = gtk_combo_box_get_active(GTK_COMBO_BOX(wid));
	convert_xpm(tile_file, palette, read_ini(config_ini, "UltimaCommand"), a0, a1, a2, a3, a4, false, false);
	change_image(GTK_IMAGE(img));
}

void reload_image (GtkWidget *wid, GtkWidget *img) {
	if (std::string(gtk_widget_get_name(wid)) == "Select Tile")
		a0 =int(gtk_spin_button_get_value(GTK_SPIN_BUTTON(wid)));
	if (std::string(gtk_widget_get_name(wid)) == "Select Mond")
		a1 =int(gtk_spin_button_get_value(GTK_SPIN_BUTTON(wid)));
	if (std::string(gtk_widget_get_name(wid)) == "Select Town")
		a2 =int(gtk_spin_button_get_value(GTK_SPIN_BUTTON(wid)));
	if (std::string(gtk_widget_get_name(wid)) == "Select Space")
		a3 =int(gtk_spin_button_get_value(GTK_SPIN_BUTTON(wid)));
	if (std::string(gtk_widget_get_name(wid)) == "Select Fight")
		a4 =int(gtk_spin_button_get_value(GTK_SPIN_BUTTON(wid)));
	convert_xpm(tile_file, palette, read_ini(config_ini, "UltimaCommand"), a0, a1, a2, a3, a4, false, false);
	change_image(GTK_IMAGE(img));
}

static gboolean change_sprite_pixel (GtkWidget *widget, GdkEventButton *event, GtkWidget *sprite) {
	int x((event->x / 8) - 38), y((event->y / 8) - 23);
	int tile_of_preference = 0;
	int ar[4] = {0, 0, 0, 0};
	int xp = 0, yp = 15;
	std::string addfix = "";
	switch (tile_file) {
		case 0:
			ar[0] = 16;
			ar[1] = 256;
			ar[2] = 64;
			ar[3] = 128;
			xp = 15;
			tile_of_preference = a0;
			addfix = "tiles.bin";
			break;
		case 1:
			ar[0] = 16;
			ar[1] = 256;
			ar[2] = 64;
			ar[3] = 128;
			xp = 15;
			tile_of_preference = a1;
			addfix = "mond.bin";
			break;
		case 2:
			ar[0] = 32;
			ar[1] = 612;
			ar[2] = 153;
			xp = 23;
			tile_of_preference = a3;
			addfix = "space.bin";
			break;
		case 3:
			ar[0] = 24;
			ar[1] = 456;
			ar[2] = 114;
			xp = 19;
			tile_of_preference = a3;
			addfix = "fight.bin";
			break;
		case 4:
			xp = -21;
			ar[0] = 8;
			ar[1] = 64;
			ar[2] = 16;
			ar[3] = 32;
			tile_of_preference = a2;
			addfix = "town.bin";
			break;
	};
	if (event->button == 1) {
		int bin_size = 0;
		std::vector<unsigned char> buffer;
		std::string path;
		switch (palette) {
			case 0:
				path = (read_ini(config_ini, "UltimaCommand") + "/cga" + addfix);
				buffer = readfile(path.c_str(), &bin_size);
				change_pixel(xp - x, (y + ((tile_file == 2 || tile_file == 3) ? 1 : 0)), &buffer, path.c_str(), color, tile_of_preference, ar[0], ar[1], ar[2]);
				break;
			case 1:
				path = (read_ini(config_ini, "UltimaCommand") + "/ega" + addfix);
				buffer = readfile(path.c_str(), &bin_size);
				if (tile_file == 2)
					change_ega_mono((xp - 1) - x, y + 1, &buffer, path.c_str(), color, tile_of_preference, 608, 76, 32);
				else if (tile_file == 3)
					change_ega_mono(19 - x, y, &buffer, path.c_str(), color, tile_of_preference, 24, 57, 24);
				else if (tile_file == 4)
					change_ega_town(xp - x, y, &buffer, path.c_str(), color, tile_of_preference, 456, 228, 24);
				else
					change_ega_pixel(xp - x, y, &buffer, path.c_str(), color, tile_of_preference, ar[1], ar[3], ar[0]);
				break;
			case 2:
				path = (read_ini(config_ini, "UltimaCommand") + "/t1k" + addfix);
				buffer = readfile(path.c_str(), &bin_size);
				if (tile_file == 2)
					change_tandy_pixel(xp - x, y + 1, &buffer, path.c_str(), color, a2, 608, 304, 32);
				else if (tile_file == 3)
					change_tandy_pixel(xp - x, y + 1, &buffer, path.c_str(), color, tile_of_preference, 456, 228, 24);
				else
					change_tandy_pixel(xp - x, y, &buffer, path.c_str(), color, tile_of_preference, ar[1], ar[3], ar[0]);
				break;

		}
		convert_xpm(tile_file, palette, read_ini(config_ini, "UltimaCommand"), a0, a1, a2, a3, a4, false, false);
		change_image(GTK_IMAGE(sprite));
	} else if (event->button == 3) {
		color++;
		if (palette == 0) {
			if (color > 3)
				color = 0;
		} else {
			if (color > 15)
				color = 0;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	gtk_init (&argc, &argv);
	GtkBuilder *builder = gtk_builder_new ();
	GError *err = NULL;
	gtk_builder_add_from_file(builder, "../src/glade/main.glade", &err);

	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (builder, "window_ud"));
	GtkWidget *menu_quit = GTK_WIDGET(gtk_builder_get_object (builder, "menu_quit"));
	GtkWidget *menu_run = GTK_WIDGET(gtk_builder_get_object (builder, "menu_run"));
	GtkWidget *menu_open = GTK_WIDGET(gtk_builder_get_object (builder, "menu_open"));
	GtkWidget *window_open = GTK_WIDGET(gtk_builder_get_object (builder, "window_open"));
	GtkWidget *window_res = GTK_WIDGET(gtk_builder_get_object (builder, "window_res"));
	GtkWidget *window_palette = GTK_WIDGET(gtk_builder_get_object (builder, "window_palette"));
	GtkWidget *window_tile = GTK_WIDGET(gtk_builder_get_object (builder, "window_tile"));
	GtkWidget *window_tiles_editor = GTK_WIDGET(gtk_builder_get_object (builder, "window_tiles_editor"));
	GtkWidget *menu_tiles_editor = GTK_WIDGET(gtk_builder_get_object (builder, "menu_tiles_editor"));
	GtkWidget *menu_titlescreen = GTK_WIDGET(gtk_builder_get_object (builder, "menu_titlescreen"));

	GtkWidget *window_event = GTK_WIDGET(gtk_builder_get_object (builder, "window_event"));
	GtkWidget *window_select_tile = GTK_WIDGET(gtk_builder_get_object (builder, "window_select_tile"));
	GtkWidget *window_select_mond = GTK_WIDGET(gtk_builder_get_object (builder, "window_select_mond"));
	GtkWidget *window_select_town = GTK_WIDGET(gtk_builder_get_object (builder, "window_select_town"));
	GtkWidget *window_select_space = GTK_WIDGET(gtk_builder_get_object (builder, "window_select_space"));
	GtkWidget *window_select_fight = GTK_WIDGET(gtk_builder_get_object (builder, "window_select_fight"));
	GtkWidget *window_castle = GTK_WIDGET(gtk_builder_get_object (builder, "window_castle"));

	convert_xpm(0, 0, read_ini(config_ini, "UltimaCommand"), 0, 0, 0, 0, 0, false, false);
	convert_xpm(0, 1, read_ini(config_ini, "UltimaCommand"), 0, 0, 0, 0, 0, false, false);
	convert_xpm(0, 2, read_ini(config_ini, "UltimaCommand"), 0, 0, 0, 0, 0, false, false);
	if (read_ini(config_ini, "UltimaCommand").length() > 5)
		convert_xpm(0, 0, read_ini(config_ini, "UltimaCommand"), 0, 0, 0, 0, 0, false, false);
	gtk_image_set_from_file(GTK_IMAGE(window_res), "./img/tiles_normal.bmp");

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(menu_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(menu_run), "activate", G_CALLBACK(run_ultima_window), NULL);
	g_signal_connect(G_OBJECT(menu_open), "activate", G_CALLBACK(open_ultima), NULL);
	g_signal_connect(G_OBJECT(window_open), "clicked", G_CALLBACK(open_ultima), NULL);
	g_signal_connect(G_OBJECT(window_res), "draw", G_CALLBACK(scale_image), NULL);
	g_signal_connect(GTK_SPIN_BUTTON(window_select_tile), "value-changed", G_CALLBACK(reload_image), window_res);
	g_signal_connect(GTK_SPIN_BUTTON(window_select_mond), "value-changed", G_CALLBACK(reload_image), window_res);
	g_signal_connect(GTK_SPIN_BUTTON(window_select_town), "value-changed", G_CALLBACK(reload_image), window_res);
	g_signal_connect(GTK_SPIN_BUTTON(window_select_space), "value-changed", G_CALLBACK(reload_image), window_res);
	g_signal_connect(GTK_SPIN_BUTTON(window_select_fight), "value-changed", G_CALLBACK(reload_image), window_res);
	g_signal_connect(GTK_COMBO_BOX(window_palette), "changed", G_CALLBACK(change_palette), window_res);
	g_signal_connect(GTK_COMBO_BOX(window_tile), "changed", G_CALLBACK(change_palette), window_res);
	g_signal_connect(GTK_BUTTON(window_castle), "clicked", G_CALLBACK(castle_view), NULL);
	g_signal_connect(GTK_BUTTON(window_tiles_editor), "clicked", G_CALLBACK(tiles_editor), NULL);
	g_signal_connect(G_OBJECT(menu_tiles_editor), "activate", G_CALLBACK(tiles_editor), NULL);
	g_signal_connect(G_OBJECT(menu_titlescreen), "activate", G_CALLBACK(castle_view), NULL);
	g_signal_connect(G_OBJECT(window_event), "button-press-event", G_CALLBACK(change_sprite_pixel), window_res);

	gtk_window_set_title(GTK_WINDOW(window), "Ultima Editor v0.0");
	gtk_widget_show(window);
	gtk_main ();
	return 0;
}
