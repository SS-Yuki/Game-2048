#pragma once                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#include "player.h"
#include "map.h"
#include "cheat.h"
#include "file.h"
#include "log.h"
#include "bonus.h"
using namespace std;

//游戏系统
class GameManager {
public:
	//构造函数
	GameManager(int argc, char* const argv[]);

	//析构函数
	~GameManager();

	//命令行参数处理
	void paraProcess(int argc, char* const argv[]);

	//命令行设置棋盘大小
	void paraMapSize(int argc, char* const argv[], const int& i);

	//进入文件测试模式
	void fileTest();

	//游戏初始化
	void gameInit();

	//游戏模式选择
	void modeChoosing();

	//游戏模式代号获取
	int modeGet();

	//游戏运行：单人模式
	void gameExecute();

	//游戏运行：双人模式
	void gameExecute(const int& num);

	//游戏玩家命名
	void gamePlayerName(const int& playerNum, Player* plrs);

	//游戏指令操作
	void chExecute(bool& sign, const int& playerNum, Player* plrs, int& order);

	//玩家加分
	void addPlayerScore(Player* plrs, const int& playerNum, const int& order);

	//判断游戏结束
	void judgeGameOver(bool& sign);

	//游戏道具：cheat
	void cheatFunc(const int& playerNum, Player* plrs, int& order);

	//双人模式结果判断
	void resultJudge(const int& playerNum, Player* plrs);

private:
	//游戏模式
	int modeNum;

	//胜利条件
	const int normal;
	const int test;
	int vic;

	//游戏数盘
	Map* map;

	//操作指令
	char chImple;

	//cheat道具
	Cheat ct;

	//文件模式
	File* fp;

	//Log模式
	Log* log;

	//Bonus模式
	Bonus* bonus;
};

