#include "./convert_ultima_into_xpm.h"
#include "../graphic/start_window.h"
#include "../files.h"
#include "../cga/cga_select.h"
#include "../ega/ega_select.h"
#include "../t1k/Tandy_Select.h"
//#include "../map/map_pixel.h"

std::string get_cas (int index) {
	std::string cas = (std::string(cas_path_prefix) + (index < 10 ? "0" : "") + std::to_string((int)index) + ".bmp");
	return cas;
}

