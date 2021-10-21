#pragma once
#include "playerEventObserver.h"
#include "map.h"

class Bonus : public PlayerEventObserver {
public:
	//构造函数
	Bonus(Map* map);

	//析构函数
	~Bonus();

	//获取方向、分数；执行功能
	virtual void messageDirScore(const char& dir, int& mergeScore); 

	//获取玩家姓名
	virtual void messageName(const string& name);

	//获取当前时间
	virtual void messageTime(tm* nowTime);

	//打开log功能
	void changeLog();
private:
	//棋盘指针
	Map* map;

	//玩家姓名
	string pName;

	//文件名
	string logName;

	//时间结构
	tm* time;

	//时刻及时间间隔
	clock_t last;
	clock_t now;
	double timeLag;

	//日志开关
	bool loged;
	
	//计算时间间隔
	double getTimeLag();

	//文件操作
	void fileLog();
};