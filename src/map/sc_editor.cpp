#include "sc_editor.h"
#include "../files.h"
#include "../tinyfiledialogs-master/tinyfiledialogs.h"
#include "../cga/select_cga.h"

#include <bitset>
#include <setjmp.h>
#include <stdio.h>
#include <png.h>
#include <string>
#include <gtk/gtk.h>
#include <iostream>

int sc_c = 0;

int vga_to_ega (int v) {
	int res = 0;
	if (v >= 85)
		res = 85;
	if (v >= 170)
		res = 170;
	if (v >= 220)
		res = 255;
	return res;
}

std::vector<int> get_color_ega_sc (int v) {
	std::vector<int> colors(3);
	switch (v) {
		case 0:
			colors.at(0) = 0;
			colors.at(1) = 0;
			colors.at(2) = 0;
			break;
		case 1:
			colors.at(0) = 85;
			colors.at(1) = 85;
			colors.at(2) = 85;
			break;
		case 2:
			colors.at(0) = 170;
			colors.at(1) = 170;
			colors.at(2) = 170;
			break;
		case 3:
			colors.at(0) = 255;
			colors.at(1) = 255;
			colors.at(2) = 255;
			break;
		case 4:
			colors.at(0) = 255;
			colors.at(1) = 255;
			colors.at(2) = 255;
			break;
		case 5:
			colors.at(0) = 0;
			colors.at(1) = 170;
			colors.at(2) = 0;
			break;
		case 6:
			colors.at(0) = 170;
			colors.at(1) = 255;
			colors.at(2) = 170;
			break;
		case 7:
			colors.at(0) = 170;
			colors.at(1) = 85;
			colors.at(2) = 0;
			break;
		case 8:
			colors.at(0) = 255;
			colors.at(1) = 85;
			colors.at(2) = 85;
			break;
		case 9:
			colors.at(0) = 170;
			colors.at(1) = 170;
			colors.at(2) = 170;
			break;
		case 10:
			colors.at(0) = 255;
			colors.at(1) = 85;
			colors.at(2) = 255;
			break;
		case 11:
			colors.at(0) = 85;
			colors.at(1) = 255;
			colors.at(2) = 255;
			break;
		case 12:
			colors.at(0) = 0;
			colors.at(1) = 0;
			colors.at(2) = 85;
			break;
		case 13:
			colors.at(0) = 85;
			colors.at(1) = 85;
			colors.at(2) = 255;
			break;
		case 14:
			colors.at(0) = 170;
			colors.at(1) = 170;
			colors.at(2) = 170;
			break;
		case 15:
			colors.at(0) = 255;
			colors.at(1) = 255;
			colors.at(2) = 255;
			break;
	};
	return colors;
}

std::vector<std::vector<int>> get_color_sc (bool ec, int v) {
	std::vector<std::vector<int>> colors(2, std::vector<int>(3));
	switch (v) {
		case 1:
			colors[0][0] = 0;
			colors[0][1] = 0;
			colors[0][2] = 0;
			colors[1][0] = 0;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 2:
			colors[0][0] = 0;
			colors[0][1] = 0;
			colors[0][2] = 0;
			colors[1][0] = 255;
			colors[1][1] = 0;
			colors[1][2] = 255;
			break;
		case 3:
			colors[0][0] = 0;
			colors[0][1] = 0;
			colors[0][2] = 0;
			colors[1][0] = 255;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 4:
			colors[0][0] = 0;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 0;
			colors[1][2] = 0;
			break;
		case 5:
			colors[0][0] = 0;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 6:
			colors[0][0] = 0;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 0;
			colors[1][2] = 255;
			break;
		case 7:
			colors[0][0] = 0;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 8:
			colors[0][0] = 255;
			colors[0][1] = 0;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 0;
			colors[1][2] = 0;
			break;
		case 9:
			colors[0][0] = 255;
			colors[0][1] = 0;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 10:
			colors[0][0] = 255;
			colors[0][1] = 0;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 0;
			colors[1][2] = 255;
			break;
		case 11:
			colors[0][0] = 255;
			colors[0][1] = 0;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 12:
			colors[0][0] = 255;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 0;
			colors[1][2] = 0;
			break;
		case 13:
			colors[0][0] = 255;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 0;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
		case 14:
			colors[0][0] = 255;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 0;
			colors[1][2] = 255;
			break;
		case 15:
			colors[0][0] = 255;
			colors[0][1] = 255;
			colors[0][2] = 255;
			colors[1][0] = 255;
			colors[1][1] = 255;
			colors[1][2] = 255;
			break;
	}
	return colors;
}

static void on_resize_sc() {
	int bin_size = 0;
	const std::string current = "{CGA | EGA | NIF}";
	const std::string note_ega = "16 color palette 320x200";
	const std::string note_cga = " 4 color palette 320x200";
	const std::string note_nif = " 2 color palette 320x168";
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	std::vector <unsigned char> bin_buffer;
	int xp = 191997;
	GLubyte* pixel_buffer = new GLubyte[192000];
	if (sc_c == 0) {
		bin_buffer = readfile((read_ini(config_ini, "UltimaCommand") + "/castle.4").c_str(), &bin_size);
		for (int y = 0; y < 100; y++) {
			for (int x = 0; x < 80; x++) {
				std::vector<std::vector<int>> pixel;
				std::vector<std::vector<int>> pixel2;
				pixel = get_color_sc(false, (bin_buffer.at(x + (y * 80)) & 0xF0) >> 4);
				pixel2 = get_color_sc(false, (bin_buffer.at(x + (y * 80)) & 0x0F));
				pixel_buffer[xp] = pixel[0][0];
				pixel_buffer[xp + 1] = pixel[0][1];
				pixel_buffer[xp + 2] = pixel[0][2];
				xp -= 3;
				pixel_buffer[xp] = pixel[1][0];
				pixel_buffer[xp + 1] = pixel[1][1];
				pixel_buffer[xp + 2] = pixel[1][2];
				xp -= 3;
				pixel_buffer[xp] = pixel2[0][0];
				pixel_buffer[xp + 1] = pixel2[0][1];
				pixel_buffer[xp + 2] = pixel2[0][2];
				xp -= 3;
				pixel_buffer[xp] = pixel2[1][0];
				pixel_buffer[xp + 1] = pixel2[1][1];
				pixel_buffer[xp + 2] = pixel2[1][2];
				xp -= 3;
			}
			xp -= 960;
		}
		xp = 191037;
		for (int y = 0; y < 100; y++) {
			for (int x = 0; x < 80; x++) {
				std::vector<std::vector<int>> pixel;
				std::vector<std::vector<int>> pixel2;
				pixel = get_color_sc(false, (bin_buffer.at((x + (y * 80)) + 8192) & 0xF0) >> 4);
				pixel2 = get_color_sc(false, (bin_buffer.at((x + (y * 80)) + 8192) & 0x0F));
				pixel_buffer[xp] = pixel[0][0];
				pixel_buffer[xp + 1] = pixel[0][1];
				pixel_buffer[xp + 2] = pixel[0][2];
				xp -= 3;
				pixel_buffer[xp] = pixel[1][0];
				pixel_buffer[xp + 1] = pixel[1][1];
				pixel_buffer[xp + 2] = pixel[1][2];
				xp -= 3;
				pixel_buffer[xp] = pixel2[0][0];
				pixel_buffer[xp + 1] = pixel2[0][1];
				pixel_buffer[xp + 2] = pixel2[0][2];
				xp -= 3;
				pixel_buffer[xp] = pixel2[1][0];
				pixel_buffer[xp + 1] = pixel2[1][1];
				pixel_buffer[xp + 2] = pixel2[1][2];
				xp -= 3;
			}
			xp -= 960;
		}
	} else if (sc_c == 1) {
		bin_buffer = readfile((read_ini(config_ini, "UltimaCommand") + "/castle.16").c_str(), &bin_size);
		xp = 191997;
		for (int y = 0; y < 200; y++) {
			for (int x = 0; x < 160; x++) {
				std::vector<int> colors1;
				std::vector<int> colors2;
				colors1 = get_color_ega_sc((bin_buffer.at(x + (y * (160))) & 0xF0) >> 4);
				colors2 = get_color_ega_sc(bin_buffer.at(x + (y * (160))) & 0x0F);
				pixel_buffer[xp] = colors1[0];
				pixel_buffer[xp + 1] = colors1[1];
				pixel_buffer[xp + 2] = colors1[2];
				xp -= 3;
				pixel_buffer[xp] = colors2[0];
				pixel_buffer[xp + 1] = colors2[1];
				pixel_buffer[xp + 2] = colors2[2];
				xp -= 3;
			}
		}
	} else if (sc_c == 2) {
		xp = 191997;
		bin_buffer = readfile((read_ini(config_ini, "UltimaCommand") + "/nif.bin").c_str(), &bin_size);
		for (int y = 0; y < 168; y++) {
			for (int x = 0; x < 40; x++) {
				std::bitset<8> b(bin_buffer.at(x + (y * 40)));
				for (int i = 0; i < 8; i++) {
					if (b[i] == 0) {
						pixel_buffer[xp] = 0;
						pixel_buffer[xp + 1] = 0;
						pixel_buffer[xp + 2] = 0;
						xp -= 3;
					} else  {
						pixel_buffer[xp] = 255;
						pixel_buffer[xp + 1] = 255;
						pixel_buffer[xp + 2] = 255;
						xp -= 3;
					}
				}
			}
		}
	}
	glRasterPos2f(-1, -1);
	glDrawPixels(320, 200, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);
	for (int w = 0; w < current.size(); w++) {
		glColor3f(1, 1, 1);
		switch (sc_c) {
			case 0:
				if (w > 0 && w < 4)
					glColor3f(1, 1, 0);
				break;
			case 1:
				if (w > 5 && w < 10)
					glColor3f(1, 1, 0);
				break;
			case 2:
				if (w > 12 && w < 16)
					glColor3f(1, 1, 0);
				break;
		}
		glRasterPos2f(-0.985 + ((w + 12) * 0.05), 0.9);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, current[w]);
	}
	for (int w = 0; w < note_cga.size(); w++) {
		glRasterPos2f(-0.985 + ((w + 8) * 0.05), 0.75);
		switch(sc_c) {
			case 0:
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, note_cga[w]);
				break;
			case 1:
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, note_ega[w]);
				break;
			case 2:
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, note_nif[w]);
				break;
		};
	}
	glFlush();
}

void add_rem_sc (int b, int s, int x, int y) {
	if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
		if (y < 15 && y > 0) {
			if (x > 106 && x < 134)
				sc_c = 0;
			if (x > 154 && x < 181)
				sc_c = 1;
			if (x > 200 && x < 231)
				sc_c = 2;
		} else if (y > 35) {
			int bin_size = 0;
			std::vector<unsigned char> data, cga, ega, nif;
			cga = readfile((read_ini(config_ini, "UltimaCommand") + "/castle.4").c_str(), &bin_size);
			ega = readfile((read_ini(config_ini, "UltimaCommand") + "/castle.16").c_str(), &bin_size);
			nif = readfile((read_ini(config_ini, "UltimaCommand") + "/nif.bin").c_str(), &bin_size);
			char const * bmp[1] = {"*.png"};
			FILE *png = fopen (tinyfd_openFileDialog ("Open file", "", 1, bmp, NULL, 0), "rb");
			png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			png_set_palette_to_rgb(png_ptr);
			png_infop info_ptr = png_create_info_struct (png_ptr);
			png_colorp palette;
			int why = 4;
			png_get_PLTE(png_ptr, info_ptr, &palette, &why);
			//png_set_palette_to_rgb(png_ptr);
			png_init_io (png_ptr, png);
			png_read_png (png_ptr, info_ptr, 0, 0);
			int de = png_get_bit_depth(png_ptr, info_ptr);
			png_bytepp rows = png_get_rows (png_ptr, info_ptr);
			png_byte pixel;
			if (setjmp(png_jmpbuf(png_ptr)) == 0) {
				if (sc_c == 0) {
					for (int h = 0; h < 200; h++) {
						for (int w = 0; w < 960; w += 3) {
							if (rows[h][w] == 0 && rows[h][w + 1] == 0 && rows[h][w + 2] == 0)
								data.push_back(0);
							if (rows[h][w] > 0 && rows[h][w + 1] == 0 && rows[h][w + 2] > 0)
								data.push_back(3);
							if (rows[h][w] == 0 && rows[h][w + 1] > 0 && rows[h][w + 2] > 0)
								data.push_back(2);
							if (rows[h][w] > 0 && rows[h][w + 1] > 0 && rows[h][w + 2] > 0)
								data.push_back(1);
						}
					}
					for (int h = 0; h < 100; h++) {
						int xp = 0;
						for (int w = 0; w < 320; w += 4) {
							cga.at(xp + (h * 80)) = (
								(color_to_byte(data[w + (h * 640)], data[w + 1 + (h * 640)]) << 4) +
								color_to_byte(data[w + 2 + (h * 640)], data[w + 3 + (h * 640)])
							);
							cga.at(xp + (h * 80) + 8192) = (
								(color_to_byte(data[w + (h * 640) + 320], data[w + 1 + (h * 640) + 320]) << 4) +
								color_to_byte(data[w + 2 + (h * 640) + 320], data[w + 3 + (h * 640) + 320])
							);
							xp++;
						}
					}
				} else if (sc_c == 1) {
					int xp = 0;
					data.reserve(64000);
					for (int h = 0; h < 200; h++) {
						for (int w = 0; w < 960; w += 3) {
							int r(vga_to_ega(rows[h][w])),
							g(vga_to_ega(rows[h][w + 1])),
							b(vga_to_ega(rows[h][w + 2]));
							data[xp] =(0);
							if (r == 0 && g == 0 && b == 0)
								data[xp] =(0);
							if (r == 85 && g == 85 && b == 85)
								data[xp] =(1);
							if (r == 170 && g == 170 && b == 170)
								data[xp] =(2);
							if (r == 255 && g == 255 && b == 255)
								data[xp] =(3);
							if (r == 0 && g == 170 && b == 0)
								data[xp] =(5);
							if (r == 85 && g == 255 && b == 85)
								data[xp] =(6);
							if (r == 170 && g == 85 && b == 0)
								data[xp] =(7);
							if (r == 255 && g == 85 && b == 85)
								data[xp] =(8);
							if (r == 255 && g == 85 && b == 255)
								data[xp] =(10);
							if (r == 85 && g == 255 && b == 255)
								data[xp] =(11);
							if (r == 0 && g == 0 && b == 85)
								data[xp] =(12);
							if (r == 85 && g == 85 && b == 255)
								data[xp] =(13);
							xp ++;
						}
					}
					for (int h = 0; h < 200; h++) {
						int xp = 0;
						for (int w = 0; w < 320; w += 2) {
							ega.at(xp + (h * 160)) = (data[w + (h * 320)]  << 4) + data[w + 1 + (h * 320)];
							xp += 1;
						}
					}
				} else if (sc_c == 2) {
					int xp = 0;
					data.reserve(53760);
					for (int h = 0; h < 168; h++) {
						for (int w = 0; w < 960; w += 3) {
							data[xp] = (int)(rows[h][w] > 128 && rows[h][w + 1] > 128 && rows[h][w + 2] > 128);
							xp++;
						}
					}
					xp = 0;
					for (int h = 0; h < 168; h++) {
						for (int w = 0; w < 320; w += 8) {
							unsigned int res = 0;
							for (int i = 0; i < 8; i++) {
								res = (res << 1) + (data[w + (h * 320) + i] - '0');
							}
							ega.at(xp/* + (h * 40)*/) = res;
							xp += 1;
						}
					}
				}
				fclose(png);
				std::ofstream water((read_ini(config_ini, "UltimaCommand") + "/castle.4").c_str(), std::ios::out|std::ios::binary);
				copy(cga.cbegin(), cga.cend(), std::ostreambuf_iterator<char>(water));
				water.close();
				std::ofstream fire((read_ini(config_ini, "UltimaCommand") + "/castle.16").c_str(), std::ios::out|std::ios::binary);
				copy(ega.cbegin(), ega.cend(), std::ostreambuf_iterator<char>(fire));
				fire.close();
				std::ofstream grasa((read_ini(config_ini, "UltimaCommand") + "/nif.bin").c_str(), std::ios::out|std::ios::binary);
				copy(ega.cbegin(), ega.cend(), std::ostreambuf_iterator<char>(grasa));
				fire.close();
			}
		}
	}
	glutPostRedisplay();
}

void castle_view () {
	int argc = 0;
	char *argv = {(char *)"ud"};
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(320, 235);
	glutCreateWindow("Title screen editor");
	glutDisplayFunc(on_resize_sc);
	glutMouseFunc(add_rem_sc);
	glutMainLoop();
}
