#include "log.h"

//构造函数
Log::Log(Map* map) : map(map) {
    map->addEventObserver(this);
    logName = "log.txt";
    pName = "";
    score = 0;
    dir = '0';
    time = NULL;
}

//析构函数
Log::~Log() {
    map->removeEventObserver(this);
}

//获取方向、分数；执行功能
void Log::messageDirScore(const char& dir, int& mergeScore) {
    this->dir = dir;
    this->score = mergeScore;
    if (score > 0)
        fileLog();
}

//获取玩家姓名
void Log::messageName(const string& name) {
    this-> pName = name;
}

//获取当前时间
void Log::messageTime(tm* nowTime) {
    this->time = nowTime;
}

//方向转化
string Log::dirE(const char& dir) {
    switch (dir) {
    case 'w': return "UP";
    case 'z':return "DOWN";
    case 'a':return "LEFT";
    case 's':return "RIGHT";
    default:return "";
    }
}

//文件操作
void Log::fileLog() {
    ofstream ofs;
    ofs.open(logName, ios::out | ios::app);
    ofs << pName << " ";
    ofs << 1900 + time->tm_year << "/" << 1 + time->tm_mon << "/" << time->tm_mday <<
        "/" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << " ";
    ofs << dirE(dir) << " " << score << endl;
    ofs.close();
}

