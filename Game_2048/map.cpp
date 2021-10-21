#include "map.h"
 
//构造函数
Map::Map() {
    size = 4;
    matrix.resize(size);
    for (auto& vec : matrix)
        vec.resize(size, 0);
    matrixTest.resize(size);
    for (auto& vec : matrixTest)
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

//改变棋盘大小
void Map::changeSize(const int& num) {
    size = num;
    matrix.resize(size);
    for (auto& vec : matrix)
        vec.resize(size, 0);
    matrixTest.resize(size);
    for (auto& vec : matrixTest)
        vec.resize(size, 0);
}

//单行移动操作
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

//单行合并操作
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

//单行操作结果
void Map::resultArray(vector <int>& arr) {
    for (int time = 0; time < size - 1; time++) {
        moveArray(arr);
    }
    mergeArray(arr);
    moveArray(arr);
}

//移动测验
int Map::moveTest(const char& chMove) {
    merScore = 0;
    canMove = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            switch (chMove) {
            case LEFT:matrixTest[i][j] = matrix[i][j]; break;
            case RIGHT:matrixTest[i][j] = matrix[i][size-1-j]; break;
            case UP:matrixTest[i][j] = matrix[j][i]; break;
            case DOWN:matrixTest[i][j] = matrix[size-1-j][i]; break;
            default:break;
            }
        }
        resultArray(matrixTest[i]);
    }
    return canMove;
}

//移动
void Map::moveResult(const char& chMove) {
    moveTest(chMove);
    matrixCopy = matrix;
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            switch (chMove) {
            case LEFT:matrix[i][j] = matrixTest[i][j]; break;
            case RIGHT:matrix[i][j] = matrixTest[i][size - 1 - j]; break;
            case UP:matrix[i][j] = matrixTest[j][i]; break;
            case DOWN:matrix[i][j] = matrixTest[j][size - 1 - i]; break;
            default:break;
            }
        }
    /*for (auto observer : observers) {
        observer -> messageDirScore(chMove, merScore);
    }*/
}

//移动撤销
void Map::moveUndo() {
    matrix = matrixCopy;
}

//数盘初始化
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

//打印数盘
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

//判断可移动方向
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

//随机填充
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

//判断方块是否已满
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

//获取填满标志
bool Map::getFull() {
    return fullMap;
}

//判断是否合成目标方块
bool Map::isWin(const int& goal) {
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == goal) {
                return true;
            }
        }
    return false;
}

//获取数盘大小
int Map::getSize() {
    return size;
}

//获取一轮分数
int Map::getScore() {
    return merScore;
}

//数盘赋值
int& Map::setNum(const int& i, const int& j) {
    int& val = matrix[i][j];
    return val;
}

//可移动方向获取
int Map::getCanDir(const int& i) {
    return canDir[i];
}

//获取移动判断值
int Map::getCanMove() {
    return canMove;
}

////添加观察者
//void Map::addEventObserver(PlayerEventObserver* observer) {
//    observers.push_back(observer);
//}
//
////移除观察者
//void Map::removeEventObserver(PlayerEventObserver* observer) {
//    observers.erase(
//        find(observers.begin(), observers.end(), observer)
//    );
//}
//
////返回玩家姓名
//string Map::getPlayerName(const string& name) {
//    for (auto observer : observers) {
//        observer->messageName(name);
//    }
//    return name;
//}

////返回当前时间
//struct tm* Map::getTime() {
//    time_t second = time(NULL);
//    struct tm* nowTime = localtime(&second);
//    for (auto observer : observers) {
//        observer->messageTime(nowTime);
//    }
//    return nowTime;
//}

