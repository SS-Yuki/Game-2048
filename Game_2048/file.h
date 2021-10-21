#pragma once
#include <fstream>
#include "map.h"
using namespace std;

class File {
public:
	//构造函数
	File();

	//析构函数
	~File();

	//设置输入名
	void setFileNameIn(const string& fIn);

	//设置输出名
	void setFileNameOut(const string& fOut);

	//查看名称参数数目
	int getFileNameNum();

	//增加名称参数数目
	void addFileNameNum();

	//文件输入
	void fileIn();

	//文件输出
	void fileOut();

private:
	//棋盘指针
	Map* map;

	//输入文件名称
	string in;

	//输出文件名称
	string out;

	//文件名称数目
	int fileNum;

	//输入文件移动命令
	char fileDir;
};

