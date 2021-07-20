#include "Tandy_Select.h"

void tandy_to_hex (std::vector<unsigned char> *buf, std::vector<unsigned char> bin_buffer, int pos, int len) {
	int l(buf->size() - 1), pc = 0;
	for (int i = 0; i < len; i++) {
		switch ((bin_buffer.at(i + pos) & 0xF0) >> 4) {
			case 0:
				buf->at(l - pc - 0) = 0;
				buf->at(l - pc - 1) = 0;
				buf->at(l - pc - 2) = 0;
				break;
			case 1:
				buf->at(l - pc - 0) = 0;
				buf->at(l - pc - 1) = 0;
				buf->at(l - pc - 2) = 170;
				break;
			case 2:
				buf->at(l - pc - 0) = 0;
				buf->at(l - pc - 1) = 170;
				buf->at(l - pc - 2) = 0;
				break;
			case 3:
				buf->at(l - pc - 0) = 0;
				buf->at(l - pc - 1) = 170;
				buf->at(l - pc - 2) = 170;
				break;
			case 4:
				buf->at(l - pc - 0) = 170;
				buf->at(l - pc - 1) = 0;
				buf->at(l - pc - 2) = 0;
				break;
			case 5:
				buf->at(l - pc - 0) = 170;
				buf->at(l - pc - 1) = 0;
				buf->at(l - pc - 2) = 170;
				break;
			case 6:
				buf->at(l - pc - 0) = 170;
				buf->at(l - pc - 1) = 85;
				buf->at(l - pc - 2) = 0;
				break;
			case 7:
				buf->at(l - pc - 0) = 170;
				buf->at(l - pc - 1) = 170;
				buf->at(l - pc - 2) = 170;
				break;
			case 8:
				buf->at(l - pc - 0) = 85;
				buf->at(l - pc - 1) = 85;
				buf->at(l - pc - 2) = 85;
				break;
			case 9:
				buf->at(l - pc - 0) = 85;
				buf->at(l - pc - 1) = 85;
				buf->at(l - pc - 2) = 255;
				break;
			case 10:
				buf->at(l - pc - 0) = 85;
				buf->at(l - pc - 1) = 255;
				buf->at(l - pc - 2) = 85;
				break;
			case 11:
				buf->at(l - pc - 0) = 85;
				buf->at(l - pc - 1) = 255;
				buf->at(l - pc - 2) = 255;
				break;
			case 12:
				buf->at(l - pc - 0) = 255;
				buf->at(l - pc - 1) = 85;
				buf->at(l - pc - 2) = 85;
				break;
			case 13:
				buf->at(l - pc - 0) = 255;
				buf->at(l - pc - 1) = 85;
				buf->at(l - pc - 2) = 255;
				break;
			case 14:
				buf->at(l - pc - 0) = 255;
				buf->at(l - pc - 1) = 255;
				buf->at(l - pc - 2) = 85;
				break;
			case 15:
				buf->at(l - pc - 0) = 255;
				buf->at(l - pc - 1) = 255;
				buf->at(l - pc - 2) = 255;
				break;
		};
		switch (bin_buffer.at(i + pos) & 0x0F) {
			case 0:
				buf->at(l - pc - 3) = 0;
				buf->at(l - pc - 4) = 0;
				buf->at(l - pc - 5) = 0;
				break;
			case 1:
				buf->at(l - pc - 3) = 0;
				buf->at(l - pc - 4) = 0;
				buf->at(l - pc - 5) = 170;
				break;
			case 2:
				buf->at(l - pc - 3) = 0;
				buf->at(l - pc - 4) = 170;
				buf->at(l - pc - 5) = 0;
				break;
			case 3:
				buf->at(l - pc - 3) = 0;
				buf->at(l - pc - 4) = 170;
				buf->at(l - pc - 5) = 170;
				break;
			case 4:
				buf->at(l - pc - 3) = 170;
				buf->at(l - pc - 4) = 0;
				buf->at(l - pc - 5) = 0;
				break;
			case 5:
				buf->at(l - pc - 3) = 170;
				buf->at(l - pc - 4) = 0;
				buf->at(l - pc - 5) = 170;
				break;
			case 6:
				buf->at(l - pc - 3) = 170;
				buf->at(l - pc - 4) = 85;
				buf->at(l - pc - 5) = 0;
				break;
			case 7:
				buf->at(l - pc - 3) = 170;
				buf->at(l - pc - 4) = 170;
				buf->at(l - pc - 5) = 170;
				break;
			case 8:
				buf->at(l - pc - 3) = 85;
				buf->at(l - pc - 4) = 85;
				buf->at(l - pc - 5) = 85;
				break;
			case 9:
				buf->at(l - pc - 3) = 85;
				buf->at(l - pc - 4) = 85;
				buf->at(l - pc - 5) = 255;
				break;
			case 10:
				buf->at(l - pc - 3) = 85;
				buf->at(l - pc - 4) = 255;
				buf->at(l - pc - 5) = 85;
				break;
			case 11:
				buf->at(l - pc - 3) = 85;
				buf->at(l - pc - 4) = 255;
				buf->at(l - pc - 5) = 255;
				break;
			case 12:
				buf->at(l - pc - 3) = 255;
				buf->at(l - pc - 4) = 85;
				buf->at(l - pc - 5) = 85;
				break;
			case 13:
				buf->at(l - pc - 3) = 255;
				buf->at(l - pc - 4) = 85;
				buf->at(l - pc - 5) = 255;
				break;
			case 14:
				buf->at(l - pc - 3) = 255;
				buf->at(l - pc - 4) = 255;
				buf->at(l - pc - 5) = 85;
				break;
			case 15:
				buf->at(l - pc - 3) = 255;
				buf->at(l - pc - 4) = 255;
				buf->at(l - pc - 5) = 255;
				break;
		};
		pc += 6;
	}
	
}

void map_tik_xpm (std::vector<unsigned char> *bmp, int i, int *pixel) {
	int l = bmp->size() - 1;
	switch (i) {
		case 0:
			bmp->at(l - 0 - *pixel) = 0;
			bmp->at(l - 1 - *pixel) = 0;
			bmp->at(l - 2 - *pixel) = 0;
			break;
		case 1:
			bmp->at(l - 0 - *pixel) = 85;
			bmp->at(l - 1 - *pixel) = 85;
			bmp->at(l - 2 - *pixel) = 85;
			break;
		case 2:
			bmp->at(l - 0 - *pixel) = 170;
			bmp->at(l - 1 - *pixel) = 170;
			bmp->at(l - 2 - *pixel) = 170;
			break;
		case 3:
			bmp->at(l - 0 - *pixel) = 255;
			bmp->at(l - 1 - *pixel) = 255;
			bmp->at(l - 2 - *pixel) = 255;
			break;
		case 4:
			bmp->at(l - 0 - *pixel) = 255;
			bmp->at(l - 1 - *pixel) = 255;
			bmp->at(l - 2 - *pixel) = 255;
			break;
		case 5:
			bmp->at(l - 0 - *pixel) = 70;
			bmp->at(l - 1 - *pixel) = 171;
			bmp->at(l - 2 - *pixel) = 21;
			break;
		case 6:
			bmp->at(l - 0 - *pixel) = 92;
			bmp->at(l - 1 - *pixel) = 226;
			bmp->at(l - 2 - *pixel) = 84;
			break;
		case 7:
			bmp->at(l - 0 - *pixel) = 255;
			bmp->at(l - 1 - *pixel) = 255;
			bmp->at(l - 2 - *pixel) = 85;
			break;
		case 8:
			bmp->at(l - 0 - *pixel) = 171;
			bmp->at(l - 1 - *pixel) = 50;
			bmp->at(l - 2 - *pixel) = 20;
			break;
		case 9:
			bmp->at(l - 0 - *pixel) = 170;
			bmp->at(l - 1 - *pixel) = 170;
			bmp->at(l - 2 - *pixel) = 170;
			break;
		case 10:
			bmp->at(l - 0 - *pixel) = 242;
			bmp->at(l - 1 - *pixel) = 138;
			bmp->at(l - 2 - *pixel) = 253;
			break;
		case 11:
			bmp->at(l - 0 - *pixel) = 81;
			bmp->at(l - 1 - *pixel) = 247;
			bmp->at(l - 2 - *pixel) = 253;
			break;
		case 12:
			bmp->at(l - 0 - *pixel) = 29;
			bmp->at(l - 1 - *pixel) = 79;
			bmp->at(l - 2 - *pixel) = 171;
			break;
		case 13:
			bmp->at(l - 0 - *pixel) = 93;
			bmp->at(l - 1 - *pixel) = 122;
			bmp->at(l - 2 - *pixel) = 252;
			break;
		case 14:
			bmp->at(l - 0 - *pixel) = 170;
			bmp->at(l - 1 - *pixel) = 170;
			bmp->at(l - 2 - *pixel) = 170;
			break;
		case 15:
			bmp->at(l - 0 - *pixel) = 255;
			bmp->at(l - 1 - *pixel) = 255;
			bmp->at(l - 2 - *pixel) = 255;
			break;
	}
	*pixel += 3;
}
