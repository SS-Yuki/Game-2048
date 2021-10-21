#include "bonus.h"

//构造函数
Bonus::Bonus(Map* map) : map(map) {
    map->addEventObserver(this);
    pName = "";
    logName = "log.txt";
    time = 0;
    last = 0;
    now = 0;
    timeLag = 1024;
    loged = false;
}

//析构函数
Bonus::~Bonus() {
    map->removeEventObserver(this);
}

//获取方向、分数；执行功能
void Bonus::messageDirScore(const char& dir, int& mergeScore) {
    if (getTimeLag() < 1) {
        mergeScore++;
        if (loged)
            fileLog();
    }
        
}

//获取玩家姓名
void Bonus::messageName(const string& name) {
    this->pName = name;
}

//获取当前时间
void Bonus::messageTime(tm* nowTime) {
    this->time = nowTime;
}

//打开log功能
void Bonus::changeLog() {
    loged = true;
}

//计算时间间隔
double Bonus::getTimeLag() {
    if (last == now && last == 0) {
        now = clock();
    }
    else {
        last = now;
        now = clock();
    }
    timeLag = ((double)now - last) / CLOCKS_PER_SEC;
    return timeLag;
}

//文件操作
void Bonus::fileLog() {
    ofstream ofs;
    ofs.open(logName, ios::out | ios::app);
    ofs << pName << " ";
    ofs << 1900 + time->tm_year << "/" << 1 + time->tm_mon << "/" << time->tm_mday <<
        "/" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << " ";
    ofs << timeLag << " " << "1" << endl;
    ofs.close();
}
