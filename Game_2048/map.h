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

//��������
struct Coor {
    int x;
    int y;
};

class Map {
public:
    //���캯��
    Map();

    //�ı����̴�С
    void changeSize(const int& num);

    //�����ƶ�����
    void moveArray(vector <int>& arr);

    //���кϲ�����
    void mergeArray(vector <int>& arr);

    //���в������
    void resultArray(vector <int>& arr);

    //�ƶ�����
    int moveTest(const char& chMove);

    //�ƶ�
    void moveResult(const char& chMove);

    //��ӡ����
    void printMap();

    //���̳�ʼ��
    void mapInit();

    //�жϿ��ƶ�����
    int canMoveSum();

    //�����䲢�����������
    Coor appendBlock();

    //�жϷ����Ƿ�����
    bool isFull();

    //��ȡ������־
    bool getFull();

    //�ж��Ƿ�ϳ�Ŀ�귽��
    bool isWin(const int& goal);

    //��ȡ���̴�С
    int getSize();

    //��ȡһ�ַ���
    int getScore();

    //���̸�ֵ
    int& setNum(const int& i, const int& j);

    //���ƶ������ȡ
    int getCanDir(const int& i);

    //��ȡ�ƶ��ж�ֵ
    int getCanMove();

    //��ӹ۲���
    void addEventObserver(PlayerEventObserver* observer);

    //�Ƴ��۲���
    void removeEventObserver(PlayerEventObserver* observer);

    //�����������
    string getPlayerName(const string& name);

    //���ص�ǰʱ��
    struct tm* getTime();

private:
    //���̾���
    vector <vector <int>> matrix;

    //���Ծ���
    vector <vector <int>> _matrix;

    //���̴�С
    int size;

    //�ϲ��÷�
    int merScore;

    //�жϿɷ��ƶ�
    int canMove;

    //���ƶ������ж�
    int canDir[4];

    //����������־
    bool fullMap;

    //���������
    Coor ran;

    //�۲���
    vector<PlayerEventObserver*> observers;

};




