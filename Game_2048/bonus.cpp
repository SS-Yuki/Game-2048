#include "bonus.h"

//���캯��
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

//��������
Bonus::~Bonus() {
    map->removeEventObserver(this);
}

//��ȡ���򡢷�����ִ�й���
void Bonus::messageDirScore(const char& dir, int& mergeScore) {
    if (getTimeLag() < 1) {
        mergeScore++;
        if (loged)
            fileLog();
    }
        
}

//��ȡ�������
void Bonus::messageName(const string& name) {
    this->pName = name;
}

//��ȡ��ǰʱ��
void Bonus::messageTime(tm* nowTime) {
    this->time = nowTime;
}

//��log����
void Bonus::changeLog() {
    loged = true;
}

//����ʱ����
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

//�ļ�����
void Bonus::fileLog() {
    ofstream ofs;
    ofs.open(logName, ios::out | ios::app);
    ofs << pName << " ";
    ofs << 1900 + time->tm_year << "/" << 1 + time->tm_mon << "/" << time->tm_mday <<
        "/" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << " ";
    ofs << timeLag << " " << "1" << endl;
    ofs.close();
}
