#pragma once
#include "player.h"
class Cheat {
public:
	//���캯��
	Cheat();

	//ʹ��cheat����
	void useCheat(Player* plrs, const int& num, const int& order, const string& input, char& ch);

	//�ܵ�cheat����
	void beCheated(const char& chTrue, char& ch, Player* plr);

private:
	//cheat��������
	int cheatNum;

	//cheat����ָ��
	string cheatCommand;

};

