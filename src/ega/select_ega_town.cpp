#include <fstream>
#include <bitset>
#include <iterator>
#include "./select_ega.h"

int ega_color_town (int color[16], int l) {
	int result[4] ={0, 0, 0, 0},
	blue[8] =      {0, 0, 0, 0, 0, 0, 0, 0},
	green[8] =     {0, 0, 0, 0, 0, 0, 0, 0},
	red[8] =       {0, 0, 0, 0, 0, 0, 0, 0},
	intensity[8] = {0, 0, 0, 0, 0, 0, 0, 0},
	prev[8] =      {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 8; i++) {
		blue[i] = im_blue(color[i]);
		green[i] = is_green(color[i]);
		red[i] = is_red(color[i]);
		intensity[i] = is_white(color[i]);
	}
	int e = 0, c = 0;
	for (int f = 0; f < 2; f++) {
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
	c = 2;
	for (int f = 0; f < 2; f++) {
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
	c = 4;
	for (int f = 0; f < 2; f++) {
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
	c = 6;
	for (int f = 0; f < 2; f++) {
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
	for (int i = 0; i < 8; i += 2) {
		result[e] = (prev[i] << 4) + prev[i + 1];
		e++;
	}
	return result[l];
}

int ega_town_format (int b[4], int g[4], int r[4], int i[4], int l) {
	int arr[8];
	for (int e = 0; e < 8; e++)
		arr[e] = 0;
	int pixel = 0;	
	for (int e = 0; e < 2; e++) {
		std::string bin = std::bitset<4>(b[e]).to_string();
		arr[pixel] += (bin.at(0) - '0');
		arr[pixel + 1] += (bin.at(1) - '0');
		arr[pixel + 2] += (bin.at(2) - '0');
		arr[pixel + 3] += (bin.at(3) - '0');
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 2; e++) {
		std::string bin = std::bitset<4>(g[e]).to_string();
		arr[pixel] += (bin.at(0) - '0') * 2;
		arr[pixel + 1] += (bin.at(1) - '0') * 2;
		arr[pixel + 2] += (bin.at(2) - '0') * 2;
		arr[pixel + 3] += (bin.at(3) - '0') * 2;
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 2; e++) {
		std::string bin = std::bitset<4>(r[e]).to_string();
		arr[pixel] += (bin.at(0) - '0') * 4;
		arr[pixel + 1] += (bin.at(1) - '0') * 4;
		arr[pixel + 2] += (bin.at(2) - '0') * 4;
		arr[pixel + 3] += (bin.at(3) - '0') * 4;
		pixel += 4;
	}
	pixel = 0;
	for (int e = 0; e < 2; e++) {
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

void change_ega_town (int x, int y, std::vector<unsigned char> *buffer, const char *path, int color, int tile, int size, int size2, int h) {
	int pixels[64];
	int pixel = 0;
	std::vector<unsigned char> tmp_buf = *buffer;
	for (int i = 0; i < 32; i += 4) {
		int b[2] = {
			(tmp_buf.at(i + (tile * 32)) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 32)) & 0x0F)
		},
		g[2] = {
			(tmp_buf.at(i + (tile * 32) + 1) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 32) + 1) & 0x0F)
		},
		r[2] = {
			(tmp_buf.at(i + (tile * 32) + 2) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 32) + 2) & 0x0F)
		},
		iT[2] = {
			(tmp_buf.at(i + (tile * 32) + 3) & 0xF0) >> 4,
			(tmp_buf.at(i + (tile * 32) + 3) & 0x0F)
		};
		pixels[pixel] = ega_town_format(b, g, r, iT, 0);
		pixels[pixel + 1] = ega_town_format(b, g, r, iT, 1);
		pixels[pixel + 2] = ega_town_format(b, g, r, iT, 2);
		pixels[pixel + 3] = ega_town_format(b, g, r, iT, 3);
		pixels[pixel + 4] = ega_town_format(b, g, r, iT, 4);
		pixels[pixel + 5] = ega_town_format(b, g, r, iT, 5);
		pixels[pixel + 6] = ega_town_format(b, g, r, iT, 6);
		pixels[pixel + 7] = ega_town_format(b, g, r, iT, 7);
		pixel += 8;
	}
	pixel = 0;
	pixels[x + (y * 8)] = color;
	for (int i = 0; i < 64; i += 8) {
		int color[8] = {pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3], pixels[i + 4], pixels[i + 5], pixels[i + 6], pixels[i + 7]};
		tmp_buf.at(pixel + (tile * 32)) = ega_color_town(color, 0);
		tmp_buf.at(pixel + (tile * 32) + 1) = ega_color_town(color, 1);
		tmp_buf.at(pixel + (tile * 32) + 2) = ega_color_town(color, 2);
		tmp_buf.at(pixel + (tile * 32) + 3) = ega_color_town(color, 3);
		pixel += 4;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
}

