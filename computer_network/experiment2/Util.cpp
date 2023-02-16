#include "Util.h"
#include <string>
#include <chrono>
FILE* Util::fp = nullptr;
const char* Util::filePath = "./rdt.log";
Util::Util()
{
}
void Util::print(initializer_list<string> il)
{
	string message;
	for (auto p = il.begin(); p != il.end(); p++)
		message += *p;
	char* str = new char[1024];
	sprintf(str, "%s\n", message.c_str());
	if (str == nullptr)
		return;
	if (fp == nullptr)
		fp = new FILE();
	if (fp != nullptr) {
		fopen_s(&fp, filePath, "a+");
		if (fp != nullptr) {
			fprintf(fp, "%s", str);
			fclose(fp);
		}
	}
	cout << str;
}

Util::~Util()
{
	if (fp != nullptr)
		fclose(fp);
}
