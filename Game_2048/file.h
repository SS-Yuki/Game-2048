#pragma once
#include <fstream>
#include "map.h"
using namespace std;

class File {
public:
	//���캯��
	File();

	//��������
	~File();

	//����������
	void setFileNameIn(const string& fIn);

	//���������
	void setFileNameOut(const string& fOut);

	//�鿴���Ʋ�����Ŀ
	int getFileNameNum();

	//�������Ʋ�����Ŀ
	void addFileNameNum();

	//�ļ�����
	void fileIn();

	//�ļ����
	void fileOut();

private:
	//����ָ��
	Map* map;

	//�����ļ�����
	string in;

	//����ļ�����
	string out;

	//�ļ�������Ŀ
	int fileNum;

	//�����ļ��ƶ�����
	char fileDir;
};

