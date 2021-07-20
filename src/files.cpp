#include <fstream>
#include <ostream>
#include "files.h"

using namespace std;

std::vector<unsigned char> readfile(const char* filename, int *size) {  //Thanks LihO i suck at code
	std::streampos fileSize;
	std::ifstream file(filename, std::ios::binary);
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<unsigned char> fileData(fileSize);
	file.read((char*) &fileData[0],
		fileSize
	);
	*size = fileSize;
	file.close();
	return fileData;
}

void ini_write (std::string fil, const char *key, const char *value) {
/*
	FIL = File name
	KEY = Name of the value
	VALUE = The new value
*/
	std::string line, res = "";
	std::ifstream file;
	file.open(fil, std::fstream::in);
	if (file.is_open()) {
		while (getline (file, line)) {
			if (line.substr(0, line.find("=")) == key) {
				res += line.substr(0, line.find("=") + 1) + value + "\n";
			} else {
				res += line + "\n";
			}
		}
	}
	file.close();
	std::ofstream elif;
	elif.open(fil, std::fstream::out);
	elif << res;
	elif.close();
}

std::string read_ini (std::string filename, const char* key) { //gets the data of value
/*
	Filename = The name of the file
	KEY = Name of the value
*/
	std::string line, res;
	std::ifstream file;
	file.open(filename, std::fstream::in);
	if (file.is_open()) {
		while (getline (file, line)) {
			if (line.substr(0, line.find("=")) == key)
				res = line.substr(line.find("=") + 1, line.length());
		}
	}
	file.close();
	return res;
}

file_rw::file_rw(const char *path) {
	fpath = path;
	std::streampos fileSize;
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	file.read((char*) &data[0],
		fileSize
	);
	file.close();
}

std::vector <unsigned char> file_rw::read () {
	return data;
}

void file_rw::write (std::vector<unsigned char> ndata) {
	std::ofstream file(fpath, std::ios::out|std::ios::binary);
	copy(data.cbegin(), data.cend(), std::ostreambuf_iterator<char>(file));
	file.close();
}
