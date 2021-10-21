#include "map.h"

//���캯��
Map::Map() {
    size = 4;
    matrix.resize(size);
    for (auto &vec : matrix)
        vec.resize(size, 0);
    _matrix.resize(size);
    for (auto& vec : _matrix)
        vec.resize(size, 0);
    merScore = 0;
    canMove = 0;
    for (int i = 0; i < 4; i++) {
        canDir[i] = 0;
    }
    fullMap = false;
    ran.x = 0;
    ran.y = 0;
}

//�ı����̴�С
void Map::changeSize(const int& num) {
    size = num;
    matrix.resize(size);
    for (auto& vec : matrix)
        vec.resize(size, 0);
    _matrix.resize(size);
    for (auto& vec : _matrix)
        vec.resize(size, 0);
}

//�����ƶ�����
void Map::moveArray(vector <int>& arr) {
    int tem = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == 0) {
            tem = arr[i + 1];
            arr[i] = tem;
            if (arr[i+1] != 0)
                canMove = 1;
            arr[i + 1] = 0;
        }
    }
}

//���кϲ�����
void Map::mergeArray(vector <int>& arr) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == arr[i + 1] && arr[i] != 0) {
            arr[i] *= 2;
            merScore += arr[i];
            arr[i + 1] = 0;
            canMove = 1;
        }
    }
}

//���в������
void Map::resultArray(vector <int>& arr) {
    for (int time = 0; time < size - 1; time++) {
        moveArray(arr);
    }
    mergeArray(arr);
    moveArray(arr);
}

//�ƶ�����
int Map::moveTest(const char& chMove) {
    merScore = 0;
    canMove = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            switch (chMove) {
            case LEFT:_matrix[i][j] = matrix[i][j]; break;
            case RIGHT:_matrix[i][j] = matrix[i][size-1-j]; break;
            case UP:_matrix[i][j] = matrix[j][i]; break;
            case DOWN:_matrix[i][j] = matrix[size-1-j][i]; break;
            default:break;
            }
        }
        resultArray(_matrix[i]);
    }
    return canMove;
}

//�ƶ�
void Map::moveResult(const char& chMove) {
    moveTest(chMove);
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            switch (chMove) {
            case LEFT:matrix[i][j] = _matrix[i][j]; break;
            case RIGHT:matrix[i][j] = _matrix[i][size - 1 - j]; break;
            case UP:matrix[i][j] = _matrix[j][i]; break;
            case DOWN:matrix[i][j] = _matrix[j][size - 1 - i]; break;
            default:break;
            }
        }
    for (auto observer : observers) {
        observer -> messageDirScore(chMove, merScore);
    }
}

//���̳�ʼ��
void Map::mapInit() {
    int x1, x2, y1, y2;
    srand((int)time(NULL));
    do {
        x1 = rand() % size;
        y1 = rand() % size;
        x2 = rand() % size;
        y2 = rand() % size;
    } while (x1 == x2 && y1 == y2);
    matrix[x1][y1] = 2;
    matrix[x2][y2] = 2;
}

//��ӡ����
void Map::printMap() {
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            cout << "+-----";
        cout << endl;
        for (k = 0; k < size + 1; k++)
            (k < size && matrix[i][k] != 0) ? cout << "|" << setw(5) << matrix[i][k] : cout << "|     ";
        cout << endl;
    }
    for (j = 0; j < size; j++)
        cout << "+-----";
    cout << endl;
}

//�жϿ��ƶ�����
int Map::canMoveSum() {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        canDir[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        if (moveTest(direct[i])) {
            canDir[i] = 1;
            sum++;
        }
    }
    return sum;
}

//������
Coor Map::appendBlock() {
    if (isFull() || !canMove)
        return ran;
    srand((int)time(NULL));
    do {
        ran.x = rand() % size;
        ran.y = rand() % size;
    } while (matrix[ran.x][ran.y] != 0);
    matrix[ran.x][ran.y] = 2;
    return ran;
}

//�жϷ����Ƿ�����
bool Map::isFull() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != 0)
                count++;
        }
    }
    if (count == size * size) {
        fullMap = true;
        return true;
    }
    return false;
}

//��ȡ������־
bool Map::getFull() {
    return fullMap;
}

//�ж��Ƿ�ϳ�Ŀ�귽��
bool Map::isWin(const int& goal) {
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == goal) {
                return true;
            }
        }
    return false;
}

//��ȡ���̴�С
int Map::getSize() {
    return size;
}

//��ȡһ�ַ���
int Map::getScore() {
    return merScore;
}

//���̸�ֵ
int& Map::setNum(const int& i, const int& j) {
    int& val = matrix[i][j];
    return val;
}

//���ƶ������ȡ
int Map::getCanDir(const int& i) {
    return canDir[i];
}

//��ȡ�ƶ��ж�ֵ
int Map::getCanMove() {
    return canMove;
}

//��ӹ۲���
void Map::addEventObserver(PlayerEventObserver* observer) {
    observers.push_back(observer);
}

//�Ƴ��۲���
void Map::removeEventObserver(PlayerEventObserver* observer) {
    observers.erase(
        find(observers.begin(), observers.end(), observer)
    );
}

//�����������
string Map::getPlayerName(const string& name) {
    for (auto observer : observers) {
        observer->messageName(name);
    }
    return name;
}

//���ص�ǰʱ��
struct tm* Map::getTime() {
    time_t second = time(NULL);
    struct tm* nowTime = localtime(&second);
    for (auto observer : observers) {
        observer->messageTime(nowTime);
    }
    return nowTime;
}

