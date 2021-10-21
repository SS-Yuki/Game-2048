#pragma once
#include <iostream>
#include <string>

using namespace std;

class Player {
public:
	//构造函数
	Player();

	//查看玩家姓名
	string getName();

	//修改玩家姓名
	void setName(const string& tname);

	//查看玩家分数
	int getTScore();

	//修改玩家分数
	void changeScore(const int& add);

	//获得cheat属性
	bool getCheatState();

	//更改cheat属性
	void setCheatState(const bool& judge);

	
private:
	//玩家名称
	string name;

	//玩家得分
	int totalScore;

	//cheat属性
	bool _beCheated;

	

	


};

