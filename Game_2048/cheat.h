#pragma once
#include <vector>
#include "player.h"
class Cheat {
public:
	//构造函数
	Cheat();

	//使用cheat道具
	void useCheat(vector <Player*> pls, const int& num, const int& order, const string& input, char& ch);

	//受到cheat攻击
	void beCheated(const char& chTrue, char& ch, Player* plr);

private:
	//cheat道具数量
	int cheatNum;

	//cheat道具指令
	string cheatCommand;

};

