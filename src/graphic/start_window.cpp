#include "../graphic/tiles.h"

#include <string>
#include <vector>
#include "./start_window.h"
#include "./palette.h"
#include "../files.h"
#include "../cga/cga.h"
#include "../cga/select_cga.h"
#include "../ega/select_ega.h"
#include "../ega/ega_select.h"
#include "../cga/cga_select.h"
#include "../t1k/Tandy_Select.h"
#include "../t1k/Select_Tandy.h"
#ifndef BMP_H
	#include "../img/convert_ultima_into_xpm.h"
#endif
#include "../legal.h"
#include "../map/map_editor.h"
#include "../color/color.h"

#include <glib.h>
#include <iostream>

#define version "1"

std::string ultima_path;
std::vector<unsigned char> buffer;

//control
int bin_size = 0;
bool fullscreen_castle = false;

void run_ultima () {
	system(("wine " + read_ini(config_ini, "UltimaCommand") + "/ultima.exe").c_str());
}

void ultima_set_path (GtkEntry *entry) {
	ini_write(config_ini, "UltimaCommand", gtk_entry_get_text(entry));
}

void run_ultima_window () {
	GtkBuilder *builder = gtk_builder_new ();
	gtk_builder_add_from_file(builder, "../src/glade/ultima.glade", NULL);

	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (builder, "u_window"));
	GtkWidget *path = GTK_WIDGET(gtk_builder_get_object (builder, "u_path"));
	GtkWidget *run = GTK_WIDGET(gtk_builder_get_object (builder, "u_run"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	g_signal_connect(G_OBJECT(path), "activate", G_CALLBACK(ultima_set_path), NULL);
	g_signal_connect(G_OBJECT(run), "clicked", G_CALLBACK(run_ultima), NULL);
	gtk_widget_show(window);
}

void open_ultima () {
	GtkBuilder *builder = gtk_builder_new ();
	gtk_builder_add_from_file(builder, "../src/glade/select_ultima.glade", NULL);

	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (builder, "u_window"));
	GtkWidget *path = GTK_WIDGET(gtk_builder_get_object (builder, "u_path"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	g_signal_connect(G_OBJECT(path), "activate", G_CALLBACK(ultima_set_path), NULL);
	gtk_widget_show(window);
}

void convert_xpm (int tt, int pal, std::string ultima_path, int index_tiles, int index_mond, int index_town, int index_space, int index_fight, bool fsc, bool map) {
	std::vector<unsigned char> bmp_buffer, bin_buffer;
	int size, bin_size;
	if (!fsc) {
		if (pal == 0) { //When i do a BIG switch it just doesn't work
			bmp_buffer = readfile(water_cga_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/cgatiles.bin").c_str(), &bin_size);
					index = index_tiles;
					width = 64;
					height = 64;
					file_path = water_cga_path;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/cgamond.bin").c_str(), &bin_size);
					index = index_mond;
					width = MOND_W * 4;
					height = TILES_H * 4;
					file_path = water_cga_path;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/cgaspace.bin").c_str(), &bin_size);
					bmp_buffer = readfile(space_cga_path, &size);
					index = index_space;
					width = 152;
					height = 152;
					file_path = space_cga_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/cgafight.bin").c_str(), &bin_size);
					bmp_buffer = readfile(fight_cga_path, &size);
					index = index_fight;
					width = 114;
					height = 114;
					file_path = fight_cga_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/cgatown.bin").c_str(), &bin_size);
					width = TOWN_W;
					index = index_town * 2;
					height = TILES_H;
					bmp_buffer = readfile(town_cga_path, &size);
					file_path = town_cga_path;
					break;
			}
			for (int i = 0; i < height; i++) {
				cga_to_hex((unsigned char)((bin_buffer.at(i + (width * index)) & 0xF0) >> 4), &bmp_buffer, (6 * i) * 2);
				cga_to_hex((unsigned char)(bin_buffer.at(i  + (width * index)) & 0x0F), &bmp_buffer, (6 * (i + 1)) + (i * 6));
			}
			std::ofstream water((map ? get_cas(index) : file_path), std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
			water.close();
		}
		if (pal == 1) {
			bmp_buffer = readfile(water_cga_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			int ind = 0, ex = 0;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/egatiles.bin").c_str(), &bin_size);
					ind = (index_tiles * 128);
					file_path = water_cga_path;
					height = 16;
					width = 12;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/egamond.bin").c_str(), &bin_size);
					ind = (index_mond * 128);
					file_path = water_cga_path;
					height = 16;
					width = 12;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/egaspace.bin").c_str(), &bin_size);
					bmp_buffer = readfile(space_cga_path, &size);
					ind = index_space * 152;
					height = 9;
					width = 12;
					file_path = space_cga_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/egafight.bin").c_str(), &bin_size);
					bmp_buffer = readfile(fight_cga_path, &size);
					ind = index_fight * 114;
					height = 7;
					width = 8;
					file_path = fight_cga_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/egatown.bin").c_str(), &bin_size);
					ind = index_town * 32;
					bmp_buffer = readfile(town_cga_path, &size);
					height = 8;
					width = 4;
					file_path = town_cga_path;
					break;
			}
			for (int i = 0; i < height; i++) {
				if (tt == 0 || tt == 1)
					ega_to_hex(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 4)
					ega_to_town(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 2)
					ega_to_space(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 3)
					ega_to_space(&bmp_buffer, bin_buffer, i, &ind, &ex);
			}
			std::ofstream water(file_path, std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
			water.close();
		}
		if (pal == 2) {
			bmp_buffer = readfile(water_cga_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			int ind = 0, ex = 0;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/t1ktiles.bin").c_str(), &bin_size);
					ind = (index_tiles * 128);
					width = 128;
					file_path = water_cga_path;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/t1kmond.bin").c_str(), &bin_size);
					ind = (index_mond * 128);
					width = 128;
					file_path = water_cga_path;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/t1kspace.bin").c_str(), &bin_size);
					bmp_buffer = readfile(space_cga_path, &size);
					ind = index_space * 304;
					width = 304;
					file_path = space_cga_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/t1kfight.bin").c_str(), &bin_size);
					bmp_buffer = readfile(fight_cga_path, &size);
					ind = index_fight * 228;
					width = 228;
					file_path = fight_cga_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/t1ktown.bin").c_str(), &bin_size);
					ind = (index_town * 32);
					width = 32;
					bmp_buffer = readfile(town_cga_path, &size);
					file_path = town_cga_path;
					break;
			}
			tandy_to_hex(&bmp_buffer, bin_buffer, ind, width);
			std::ofstream water(file_path, std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
			water.close();
		}
	} else {
		int l;
		castle_xpm(pal, ultima_path);
		map_xpm((ultima_path + "/MAP.BIN").c_str());
	}
}

void castle_xpm (int pal, std::string ultima_path) {
	std::vector<unsigned char> bmp_buffer, bin_buffer;
	int size = 0, bin_size = 0, pixel = 0;
	if (pal == 0) { //Switch doesn't work
		bin_buffer = readfile((ultima_path + "/CASTLE.4").c_str(), &bin_size);
		bmp_buffer = readfile(castle_cga_path, &size);
		int nex = 0, t = 80;
		for (int i = 0; i < 8000; i++) {
			int width = 64;
			if (i == t) {
				nex += 2;
				if (nex <= 200)
					t += 80;
			}
			cga_to_hex((unsigned char)((bin_buffer.at(i) & 0xF0) >> 4), &bmp_buffer, ((6 * i) + (i * 6)) + (nex * 480));
			cga_to_hex((unsigned char)(bin_buffer.at(i) & 0x0F), &bmp_buffer, (6 * ((i + 1)) + (i * 6)) +  (nex * 480));
			cga_to_hex((unsigned char)((bin_buffer.at(i + 8192) & 0xF0) >> 4), &bmp_buffer, ((6 * i) + (i * 6)) + ((nex + 2) * 480));
			cga_to_hex((unsigned char)(bin_buffer.at(i + 8192) & 0x0F), &bmp_buffer, (6 * ((i + 1)) + (i * 6)) +  ((nex + 2) * 480));
		}
		std::ofstream castle(castle_cga_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
	if (pal == 1) {
		bin_buffer = readfile((ultima_path + "/CASTLE.16").c_str(), &bin_size);
		bmp_buffer = readfile(castle_cga_path, &size);
		for (int i = 0; i < 32000; i++) {
			map_ega_xpm(&bmp_buffer, (bin_buffer[i] & 0xF0) >> 4, &pixel);
			map_ega_xpm(&bmp_buffer, bin_buffer[i] & 0x0F, &pixel);
		}
		std::ofstream castle(castle_cga_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
	if (pal == 2) {
		bin_buffer = readfile((ultima_path + "/CASTLE.16").c_str(), &bin_size);
		bmp_buffer = readfile(castle_cga_path, &size);
		for (int i = 0; i < 32000; i++) {
			map_tik_xpm(&bmp_buffer, (bin_buffer[i] & 0xF0) >> 4, &pixel);
			map_tik_xpm(&bmp_buffer, bin_buffer[i] & 0x0F, &pixel);
		}
		std::ofstream castle(castle_cga_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
}

void map_xpm (const char* path) {
	std::vector<unsigned char> bmp_buffer;
	int size = 0, e = 0;
	std::vector<unsigned char> bin_buf;
	bmp_buffer = readfile(map_cga_path, &size);
	bin_buf = readfile(path, &size);
	for (int i = 0; i < 78624; i += 6) {
		int index = bmp_buffer.size() - i;
		switch ((bin_buf[e] & 0xF0) >> 4) {
			case 0:
				bmp_buffer[index - 1] = ((unsigned char)000);
				bmp_buffer[index - 2] = ((unsigned char)153);
				bmp_buffer[index - 3] = ((unsigned char)204);
				break;
			case 1:
				bmp_buffer[index - 1] = ((unsigned char)000);
				bmp_buffer[index - 2] = ((unsigned char)255);
				bmp_buffer[index - 3] = ((unsigned char)000);
				break;
			case 2:
				bmp_buffer[index - 1] = ((unsigned char)000);
				bmp_buffer[index - 2] = ((unsigned char) 50);
				bmp_buffer[index - 3] = ((unsigned char)000);
				break;
			case 3:
				bmp_buffer[index - 1] = ((unsigned char)150);
				bmp_buffer[index - 2] = ((unsigned char)150);
				bmp_buffer[index - 3] = ((unsigned char)150);
				break;
			case 4:
				bmp_buffer[index - 1] = ((unsigned char) 20);
				bmp_buffer[index - 2] = ((unsigned char) 20);
				bmp_buffer[index - 3] = ((unsigned char) 20);
				break;
			case 5:
				bmp_buffer[index - 1] = ((unsigned char)255);
				bmp_buffer[index - 2] = ((unsigned char)255);
				bmp_buffer[index - 3] = ((unsigned char)204);
				break;
			case 6:
				bmp_buffer[index - 1] = ((unsigned char)255);
				bmp_buffer[index - 2] = ((unsigned char)204);
				bmp_buffer[index - 3] = ((unsigned char)153);
				break;
			case 7:
				bmp_buffer[index - 1] = ((unsigned char)255);
				bmp_buffer[index - 2] = ((unsigned char)000);
				bmp_buffer[index - 3] = ((unsigned char)000);
				break;
		};

		switch (bin_buf[e] & 0x0F) {
			case 0:
				bmp_buffer[index - 4] = ((unsigned char)000);
				bmp_buffer[index - 5] = ((unsigned char)153);
				bmp_buffer[index - 6] = ((unsigned char)204);
				break;
			case 1:
				bmp_buffer[index - 4] = ((unsigned char)000);
				bmp_buffer[index - 5] = ((unsigned char)255);
				bmp_buffer[index - 6] = ((unsigned char)000);
				break;
			case 2:
				bmp_buffer[index - 4] = ((unsigned char)000);
				bmp_buffer[index - 5] = ((unsigned char) 50);
				bmp_buffer[index - 6] = ((unsigned char)000);
				break;
			case 3:
				bmp_buffer[index - 4] = ((unsigned char)150);
				bmp_buffer[index - 5] = ((unsigned char)150);
				bmp_buffer[index - 6] = ((unsigned char)150);
				break;
			case 4:
				bmp_buffer[index - 4] = ((unsigned char) 20);
				bmp_buffer[index - 5] = ((unsigned char) 20);
				bmp_buffer[index - 6] = ((unsigned char) 20);
				break;
			case 5:
				bmp_buffer[index - 4] = ((unsigned char)255);
				bmp_buffer[index - 5] = ((unsigned char)255);
				bmp_buffer[index - 6] = ((unsigned char)204);
				break;
			case 6:
				bmp_buffer[index - 4] = ((unsigned char)255);
				bmp_buffer[index - 5] = ((unsigned char)204);
				bmp_buffer[index - 6] = ((unsigned char)153);
				break;
			case 7:
				bmp_buffer[index - 4] = ((unsigned char)255);
				bmp_buffer[index - 5] = ((unsigned char)000);
				bmp_buffer[index - 6] = ((unsigned char)000);
				break;
		};
		e += 1;
	}
	std::ofstream castle(map_cga_path, std::ios::out|std::ios::binary);
	copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
}

/*
			} else if (Read_Tile_As->GetSelection() == 3) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -50
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 34
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -26
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 16
				) {
					switch (Select_Palette->GetSelection()) {
						case 0:{
							int x = (evt.GetLogicalPosition(*this->dc).x + 26) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGAFIGHT.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGAFIGHT.BIN").c_str(), cga_current_color, fight_tile_wid->GetValue(), 24, 456, 114);
							}
							break;
						case 2:{
							int x = (evt.GetLogicalPosition(*this->dc).x + 26) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KFIGHT.BIN").c_str(), &bin_size);
							change_tandy_pixel(x, y, &bin_buffer, (ultima_path + "T1KFIGHT.BIN").c_str(), cga_current_color, fight_tile_wid->GetValue(), 456, 228, 24);
							}
							break;
					}
				}
			} else if (Read_Tile_As->GetSelection() == 4) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -30
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 23
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -22
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 15
				) {
					switch (Select_Palette->GetSelection()) {
						case 0: {
							int x = ((evt.GetLogicalPosition(*this->dc).x + 22) * -1),
							y = (evt.GetLogicalPosition(*this->dc).y - 15);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGATOWN.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGATOWN.BIN").c_str(), cga_current_color, town_tile_wid->GetValue(), 8, 64, 16);
							}
							break;
						case 2: {
							int x = ((evt.GetLogicalPosition(*this->dc).x + 22) * -1),
							y = (evt.GetLogicalPosition(*this->dc).y - 15);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KTOWN.BIN").c_str(), &bin_size);
							change_tandy_pixel(x, y, &bin_buffer, (ultima_path + "T1KTOWN.BIN").c_str(), cga_current_color, town_tile_wid->GetValue(), 64, 32, 8);
							}
							break;
					}
				}
			}
		}
}*/
