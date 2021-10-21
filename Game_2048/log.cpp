#include "log.h"

//���캯��
Log::Log(Map* map) : map(map) {
    map->addEventObserver(this);
    logName = "log.txt";
    pName = "";
    score = 0;
    dir = '0';
    time = NULL;
}

//��������
Log::~Log() {
    map->removeEventObserver(this);
}

//��ȡ���򡢷�����ִ�й���
void Log::messageDirScore(const char& dir, int& mergeScore) {
    this->dir = dir;
    this->score = mergeScore;
    if (score > 0)
        fileLog();
}

//��ȡ�������
void Log::messageName(const string& name) {
    this-> pName = name;
}

//��ȡ��ǰʱ��
void Log::messageTime(tm* nowTime) {
    this->time = nowTime;
}

//����ת��
string Log::dirE(const char& dir) {
    switch (dir) {
    case 'w': return "UP";
    case 'z':return "DOWN";
    case 'a':return "LEFT";
    case 's':return "RIGHT";
    default:return "";
    }
}

//�ļ�����
void Log::fileLog() {
    ofstream ofs;
    ofs.open(logName, ios::out | ios::app);
    ofs << pName << " ";
    ofs << 1900 + time->tm_year << "/" << 1 + time->tm_mon << "/" << time->tm_mday <<
        "/" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << " ";
    ofs << dirE(dir) << " " << score << endl;
    ofs.close();
}

