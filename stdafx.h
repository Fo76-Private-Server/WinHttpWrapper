#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <iostream>
#include <sstream>


void ConsoleWrite(const char *lpBuffer);
template <typename I> std::string n2hexstr(I, size_t);

//https://stackoverflow.com/a/33447587/8481710
template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
	static const char* digits = "0123456789ABCDEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
		rc[i] = digits[(w >> j) & 0x0f];
	return rc;
}

std::string PrintCharArray(const char *buffer, int length);