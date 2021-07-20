#include "map_editor.h"
#include "../files.h"
#include "../tinyfiledialogs-master/tinyfiledialogs.h"

#include <string>
#include <gtk/gtk.h>
#include <iostream>

#define add_x 0.0525275
#define add_y 0.07

bool map_town = true;
int ypos(0), current_map(0), current_tile(0);
int mapx(0), mapy(0);
std::vector<unsigned char> bin_buffer;
const std::string tiles_names_town[65] = {
	"Solid Wall",
	"Floor",
	"Water",
	"Water Corner - Top-Left",
	"Water Corner - Bottom-Left",
	"Water Corner - Top-Right",
	"Water Corner - Bottom-Right",
	"Water Diagonal - Bottom-Right",
	"Water Diagonal - Bottom-Left",
	"Tree - Small",
	"Tree - Big",
	"Counter - Left-Right",
	"Counter - Top-Bottom",
	"Counter - Top",
	"Counter - Bottom",
	"Counter - Left",
	"Counter - Right",
	"Person - Guard",
	"Person - Player",
	"Person - Jester 1",
	"Person - King",
	"Person - Merchant",
	"Person - Prisoner",
	"Brick Wall",
	"Char A",
	"Char B",
	"Char C",
	"Char D",
	"Char E",
	"Char F",
	"Char G",
	"Char H",
	"Char I",
	"Char J",
	"Char J",
	"Char K",
	"Char L",
	"Char M",
	"Char N",
	"Char O",
	"Char P",
	"Char Q",
	"Char R",
	"Char S",
	"Char T",
	"Char U",
	"Char V",
	"Char W",
	"Char X",
	"Char Y",
	"Char Z",
	"Person - Jester 2",
	"Floor - Water Floor 1",
	"Floor - Water Floor 2",
	"Floor - Water Floor 3",
	"Floor - Armoury 1",
	"Floor - Armoury 2",
	"Floor - Grocery 1",
	"Floor - Grocery 2",
	"Floor - Weaponry 1",
	"Floor - Weaponry 2",
	"Floor - Magic / Prison Cell 1",
	"Floor - Pub or Inn / Prison Cell 2",
	"Floor - Transportation / Throne Room",
	"Floor - Between Grocery and Pub"
}; /// https://moddingwiki.shikadi.net/wiki/Ultima_I_Town_Map_Format

void ent_square (int ent, int x, int y) {
	switch (ent) {
		case 0:
			glColor3f(1.0, 1.0, 0.35);
			break;
		case 1:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 2:
			glColor3f(1.0, 0.3, 1.0);
			break;
		case 3:	
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 4:
			glColor3f(1.0, 0.625, 0.0);
			break;
	}
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.985 + (0.025 * x), 0.98 - (y * 0.04));
		glVertex2f(-0.985 + (0.025 * (x + 2)), 0.98 - (y * 0.04));
		glVertex2f(-0.985 + (0.025 * (x + 2)), 0.98 - ((y + 1) * 0.04));
		glVertex2f(-0.985 + (0.025 * x), 0.98 - ((y + 1) * 0.04));
	glEnd();
	glutPostRedisplay();
} 

static void on_resize() {
	int bin_size = 0;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	char city[14] = "Town - [  ] +\0";
	char tile_town[14] = "Tile - [  ] +\0";
	const char player[7] = "Player\0";
	const char guard[6] = "Guard\0";
	const char king[5] = "King\0";
	const char jester[7] = "Jester\0";
	const char prisoner[18] = "Prisoner/Merchant\0";
	const char current[17] = "Current {TCD|MAP}\0";
	int cara1 = 0, cara2 = 0;
	int text[38][18];
	const std::string note_bmp = "Note: The image most be a 7 color paletted .bmp",
	note_cast = "Also you can't change castle/town/post position";
	glRasterPos2f(-0.985, 1);
	for (int c = 0; c < 17; c++) {
		if (map_town) {
			if (c > 8 && c < 12)
				glColor3f(1, 1, 0);
			else
				glColor3f(1, 1, 1);
		} else {
			if (c > 12 && c < 16)
				glColor3f(1, 1, 0);
			else
				glColor3f(1, 1, 1);
		}
		glRasterPos2f(-0.985 + (0.025 * (c + 32)), 0.98 - (48 * 0.04));
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, current[c]);
	}
	if (map_town) {
		bin_buffer = readfile((read_ini(config_ini, "UltimaCommand") + "/tcd.bin").c_str(), &bin_size);
		for (int w = 0; w < 38; w++) {
			for (int h = 0; h < 18; h++) {
				unsigned char v = (int)bin_buffer.at(h + (w * 18) + (684 * current_map));
				text[w][h] = v;
			}
		}
		for (int h = 0; h < 18; h++) {
			for (int w = 0; w < 38; w++) {
				int v = (unsigned char)text[w][h];
				if (v == 0)
					glColor3f(1, 1, 1);
				if (v == 1)
					glColor3f(0.2, 0.2, 0.2);
				if (v >= 2 && v <= 8)
					glColor3f(0.2, 0.2, 0.8);
				if (v == 9 || v == 10)
					glColor3f(0.2, 0.8, 0.2);
				if (v >= 11 && v <= 16)
					glColor3f(0.1, 0.1, 0.1);
				if ((v >= 17 && v <= 22) || v == 50)
					glColor3f(0.8, 0.8, 0.4);
				if (v >= 23 && v <= 49)
					glColor3f(0.8, 0.8, 0.8);
				if (v >= 50 && v <= 63)
					glColor3f(0.8, 0.2, 0.8);

				if (v > 10) {
					cara1 = ((v & 0xF0) >> 4) + '0';
					cara2 = (v & 0x0F) + '0';
				} else {
					cara1 = v + '0';
					cara2 = '0';
				}
				glRasterPos2f(-0.985 + ((w + 1) * (0.025 * 2)), 0.98 - ((h + 1) * 0.04));
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, cara1);
				glRasterPos2f(-0.985 + ((w + 1) * (0.025 * 2)) - 0.025, 0.98 - ((h + 1) * 0.04));
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, cara2);
			}
		}
		glColor3f(1, 1, 1);
		for (int c = 0; c < 13; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 2)), 0.98 - (20 * 0.04));
			//if (current_map > 9) {
			//	city[8] = int(current_map / 10) + '0';
			//	city[9] = current_map - (int(current_map / 10) * 10) + '0';
			//} else {
			city[8] = ' ';
			city[9] = current_map + '0';
			//}
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, city[c]);
		}
		glColor3f(1, 1, 1);
		for (int c = 0; c < 13; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 2)), 0.98 - (22 * 0.04));
			if (current_tile > 9) {
				tile_town[8] = int(current_tile / 10) + '0';
				tile_town[9] = current_tile - (int(current_tile / 10) * 10) + '0';
			} else {
				tile_town[8] = ' ';
				tile_town[9] = current_tile + '0';
			}
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, tile_town[c]);
		}
		for (int c = 0; c < 6; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 5)), 0.98 - (26 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, player[c]);
		}
		for (int c = 0; c < 5; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 5)), 0.98 - (28 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, guard[c]);
		}
		for (int c = 0; c < 4; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 5)), 0.98 - (30 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, king[c]);
		}
		for (int c = 0; c < 6; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 5)), 0.98 - (32 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, jester[c]);
		}
		for (int c = 0; c < 17; c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 5)), 0.98 - (34 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, prisoner[c]);
		}
		glColor3f(1, 1, 0);
		for (int c = 0; c < tiles_names_town[current_tile].length(); c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 2)), 0.98 - (23 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, tiles_names_town[current_tile][c]);
		}	
		switch (current_map) {
			case 0:
				ent_square(0, 1, 9);
				
				ent_square(1, 3, 6);
				ent_square(1, 35, 6);
				ent_square(1, 35, 11);
				ent_square(1, 51, 7);
				ent_square(1, 51, 12);
				ent_square(1, 73, 9);

				ent_square(3, 67, 4);

				ent_square(2, 71, 12);
				ent_square(4, 71, 7);
				break;
			case 1:
				ent_square(0, 1, 9);

				ent_square(1, 1, 8);
				ent_square(1, 23, 3);
				ent_square(1, 45, 1);
				ent_square(1, 57, 1);
				ent_square(1, 67, 5);
				ent_square(1, 69, 12);
				ent_square(1, 57, 12);

				ent_square(2, 63, 2);

				ent_square(3, 51, 4);

				ent_square(4, 45, 14);
				break;
			case 2:
				ent_square(0, 39, 17);

				ent_square(1, 43, 16);
				ent_square(1, 33, 16);
				ent_square(1, 41, 8);
				ent_square(1, 73, 8);
				ent_square(1, 5, 9);
				ent_square(1, 37, 3);

				ent_square(2, 27, 14);
				ent_square(2, 13, 14);
				ent_square(2, 51, 12);
				ent_square(2, 51, 3);
				ent_square(2, 65, 3);
				ent_square(2, 13, 3);

				ent_square(4, 69, 5);
				ent_square(4, 31, 5);
				break;
			case 3:
				ent_square(0, 39, 17);

				ent_square(1, 43, 16);
				ent_square(1, 3, 10);
				ent_square(1, 19, 8);
				ent_square(1, 33, 1);
				ent_square(1, 73, 7);

				ent_square(2, 11, 3);
				ent_square(2, 9, 16);
				ent_square(2, 25, 3);
				ent_square(2, 61, 1);
				ent_square(2, 69, 12);

				ent_square(4, 31, 9);
				ent_square(4, 55, 3);
				break;
			case 4:
				ent_square(0, 39, 17);

				ent_square(1, 45, 15);
				ent_square(1, 31, 15);
				ent_square(1, 47, 9);
				ent_square(1, 47, 9);
				ent_square(1, 21, 10);

				ent_square(2, 13, 3);
				ent_square(2, 7, 12);
				ent_square(2, 39, 1);
				ent_square(2, 69, 1);

				ent_square(4, 35, 3);
				ent_square(4, 43, 5);
				break;
			case 5:
				ent_square(0, 39, 17);

				ent_square(1, 3, 11);
				ent_square(1, 3, 7);
				ent_square(1, 29, 7);
				ent_square(1, 17, 16);
				ent_square(1, 59, 16);
				ent_square(1, 73, 11);
				
				ent_square(2, 69, 1);
				ent_square(2, 57, 1);
				ent_square(2, 45, 1);
				ent_square(2, 35, 1);
				ent_square(2, 25, 1);
				ent_square(2, 9, 1);

				ent_square(4, 49, 3);
				ent_square(4, 39, 12);
				break;
			case 6:
				ent_square(0, 39, 17);

				ent_square(1, 41, 15);
				ent_square(1, 35, 15);
				ent_square(1, 41, 2);
				ent_square(1, 35, 2);

				ent_square(2, 51, 8);
				ent_square(2, 25, 8);
				break;
			case 7:
				ent_square(0, 39, 17);

				ent_square(1, 3, 16);
				ent_square(1, 73, 16);
				ent_square(1, 3, 1);
				ent_square(1, 73, 1);
				ent_square(1, 43, 15);
				ent_square(1, 33, 15);
				ent_square(1, 17, 9);
				ent_square(1, 59, 9);
				ent_square(1, 37, 10);

				ent_square(2, 37, 2);
				ent_square(2, 17, 4);
				ent_square(2, 59, 4);
				ent_square(2, 19, 13);
				ent_square(2, 57, 13);

				ent_square(4, 41, 4);
				break;
			case 8:
				ent_square(0, 39, 17);

				ent_square(1, 41, 14);
				ent_square(1, 35, 14);
				ent_square(1, 9, 11);

				ent_square(2, 15, 4);
				ent_square(2, 37, 4);
				ent_square(2, 59, 3);
				
				ent_square(4, 55, 5);
				ent_square(4, 61, 14);
				break;
			case 9:
				ent_square(0, 39, 17);

				ent_square(1, 57, 17);
				ent_square(1, 13, 15);
				ent_square(1, 13, 12);
				ent_square(1, 15, 7);
				ent_square(1, 19, 5);
				ent_square(1, 75, 8);

				ent_square(2, 67, 16);
				ent_square(2, 69, 1);
				ent_square(2, 49, 1);
				ent_square(2, 33, 1);
				ent_square(2, 9, 1);
				ent_square(2, 3, 13);

				ent_square(4, 39, 10);
				break;
		};
		ent_square(0, 2, 25);
		ent_square(1, 2, 27);
		ent_square(2, 2, 33);
		ent_square(3, 2, 29);
		ent_square(4, 2, 31);
	} else {
		bin_buffer = readfile((read_ini(config_ini, "UltimaCommand") + "/map.bin").c_str(), &bin_size);
		glColor3f(1, 1, 1);
		for (int c = 0; c < note_bmp.size(); c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 2)), 0.98 - (32 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, note_bmp[c]);
		}
		for (int c = 0; c < note_cast.size(); c++) {
			glRasterPos2f(-0.985 + (0.025 * (c + 2)), 0.98 - (33 * 0.04));
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, note_cast[c]);
		}
		for (int w = 0; w < 38; w++) {
			for (int h = 0; h < 30; h++) {
				int8_t b1 = (((bin_buffer.at((w + mapx) + ((h + mapy) * 168))) >> 4) & 0x0F);
				int8_t b2 = ((bin_buffer.at((w + mapx) + ((h + mapy) * 168))) & 0x0F);
				//std::cout << (int)b1 << "\t" << (int)b2 << "\n";
				switch (b1) {
					case 0:
						glColor3f(0.2, 0.2, 1);
						break;
					case 1:
						glColor3f(0.2, 0.7, 0.2);
						break;
					case 2:
						glColor3f(0, 1, 0);
						break;
					case 3:
						glColor3f(0.6, 0.6, 0.2);
						break;
					case 4:
						glColor3f(0, 0, 1);
						break;
					case 5:
						glColor3f(1, 1, 1);
						break;
					case 6:
						glColor3f(0.5, 0.5, 0.5);
						break;
					case 7:
						glColor3f(1, 0, 0);
						break;
				};
				glRasterPos2f(-0.985 + ((w + 1) * (0.025 * 2)), 0.98 - ((h + 1) * 0.04));
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, char(b1 + '0'));

				switch (b2) {
					case 0:
						glColor3f(0.2, 0.2, 1);
						break;
					case 1:
						glColor3f(0.2, 0.7, 0.2);
						break;
					case 2:
						glColor3f(0, 1, 0);
						break;
					case 3:
						glColor3f(0.6, 0.6, 0.2);
						break;
					case 4:
						glColor3f(0, 0, 1);
						break;
					case 5:
						glColor3f(1, 1, 1);
						break;
					case 6:
						glColor3f(0.5, 0.5, 0.5);
						break;
					case 7:
						glColor3f(1, 0, 0);
						break;
				};
				glRasterPos2f(-0.985 + ((w + 1) * (0.025 * 2)) - 0.025, 0.98 - ((h + 1) * 0.04));
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, char(b2 + '0'));
			}
		}
	}
	glFlush();
}

void draw_tile_on_bmp (std::vector<unsigned char> *buf, int color, int pos, bool ot, int *e) {
	const int index = buf->size() - pos;
	switch (color) {
		case 0:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char)153);
			buf->at(index - 3) = ((unsigned char)204);
			break;
		case 1:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char)255);
			buf->at(index - 3) = ((unsigned char)000);
			break;
		case 2:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char) 50);
			buf->at(index - 3) = ((unsigned char)000);
			break;
		case 3:
			buf->at(index - 1) = ((unsigned char)150);
			buf->at(index - 2) = ((unsigned char)150);
			buf->at(index - 3) = ((unsigned char)150);
			break;
		case 4:
			buf->at(index - 1) = ((unsigned char) 20);
			buf->at(index - 2) = ((unsigned char) 20);
			buf->at(index - 3) = ((unsigned char) 20);
			break;
		case 5:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)255);
			buf->at(index - 3) = ((unsigned char)204);
			break;
		case 6:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)204);
			buf->at(index - 3) = ((unsigned char)153);
			break;
		case 7:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)000);
			buf->at(index - 3) = ((unsigned char)000);
			break;
	}
	*e++;
}

void change_tile_map (int x, int y, int o_or_t, std::vector<unsigned char> *buffer, int color) {
	unsigned char prev_color = (buffer->at(x + (y * 78))), res_color;
	if (!o_or_t) {
		res_color =
			((prev_color & 0xF0) >> 4)
			+ color;
	} else {
		res_color =
			(color * 10) +
			(prev_color & 0x0F);
	}
	buffer->at(x + (y * 78)) = res_color;
}

void castle_map () {
	map_town = !map_town;
}

void move_map (unsigned char k, int x, int y) {
	switch (k) {
		case 'd':
			if (mapx < 46)
				mapx += 1;
			break;
		case 'a':
			if (mapx > 0)
				mapx -= 1;
			break;
		case 's':
			if (mapy < 48)
				mapy += 1;
			break;
		case 'w':
			if (mapy > 0)
				mapy -= 1;
			break;
	};
	std::cout << mapy << "\n";
	glutPostRedisplay();
}

void add_rem_castle (int b, int s, int x, int y) {
	if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
		//std::cout << x << "\t" << y << "\n";
		if ((x >= 386 && x <= 420) && (y >= 567 && y <= 588)) {
			map_town = true;
			current_tile = 0;		
		} else if ((x >= 427 && x <= 461) && (y >= 567 && y <= 588)) {
			map_town = false;
			current_tile = 0;
		}
		if (map_town) {
			if ((x >= 132 && x <= 234) && (y <= 251 && y >= 234)) {
				if (current_map < 9)
					current_map += 1;
			} else if ((x >= 69 && x <= 84) && (y <= 251 && y >= 234)) {
				if (current_map > 0)
					current_map -= 1;
			}
			
			if ((x >= 132 && x <= 234) && (y <= 271 && y >= 258)) {
				if (current_tile < 64)
					current_tile += 1;
			} else if ((x >= 69 && x <= 84) && (y <= 271 && y >= 258)) {
				if (current_tile > 0)
					current_tile -= 1;
			}
			int tile_y = ((y - 7) / 12);
			int tile_x = ((x - 15) / 18);// - 1;
			//std::cout << tile_y << "\t" << tile_x << "\n";
			//std::cout << (tile_y + (tile_x * 18) + (684 * current_map)) << "\t" << tile_x << "\t" << tile_y << "\n";
			if (tile_y > -1 && tile_x > -1 && y < 225) {
				bin_buffer[tile_y + (tile_x * 18) + (684 * current_map)] = current_tile;
				std::ofstream water((read_ini(config_ini, "UltimaCommand") + "/tcd.bin").c_str(), std::ios::out|std::ios::binary);
				copy(bin_buffer.cbegin(), bin_buffer.cend(), std::ostreambuf_iterator<char>(water));
				water.close();
			}
		} else {
			if ((x >= 132 && x <= 234) && (y <= 394 && y >= 378)) {
				if (current_tile < 7)
					current_tile += 1;
			} else if ((x >= 69 && x <= 84) && (y <= 394 && y >= 378)) {
				if (current_tile > 0)
					current_tile -= 1;
			}
			if ((x >= 13 && x <= 730) && (y >= 5 && y <= 370)) {
				char const * bmp[1] = {"*.bmp"};
				int bin_size = 0;
				std::vector <unsigned char> map = readfile(tinyfd_openFileDialog ("Open file", "", 1, bmp, NULL, 0), &bin_size);
				for (int i = 150; i < map.size() - 2; i++)
					bin_buffer[i] = map.at(map.size() - i);
				std::ofstream water((read_ini(config_ini, "UltimaCommand") + "/map.bin").c_str(), std::ios::out|std::ios::binary);
				copy(bin_buffer.cbegin(), bin_buffer.cend(), std::ostreambuf_iterator<char>(water));
				water.close();
			}
		}
		glutPostRedisplay();
	}
}

void tiles_editor () {
	int argc = 0;
	char *argv = {(char *)"ud"};
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(750, 600);
	glutCreateWindow("Tiles editor");
	glutDisplayFunc(on_resize);
	glutKeyboardFunc(move_map);
	glutMouseFunc(add_rem_castle);
	glutMainLoop();
}
