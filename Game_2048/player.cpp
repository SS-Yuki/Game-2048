#include "player.h"

//构造函数
Player::Player() {
	name = "default";
	totalScore = 0;
	_beCheated = false;
}

//查看玩家姓名
string Player::getName() {
	return name;
}

//修改玩家姓名
void Player::setName(const string& tname) {
	name = tname;
}

//查看玩家分数
int Player::getTScore() {
	return totalScore;
}

//修改玩家分数
void Player::changeScore(const int& add) {
	totalScore += add;
}

//获得cheat属性
bool Player::getCheatState() {
	return _beCheated;
}

//更改cheat属性
void Player::setCheatState(const bool& judge) {
	_beCheated = judge;
}




