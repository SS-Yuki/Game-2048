#include "player.h"

//���캯��
Player::Player() {
	name = "default";
	totalScore = 0;
	_beCheated = false;
}

//�鿴�������
string Player::getName() {
	return name;
}

//�޸��������
void Player::setName(const string& tname) {
	name = tname;
}

//�鿴��ҷ���
int Player::getTScore() {
	return totalScore;
}

//�޸���ҷ���
void Player::addScore(const int& add) {
	totalScore += add;
}

//���cheat����
bool Player::getCheatState() {
	return _beCheated;
}

//����cheat����
void Player::setCheatState(const bool& judge) {
	_beCheated = judge;
}




