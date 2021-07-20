#pragma once
#ifndef CGA_H
#define CGA_H

#include <vector>

void black_cga (std::vector<unsigned char>*, int, bool);
void black_cya (std::vector<unsigned char>*, int, bool);
void black_mag (std::vector<unsigned char>*, int, bool);
void black_whi (std::vector<unsigned char>*, int, bool);

void cga_to_hex (int, std::vector<unsigned char>*, int);

#endif
