#include <fstream>
#include <iterator>
#include "./select_cga.h"

int mx_color (int p_v, int n_v, bool s) {
	return colors_table_cga[n_v][p_v][s];
}

void change_pixel (int x, int y, std::vector<unsigned char> *buffer, const char* path, int color, int tile, int y_m, int size, int size2) {
	int pixels[size];
	int pixel = 0;
	std::vector<unsigned char> tmp_buf = *buffer;
	for (int i = 0; i < size2; i++) {
		pixels[pixel] = byte_to_color((tmp_buf[i + (tile * size2)] & 0xF0) >> 4, false);
		pixels[pixel + 1] = byte_to_color((tmp_buf[i + (tile * size2)] & 0xF0) >> 4, true);
		pixels[pixel + 2] = byte_to_color(tmp_buf[i + (tile * size2)] & 0x0F, false);
		pixels[pixel + 3] = byte_to_color(tmp_buf[i + (tile * size2)] & 0x0F, true);
		pixel += 4;
	}
	pixels[x + (y * y_m)] = color;
	int first_byte = 0, second_byte = 0, e = 0;
	for (int i = 0; i < size; i += 4) {
		first_byte = color_to_byte(pixels[i], pixels[i + 1]);
		second_byte = color_to_byte(pixels[i + 2], pixels[i + 3]);
		buffer->at(e + (tile * size2)) = ((first_byte << 4) + second_byte);
		e += 1;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(buffer->cbegin(), buffer->cend(), std::ostream_iterator<char>(file));
	file.close();
}

int color_to_byte (int byte1, int byte2) { //PATTERN
	int result = 0;
	switch (byte1) {
		case 0:
			switch (byte2) {
				case 0:
					result = 0;
					break;
				case 1:
					result = 3;
					break;
				case 2:
					result = 1;
					break;
				case 3:
					result = 2;
					break;
			}
			break;
		case 1:
			switch (byte2) {
				case 0:
					result = 12;
					break;
				case 1:
					result = 15;
					break;
				case 2:
					result = 13;
					break;
				case 3:
					result = 14;
					break;
			}
			break;
		case 2:
			switch (byte2) {
				case 0:
					result = 4;
					break;
				case 1:
					result = 7;
					break;
				case 2:
					result = 5;
					break;
				case 3:
					result = 6;
					break;
			}
			break;
		case 3:
			switch (byte2) {
				case 0:
					result = 8;
					break;
				case 1:
					result = 11;
					break;
				case 2:
					result = 9;
					break;
				case 3:
					result = 10;
					break;
			}
			break;
		default:
			result = 0;
	};
	return result;
}

int byte_to_color (int color, bool c) {
	int result = 0;
	switch (color) {
		case 0:
			result = (!c ? 0 : 0);
			break;
		case 1:
			result = (!c ? 0 : 2);
			break;
		case 2:
			result = (!c ? 0 : 3);
			break;
		case 3:
			result = (!c ? 0 : 1);
			break;
		case 4:
			result = (!c ? 2 : 0);
			break;
		case 5:
			result = (!c ? 2 : 2);
			break;
		case 6:
			result = (!c ? 2 : 3);
			break;
		case 7:
			result = (!c ? 2 : 1);
			break;
		case 8:
			result = (!c ? 3 : 0);
			break;
		case 9:
			result = (!c ? 3 : 2);
			break;
		case 10:
			result = (!c ? 3 : 3);
			break;
		case 11:
			result = (!c ? 3 : 1);
			break;
		case 12:
			result = (!c ? 1 : 0);
			break;
		case 13:
			result = (!c ? 1 : 2);
			break;
		case 14:
			result = (!c ? 1 : 3);
			break;
		case 15:
			result = (!c ? 1 : 1);
			break;
		default:
			result = (!c ? 0 : 0);
			break;
	};
	return result;
}
