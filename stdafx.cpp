#include "stdafx.h"
HANDLE stdHandle = NULL;
HANDLE fileHandle = NULL;
void ConsoleWrite(const char *lpBuffer) {
#ifdef LOG
	if (stdHandle == NULL)
		stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (fileHandle == NULL)
		fileHandle = CreateFile("winhttplog.txt",GENERIC_WRITE, 1 | 2, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(fileHandle, lpBuffer, strlen(lpBuffer), NULL, NULL);
	WriteConsole(stdHandle, lpBuffer, strlen(lpBuffer), NULL, NULL);
#endif
}

std::string PrintCharArray(const char *buffer, int length) {
	std::string output = "";
	for (int i = 0; i < length; i++) {
		output = output + " " + n2hexstr((buffer[i]), sizeof(char) << 1);
	}
	return output;
}