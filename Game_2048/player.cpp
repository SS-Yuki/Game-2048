#include "player.h"


Player::Player() {
	m_name = "default";
	m_totalScore = 0;
}

void Player::nameSet() {
	string name;
	cin >> name;
	m_name = name;
	cin.ignore(INT_MAX, '\n');
}


