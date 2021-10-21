#pragma once
#include "playerEventObserver.h"
#include "map.h"

class Log : public PlayerEventObserver {
public:
    //���캯��
    Log(Map* map);

    //��������
    virtual ~Log();

    //��ȡ���򡢷�����ִ�й���
    virtual void messageDirScore(const char& dir, int& mergeScore);

    //��ȡ�������
    virtual void messageName(const string& name);

    //��ȡ��ǰʱ��
    virtual void messageTime(tm* nowTime);  

private:
    //����ָ��
    Map* map;

    //�ļ���
    string logName;

    //�������
    string pName;

    //��ҷ���
    int score;

    //�ƶ�����
    char dir;

    //ʱ��ṹ
    tm* time;

    //����ת��
    string dirE(const char& dir);

    //�ļ�����
    void fileLog();
};
