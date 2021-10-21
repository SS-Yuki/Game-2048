#pragma once
#include "playerEventObserver.h"
#include "map.h"

class Log : public PlayerEventObserver {
public:
    //构造函数
    Log(Map* map);

    //析构函数
    virtual ~Log();

    //获取方向、分数；执行功能
    virtual void messageDirScore(const char& dir, int& mergeScore);

    //获取玩家姓名
    virtual void messageName(const string& name);

    //获取当前时间
    virtual void messageTime(tm* nowTime);  

private:
    //棋盘指针
    Map* map;

    //文件名
    string logName;

    //玩家姓名
    string pName;

    //玩家分数
    int score;

    //移动方向
    char dir;

    //时间结构
    tm* time;

    //方向转化
    string dirE(const char& dir);

    //文件操作
    void fileLog();
};
