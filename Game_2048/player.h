#pragma once
#include <iostream>
#include <string>


using namespace std;

class Player {
public:
	//���캯��
	Player();

	//�鿴�������
	string getName();

	//�޸��������
	void setName(const string& tname);

	//�鿴��ҷ���
	int getTScore();

	//�޸���ҷ���
	void addScore(const int& add);

	//���cheat����
	bool getCheatState();

	//����cheat����
	void setCheatState(const bool& judge);

	
private:
	//�������
	string name;

	//��ҵ÷�
	int totalScore;

	//cheat����
	bool _beCheated;

	

	


};

