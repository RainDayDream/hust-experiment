#define _CRT_SECURE_NO_WARNINGS
struct SAMPLES
{
	char SAMID[9];  //每组数据的流水号
	int SDA;  // 状态信息a
	int SDB;   //状态信息b
	int SDC;   //状态信息c
	int SF;    // 处理结果f
};