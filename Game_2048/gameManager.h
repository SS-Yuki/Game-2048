#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include "player.h"
#define UP 'w'
#define DOWN 'z'
#define LEFT 'a'
#define RIGHT 's'

using namespace std;

//��Ϸϵͳ
class GameManager
{
public:
	//���캯��
	GameManager();

	//��Ϸ�Ѷ�����
	void difficultySettings();    

	//��Ϸģʽѡ��
	void modeChoosing(); 
	
	//��Ϸģʽ���Ż�ȡ
	int modeGet();

	//��Ϸ���У�����ģʽ
	void gameExecute();	

	//��Ϸ���У�˫��ģʽ
	void gameExecute(int num);

	//��ӡ����
	void printMap(); 

	//��Ϸ��ʼ��
	void gameInit();

	//ʵ�ַ����ƶ�
	int impleMap(char ch);

	//���ַ����ʵ��
	void directionJudge(int rowL, int colL, int& x, int& y, int& next, char ch);

	//�жϷ����Ƿ�����
	bool isFull();

	//�ж��Ƿ�ϳ�Ŀ�귽��
	bool isWin();

	//�漴���
	void fillMap();

	//˫��ģʽ����ж�
	void resultJudge(Player* players, int num);

private:
	int map[4][4];
	int m_diffy[2];
	int m_dSign;
	int m_modeNum;
	int m_score;
	bool m_isChange;
	bool endSign;
};

