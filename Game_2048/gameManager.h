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

//游戏系统
class GameManager
{
public:
	//构造函数
	GameManager();

	//游戏难度设置
	void difficultySettings();    

	//游戏模式选择
	void modeChoosing(); 
	
	//游戏模式代号获取
	int modeGet();

	//游戏运行：单人模式
	void gameExecute();	

	//游戏运行：双人模式
	void gameExecute(int num);

	//打印数盘
	void printMap(); 

	//游戏初始化
	void gameInit();

	//实现方块移动
	int impleMap(char ch);

	//四种方向的实现
	void directionJudge(int rowL, int colL, int& x, int& y, int& next, char ch);

	//判断方块是否已满
	bool isFull();

	//判断是否合成目标方块
	bool isWin();

	//随即填充
	void fillMap();

	//双人模式结果判断
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

