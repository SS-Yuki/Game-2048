#pragma once                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#include "player.h"
#include "map.h"
#include "cheat.h"
#include "file.h"
#include "log.h"
#include "bonus.h"
using namespace std;

//��Ϸϵͳ
class GameManager {
public:
	//���캯��
	GameManager(int argc, char* const argv[]);

	//��������
	~GameManager();

	//�����в�������
	void paraProcess(int argc, char* const argv[]);

	//�������������̴�С
	void paraMapSize(int argc, char* const argv[], const int& i);

	//�����ļ�����ģʽ
	void fileTest();

	//��Ϸ��ʼ��
	void gameInit();

	//��Ϸģʽѡ��
	void modeChoosing();

	//��Ϸģʽ���Ż�ȡ
	int modeGet();

	//��Ϸ���У�����ģʽ
	void gameExecute();

	//��Ϸ���У�˫��ģʽ
	void gameExecute(const int& num);

	//��Ϸ�������
	void gamePlayerName(const int& playerNum, Player* plrs);

	//��Ϸָ�����
	void chExecute(bool& sign, const int& playerNum, Player* plrs, int& order);

	//��Ҽӷ�
	void addPlayerScore(Player* plrs, const int& playerNum, const int& order);

	//�ж���Ϸ����
	void judgeGameOver(bool& sign);

	//��Ϸ���ߣ�cheat
	void cheatFunc(const int& playerNum, Player* plrs, int& order);

	//˫��ģʽ����ж�
	void resultJudge(const int& playerNum, Player* plrs);

private:
	//��Ϸģʽ
	int modeNum;

	//ʤ������
	const int normal;
	const int test;
	int vic;

	//��Ϸ����
	Map* map;

	//����ָ��
	char chImple;

	//cheat����
	Cheat ct;

	//�ļ�ģʽ
	File* fp;

	//Logģʽ
	Log* log;

	//Bonusģʽ
	Bonus* bonus;
};

