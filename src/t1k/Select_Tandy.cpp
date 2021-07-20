#include <fstream>
#include <iterator>
#include "./Select_Tandy.h"

void change_tandy_pixel (int x, int y, std::vector<unsigned char> *buffer, const char *path, int color, int tile, int size, int size2, int h) {
	int pixels[size];
	int pixel = 0;
	std::vector<unsigned char> tmp_buf = *buffer;
	for (int i = 0; i < size2; i++) {
		pixels[pixel + 0] = (tmp_buf[i + (tile * size2)] & 0xF0) >> 4;
		pixels[pixel + 1] = (tmp_buf[i + (tile * size2)] & 0x0F);
		pixel += 2;
	}
	pixels[x + (y * h)] = color;
	int first_byte = 0, second_byte = 0, e = 0;
	for (int i = 0; i < size; i += 2) {
		buffer->at(e + (tile * size2)) = ((pixels[i] << 4) + pixels[i + 1]);
		e += 1;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(buffer->cbegin(), buffer->cend(), std::ostream_iterator<char>(file));
}
