#pragma once
#include <fstream>
#include <vector>
#include <string>
#ifndef FILES_H
#define FILES_H

#define map_cga_path (char*)"./img/castle/map.bmp"

//CGA
#define water_cga_path (char*)"./img/tiles_normal.bmp"
#define town_cga_path (char*)"./img/town_normal.bmp"
#define space_cga_path (char*)"./img/space_normal.bmp"
#define fight_cga_path (char*)"./img/fight_normal.bmp"
#define castle_cga_path (char*)"./img/castle/castle_cga.bmp"

//FILES PREFIX
#define cas_path_prefix (char*)"./img/Town Castle/town_cas_cga_"
#define config_ini (char*)"./ud.ini"

std::vector<unsigned char> readfile(const char*, int*);

void ini_write (std::string fil, const char *key, const char *);
std::string read_ini (std::string, const char*);

class file_rw {
	private:
		std::vector <unsigned char> data;
		char *fpath;
	public:
		file_rw (const char*);
		void write (std::vector<unsigned char>);
		std::vector <unsigned char> read ();
};

#endif
