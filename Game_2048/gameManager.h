#pragma once                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#include "player.h"
#include "map.h"
#include "cheat.h"
#include "file.h"
#include "playerActionExecuter.h"
#include "undoAction.h"
#include "actionObserver.h"
#include "log.h"
#include "bonus.h"
#include <cstring>
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

	//玩家关联对象创建
	void createObject(const int& num);

	//游戏玩家命名
	void gamePlayerName(const int& playerNum);

	//游戏指令操作
	void chExecute(bool& sign, const int& playerNum, int& order);

	//反悔操作实现
	bool regretResult(const int& num, int& order);

	//判断游戏结束
	void judgeGameOver(bool& sign);

	//游戏道具：cheat
	void cheatFunc(const int& playerNum, int& order);

	//双人模式结果判断
	void resultJudge(const int& playerNum);

private:
	//游戏模式
	int modeNum;

	//胜利条件
	const int normal;
	const int test;
	int vic;

	//游戏数盘
	Map* map;

	//游戏玩家
	vector <Player*> pls;

	//玩家行为控制器
	vector <PlayerActionExecuter*> aExes;

	//回溯功能控制器
	vector <UndoAction*> undos;

	//操作指令
	char chImple;

	//cheat道具
	Cheat ct;

	//文件模式 
	File* fp;

	//log功能
	bool logSwitch;
	vector <Log*> logs;

	//bonus功能
	bool bonusSwitch;
	vector <Bonus*> bonuses;
};

