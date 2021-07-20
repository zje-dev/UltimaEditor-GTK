#include <fstream>
#include <bitset>
#include <iterator>
#include "./select_ega.h"

#include <iostream>

void change_ega_mono (int x, int y, std::vector<unsigned char> *buffer, const char *path, int color, int tile, int size, int size2, int h) {
	std::vector<int> pixels, prepixls;
	int pixel = 0, r = 0;
	int v[2];
	std::vector<unsigned char> tmp_buf = *buffer;
//	if (h == 32) {
		for (int i = 0; i < size2; i++) {
			v[0] = (tmp_buf.at(i + (tile * size2)) & 0xF0) >> 4;
			v[1] = (tmp_buf.at(i + (tile * size2)) & 0x0F);
			for (int e = 0; e < 2; e++) {
				std::string bin = std::bitset<4>(v[e]).to_string();
				pixels.push_back(bin.at(0) - '0');
				pixels.push_back(bin.at(1) - '0');
				pixels.push_back(bin.at(2) - '0');
				pixels.push_back(bin.at(3) - '0');
			}
		}
//	}
	
	pixels[x + (y * h)] = ((pixels[x + (y * h)] == 0) ? 1 : 0);
	pixel = 0;

	for (int i = 0; i < pixels.size(); i += 8) {
		int f, s;
		for (int e = 0; e < 16; e++) {
			std::string bin = std::bitset<4>(e).to_string();
			if (
				pixels[i] == bin.at(0) - '0' &&
				pixels[i + 1] == bin.at(1) - '0' &&
				pixels[i + 2] == bin.at(2) - '0' &&
				pixels[i + 3] == bin.at(3) - '0'
			)
				f = e;
		}
		for (int e = 0; e < 16; e++) {
			std::string bin = std::bitset<4>(e).to_string();
			if (
				pixels[i + 4] == bin.at(0) - '0' &&
				pixels[i + 5] == bin.at(1) - '0' &&
				pixels[i + 6] == bin.at(2) - '0' &&
				pixels[i + 7] == bin.at(3) - '0'
			)
				s = e;
		}
		tmp_buf.at(pixel + (tile * size2)) = (f << 4) + s;
		pixel += 1;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
}
