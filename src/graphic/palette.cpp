#include "./palette.h"
#include "../cga/cga.h"

int check_palette (std::string p) {
	if (p == CGA_NAME)
		return 0;
	return -1;
}
