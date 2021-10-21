#pragma once
#include "playerEventObserver.h"
#include "map.h"

class Bonus : public PlayerEventObserver {
public:
	//���캯��
	Bonus(Map* map);

	//��������
	~Bonus();

	//��ȡ���򡢷�����ִ�й���
	virtual void messageDirScore(const char& dir, int& mergeScore); 

	//��ȡ�������
	virtual void messageName(const string& name);

	//��ȡ��ǰʱ��
	virtual void messageTime(tm* nowTime);

	//��log����
	void changeLog();
private:
	//����ָ��
	Map* map;

	//�������
	string pName;

	//�ļ���
	string logName;

	//ʱ��ṹ
	tm* time;

	//ʱ�̼�ʱ����
	clock_t last;
	clock_t now;
	double timeLag;

	//��־����
	bool loged;
	
	//����ʱ����
	double getTimeLag();

	//�ļ�����
	void fileLog();
};