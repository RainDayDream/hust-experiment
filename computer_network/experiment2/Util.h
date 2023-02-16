#ifndef UTIL_H
#define UTIL_H
#pragma once
class Util
{
public:
	static FILE* fp;
	static const char* filePath;
public:
	Util();
	~Util();
	static void print(initializer_list<string> il);
};
#endif