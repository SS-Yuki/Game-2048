#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include <iomanip>
#include <vector>
#include <string>
#include "playerEventObserver.h"
using namespace std;

#define UP 'w'
#define DOWN 'z'
#define LEFT 'a'
#define RIGHT 's'
const char direct[4] = { UP, LEFT, RIGHT, DOWN };

//坐标类型
struct Coor {
    int x;
    int y;
};

class Map {
public:
    //构造函数
    Map();

    //改变棋盘大小
    void changeSize(const int& num);

    //单行移动操作
    void moveArray(vector <int>& arr);

    //单行合并操作
    void mergeArray(vector <int>& arr);

    //单行操作结果
    void resultArray(vector <int>& arr);

    //移动测验
    int moveTest(const char& chMove);

    //移动
    void moveResult(const char& chMove);

    //打印数盘
    void printMap();

    //数盘初始化
    void mapInit();

    //判断可移动方向
    int canMoveSum();

    //随机填充并返回随机坐标
    Coor appendBlock();

    //判断方块是否已满
    bool isFull();

    //获取填满标志
    bool getFull();

    //判断是否合成目标方块
    bool isWin(const int& goal);

    //获取数盘大小
    int getSize();

    //获取一轮分数
    int getScore();

    //数盘赋值
    int& setNum(const int& i, const int& j);

    //可移动方向获取
    int getCanDir(const int& i);

    //获取移动判断值
    int getCanMove();

    //添加观察者
    void addEventObserver(PlayerEventObserver* observer);

    //移除观察者
    void removeEventObserver(PlayerEventObserver* observer);

    //返回玩家姓名
    string getPlayerName(const string& name);

    //返回当前时间
    struct tm* getTime();

private:
    //数盘矩阵
    vector <vector <int>> matrix;

    //测试矩阵
    vector <vector <int>> _matrix;

    //数盘大小
    int size;

    //合并得分
    int merScore;

    //判断可否移动
    int canMove;

    //可移动方向判断
    int canDir[4];

    //数盘填满标志
    bool fullMap;

    //随机数坐标
    Coor ran;

    //观察者
    vector<PlayerEventObserver*> observers;

};




