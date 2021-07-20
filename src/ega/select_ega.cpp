#include <fstream>
#include <bitset>
#include <iterator>
#include "./select_ega.h"

int blue_colors[] = {1, 3, 5, 7, 9, 11, 13, 15},
green_colors[] = {2, 3, 6, 7, 10, 11, 14, 15},
red_colors[] = {4, 5, 6, 7, 12, 13, 14, 15},
white_colors[] = {8, 9, 10, 11, 12, 13, 14, 15};

int ega_format (int b[4], int g[4], int r[4], int i[4], int l) {
	int arr[16];
	for (int e = 0; e < 16; e++)
		arr[e] = 0;
	int pixel = 0;
	for (int e = 0; e < 4; e++) {
		std::string bin = std::bitset<4>(b[e]).to_string();
		arr[pixel] += (bin.at(0) - '0');
		arr[pixel + 1] += (bin.at(1) - '0');
		arr[pixel + 2] += (bin.at(2) - '0');
		arr[pixel + 3] += (bin.at(3) - '0');
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 4; e++) {
		std::string bin = std::bitset<4>(g[e]).to_string();
		arr[pixel] += (bin.at(0) - '0') * 2;
		arr[pixel + 1] += (bin.at(1) - '0') * 2;
		arr[pixel + 2] += (bin.at(2) - '0') * 2;
		arr[pixel + 3] += (bin.at(3) - '0') * 2;
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 4; e++) {
		std::string bin = std::bitset<4>(r[e]).to_string();
		arr[pixel] += (bin.at(0) - '0') * 4;
		arr[pixel + 1] += (bin.at(1) - '0') * 4;
		arr[pixel + 2] += (bin.at(2) - '0') * 4;
		arr[pixel + 3] += (bin.at(3) - '0') * 4;
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 4; e++) {
		std::string bin = std::bitset<4>(i[e]).to_string();
		arr[pixel] += (bin.at(0) - '0') * 8;
		arr[pixel + 1] += (bin.at(1) - '0') * 8;
		arr[pixel + 2] += (bin.at(2) - '0') * 8;
		arr[pixel + 3] += (bin.at(3) - '0') * 8;
		pixel += 4;
	}
	pixel = 0;
	return arr[l];
}

int ega_color_format (int color[16], int l) {
	int result[8] = {0, 0, 0, 0, 0, 0, 0, 0},
	blue[16] =      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	green[16] =     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	red[16] =       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	intensity[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	prev[16] =      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 16; i++) {
		blue[i] = im_blue(color[i]);
		green[i] = is_green(color[i]);
		red[i] = is_red(color[i]);
		intensity[i] = is_white(color[i]);
	}
	int e = 0, c = 0;
	for (int f = 0; f < 4; f++) {
		for (int i = 0; i < 16; i++) {
			std::string bin = std::bitset<4>(i).to_string();
			if (
				(bin.at(0) - '0') == blue[e] &&
				(bin.at(1) - '0') == blue[e + 1] &&
				(bin.at(2) - '0') == blue[e + 2]  &&
				(bin.at(3) - '0') == blue[e + 3]
			) {
				prev[c] = i;
				e += 4;
				c++; //XDDDDDDDD
			}
		}
	}
	e = 0;
	c = 4;
	for (int f = 0; f < 4; f++) {
		for (int i = 0; i < 16; i++) {
			std::string bin = std::bitset<4>(i).to_string();
			if (
				(bin.at(0) - '0') == green[e] &&
				(bin.at(1) - '0') == green[e + 1] &&
				(bin.at(2) - '0') == green[e + 2]  &&
				(bin.at(3) - '0') == green[e + 3]
			) {
				prev[c] = i;
				e += 4;
				c++;
			}
		}
	}
	e = 0;
	c = 8;
	for (int f = 0; f < 4; f++) {
		for (int i = 0; i < 16; i++) {
			std::string bin = std::bitset<4>(i).to_string();
			if (
				(bin.at(0) - '0') == red[e] &&
				(bin.at(1) - '0') == red[e + 1] &&
				(bin.at(2) - '0') == red[e + 2]  &&
				(bin.at(3) - '0') == red[e + 3]
			) {
				prev[c] = i;
				e += 4;
				c++; //XDDDDDDDD
			}
		}
	}
	e = 0;
	c = 12;
	for (int f = 0; f < 4; f++) {
		for (int i = 0; i < 16; i++) {
			std::string bin = std::bitset<4>(i).to_string();
			if (
				(bin.at(0) - '0') == intensity[e] &&
				(bin.at(1) - '0') == intensity[e + 1] &&
				(bin.at(2) - '0') == intensity[e + 2]  &&
				(bin.at(3) - '0') == intensity[e + 3]
			) {
				prev[c] = i;
				e += 4;
				c++; //XDDDDDDDD
			}
		}
	}
	e = 0;
	for (int i = 0; i < 16; i += 2) {
		result[e] = (prev[i] << 4) + prev[i + 1];
		e++;
	}
	return result[l];
}

int im_blue (int color) {
	for (int b = 0; b < 8; b++) {
		if (color == blue_colors[b])
			return 1;
	}
	return 0;
}

int is_red (int color) {
	for (int r = 0; r < 8; r++) {
		if (color == red_colors[r])
			return 1;
	}
	return 0;
}

int is_green (int color) {
	for (int g = 0; g < 8; g++) {
		if (color == green_colors[g])
			return 1;
	}
	return 0;
}

int is_white (int color) {
	for (int i = 0; i < 8; i++) {
		if (color == white_colors[i])
			return 1;
	}
	return 0;
}

void change_ega_pixel (int x, int y, std::vector<unsigned char> *buffer, const char *path, int color, int tile, int size, int size2, int h) {
	int pixels[256];
	int pixel = 0;
	std::vector<unsigned char> tmp_buf = *buffer;
	for (int i = 0; i < 128; i += 8) {
		int b[4] = {
			(tmp_buf.at(i + (tile * 128)) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128)) & 0x0F),
			(tmp_buf.at(i + (tile * 128) + 1) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 1) & 0x0F)
		};
		int g[4] = {
			(tmp_buf.at(i + (tile * 128) + 2) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 2) & 0x0F),
			(tmp_buf.at(i + (tile * 128) + 3) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 3) & 0x0F)
		};
		int r[4] = {
			(tmp_buf.at(i + (tile * 128) + 4) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 4) & 0x0F),
			(tmp_buf.at(i + (tile * 128) + 5) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 5) & 0x0F)
		};
		int iN[4] = {
			(tmp_buf.at(i + (tile * 128) + 6) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 6) & 0x0F),
			(tmp_buf.at(i + (tile * 128) + 7) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 128) + 7) & 0x0F)
		};
		pixels[pixel] = ega_format(b, g, r, iN, 0);
		pixels[pixel + 1] = ega_format(b, g, r, iN, 1);
		pixels[pixel + 2] = ega_format(b, g, r, iN, 2);
		pixels[pixel + 3] = ega_format(b, g, r, iN, 3);
		pixels[pixel + 4] = ega_format(b, g, r, iN, 4);
		pixels[pixel + 5] = ega_format(b, g, r, iN, 5);
		pixels[pixel + 6] = ega_format(b, g, r, iN, 6);
		pixels[pixel + 7] = ega_format(b, g, r, iN, 7);
		pixels[pixel + 8] = ega_format(b, g, r, iN, 8);
		pixels[pixel + 9] = ega_format(b, g, r, iN, 9);
		pixels[pixel + 10] = ega_format(b, g, r, iN, 10);
		pixels[pixel + 11] = ega_format(b, g, r, iN, 11);
		pixels[pixel + 12] = ega_format(b, g, r, iN, 12);
		pixels[pixel + 13] = ega_format(b, g, r, iN, 13);
		pixels[pixel + 14] = ega_format(b, g, r, iN, 14);
		pixels[pixel + 15] = ega_format(b, g, r, iN, 15);
		pixel += 16;
	}
	pixel = 0;
	pixels[x + (y * 16)] = color;
	for (int i = 0; i < 256; i += 16) {
		int color[16] = {pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3], pixels[i + 4], pixels[i + 5], pixels[i + 6], pixels[i + 7], pixels[i + 8], pixels[i + 9], pixels[i + 10], pixels[i + 11], pixels[i + 12], pixels[i + 13], pixels[i + 14], pixels[i + 15]};
		tmp_buf.at(pixel + (tile * 128)) = ega_color_format(color, 0);
		tmp_buf.at(pixel + (tile * 128) + 1) = ega_color_format(color, 1);
		tmp_buf.at(pixel + (tile * 128) + 2) = ega_color_format(color, 2);
		tmp_buf.at(pixel + (tile * 128) + 3) = ega_color_format(color, 3);
		tmp_buf.at(pixel + (tile * 128) + 4) = ega_color_format(color, 4);
		tmp_buf.at(pixel + (tile * 128) + 5) = ega_color_format(color, 5);
		tmp_buf.at(pixel + (tile * 128) + 6) = ega_color_format(color, 6);
		tmp_buf.at(pixel + (tile * 128) + 7) = ega_color_format(color, 7);
		pixel += 8;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
}
