#include <initializer_list>
#include <vector>

void black_cga (std::vector<unsigned char> *buf, int pos, bool one_two) {
	buf->at(pos - (one_two ? 4 : 1)) = ((unsigned char)0);
	buf->at(pos - (one_two ? 5 : 2)) = ((unsigned char)0);
	buf->at(pos - (one_two ? 6 : 3)) = ((unsigned char)0);
}

void black_cya (std::vector<unsigned char> *buf, int pos, bool one_two) {
	buf->at(pos - (one_two ? 4 : 1)) = ((unsigned char)0);
	buf->at(pos - (one_two ? 5 : 2)) = ((unsigned char)204);
	buf->at(pos - (one_two ? 6 : 3)) = ((unsigned char)204);
}

void black_mag (std::vector<unsigned char> *buf, int pos, bool one_two) {
	buf->at(pos - (one_two ? 4 : 1)) = ((unsigned char)204);
	buf->at(pos - (one_two ? 5 : 2)) = ((unsigned char)0);
	buf->at(pos - (one_two ? 6 : 3)) = ((unsigned char)204);
}

void black_whi (std::vector<unsigned char> *buf, int pos, bool one_two) {
	buf->at(pos - (one_two ? 4 : 1)) = ((unsigned char)204);
	buf->at(pos - (one_two ? 5 : 2)) = ((unsigned char)204);
	buf->at(pos - (one_two ? 6 : 3)) = ((unsigned char)204);
}

void cga_to_hex (int c, std::vector<unsigned char> *buf, int pos) {
	const int new_pos = buf->size() - pos;
	switch (c) {
		case 0:
			black_cga(buf, new_pos, false);
			black_cga(buf, new_pos, true);
			break;
		case 1:
			black_cga(buf, new_pos, false);
			black_cya(buf, new_pos, true);
			break;
		case 2:
			black_cga(buf, new_pos, false);
			black_mag(buf, new_pos, true);
			break;
		case 3:
			black_cga(buf, new_pos, false);
			black_whi(buf, new_pos, true);
			break;
		case 4:
			black_cya(buf, new_pos, false);
			black_cga(buf, new_pos, true);
			break;
		case 5:
			black_cya(buf, new_pos, false);
			black_cya(buf, new_pos, true);
			break;
		case 6:
			black_cya(buf, new_pos, false);
			black_mag(buf, new_pos, true);
			break;
		case 7:
			black_cya(buf, new_pos, false);
			black_whi(buf, new_pos, true);
			break;
		case 8:
			black_mag(buf, new_pos, false);
			black_cga(buf, new_pos, true);
			break;
		case 9:
			black_mag(buf, new_pos, false);
			black_cya(buf, new_pos, true);
			break;
		case 10:
			black_mag(buf, new_pos, false);
			black_mag(buf, new_pos, true);
			break;
		case 11:
			black_mag(buf, new_pos, false);
			black_whi(buf, new_pos, true);
			break;
		case 12:
			black_whi(buf, new_pos, false);
			black_cga(buf, new_pos, true);
			break;
		case 13:
			black_whi(buf, new_pos, false);
			black_cya(buf, new_pos, true);
			break;
		case 14:
			black_whi(buf, new_pos, false);
			black_mag(buf, new_pos, true);
			break;
		case 15:
			black_whi(buf, new_pos, false);
			black_whi(buf, new_pos, true);
			break;
	}
}
