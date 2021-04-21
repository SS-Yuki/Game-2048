#include "gameManager.h"
#include "player.h"


//构造函数
GameManager::GameManager() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            map[i][j] = 0;
        }
    }
    m_diffy[0] = 64;
    m_diffy[1] = 2048;
    m_dSign = 1;
    m_modeNum = 0;
    m_score = 0;
    m_isChange = false;
    endSign = false;
    cout << "Welcome to 2048!!!" << endl << endl;
}

//游戏难度设置
void GameManager::difficultySettings() {
    cout << "Please set the difficulty first." << endl;
    cout << "(Input '-t' to switch difficulty. Enter enter to start.)" << endl;
    char ch1, ch2;
    while (1) {
        ch1 = _getch();
        if (ch1 == 13) {
            system("cls");
            cout << "------GAME START------" << endl;
            break;
        }
        else if (ch1 == '-' && (ch2 = _getch()) == 't') {
            m_dSign = 1 - m_dSign;
            cout << "transform into " << m_diffy[m_dSign] << endl;
        }
    }
}

//游戏模式选择
void GameManager::modeChoosing() {
    cout << "Please select the mode: " << endl;
    cout << "1.Single-player mode" << endl;
    cout << "2.Two-player mode" << endl;
    while(true){
        cout << "Please enter the serial number of the corresponding mode: ";
        cin >> m_modeNum;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (m_modeNum == 1) {
            cout << "Enter to single-player mode." << endl;
            system("pause");
            break;
        }
        else if (m_modeNum == 2) {
            cout << "Enter to two-player mode." << endl;
            break;
        }
        else {
            cout << "Error!" << endl;
        }
    }  
}

//游戏模式代号获取
int GameManager::modeGet() {
    return m_modeNum;
}

//游戏运行：单人模式
void GameManager::gameExecute() {
    Player plr;
    gameInit();
    while (!endSign) {
        char ch = _getch();
        if (impleMap(ch) && !endSign) {
            fillMap();
            printMap();
            plr.m_totalScore += m_score;
            cout << "The current score is " << plr.m_totalScore << endl;
            if (isWin()) {
                cout << "Congratulations, you win!" << endl;
                break;
            }
        } 
        
    }
    cout << "------Game over!------" << endl;
}

//游戏运行：双人模式
void GameManager::gameExecute(int num) {
    Player *plrs = new Player[num];
    for (int i = 0; i < num; i++) {
        cout << "Please enter the name of player" << i + 1 << ": " << endl;
        plrs[i].nameSet();
    }
    gameInit();
    cout << "The player of the first round is " << plrs[0].m_name << "." << endl;
    int order = 0;
    while (!endSign) {
        char ch = _getch();
        if (impleMap(ch) && !endSign) {
            fillMap();
            printMap();

            plrs[order].m_totalScore += m_score;
            for (int i = 0; i < num; i++) {
                cout << plrs[i].m_name << "'s current score is "
                    << plrs[i].m_totalScore << "." << endl;
            }
            if (isWin()) {
                cout << "Congratulations, you win!" << endl;
                break;
            }
            if (order == num - 1) {
                order = 0;
            }
            else order += 1;
            cout << "The player of the next round is " << plrs[order].m_name << "." << endl;
        }
    }
    resultJudge(plrs, num);
    cout << "------Game over!------" << endl;
    delete[] plrs;
}

//打印数盘
void GameManager::printMap() {
    system("cls");
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            cout << "+-----";
        cout << endl;
        for (k = 0; k < 5; k++)
            (map[i][k] != 0 && k < 4) ? cout << "|" << setw(5) << map[i][k] : cout << "|     ";
        cout << endl;
    }
    for (j = 0; j < 4; j++)
        cout << "+-----";
    cout << endl;   
}

//游戏初始化
void GameManager::gameInit(){
    int x1, x2, y1, y2;
    srand((int)time(NULL));
    do{
        x1 = rand() % 4;
        y1 = rand() % 4;
        x2 = rand() % 4;
        y2 = rand() % 4;
    } while (x1 == x2 && y1 == y2);
    map[x1][y1] = 2;
    map[x2][y2] = 2;
    printMap();
}

//实现方块移动
int GameManager::impleMap(char ch) {
    if (ch != UP && ch != DOWN && ch != LEFT && ch != RIGHT) {
        return 0;
    }
    else{
        int rowL, times, colL, x, y, next, tem;
        int test[4][4];
        m_isChange = false;
        m_score = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                test[i][j] = map[i][j];
            }
        }

        for (rowL = 0; rowL < 4; rowL++) {

            for (times = 0; times < 3; times++) {
                for (colL = 0; colL < 3; colL++) {
                    directionJudge(rowL, colL, x, y, next, ch);
                    if (map[x][y] == 0) {
                        if (ch == LEFT || ch == RIGHT) {
                            tem = map[x][y + next];
                            map[x][y + next] = 0;
                        }
                        else {
                            tem = map[x + next][y];
                            map[x + next][y] = 0;
                        }
                        map[x][y] = tem;
                    }
                }
            }

            for (colL = 0; colL < 3; colL++) {
                directionJudge(rowL, colL, x, y, next, ch);
                if (ch == LEFT || ch == RIGHT) {
                    if (map[x][y] == map[x][y + next]) {
                        map[x][y] *= 2;
                        m_score += map[x][y];
                        map[x][y + next] = 0;
                    }
                }
                else {
                    if (map[x][y] == map[x + next][y]) {
                        map[x][y] *= 2;
                        m_score += map[x][y];
                        map[x + next][y] = 0;
                    }
                }
            }

            for (colL = 0; colL < 3; colL++) {
                directionJudge(rowL, colL, x, y, next, ch);
                if (map[x][y] == 0) {
                    if (ch == LEFT || ch == RIGHT) {
                        tem = map[x][y + next];
                        map[x][y + next] = 0;
                    }
                    else {
                        tem = map[x + next][y];
                        map[x + next][y] = 0;
                    }
                    map[x][y] = tem;
                }
            }

        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (test[i][j] != map[i][j]) {
                    m_isChange = true;
                }
            }
        }

        if (isFull()) {
            endSign = true;
        }
    }
    return 1;
}

//四种方向的实现
void GameManager::directionJudge(int rowL, int colL, int& x, int& y, int& next, char ch) {
    switch (ch){   
    case LEFT:
        x = rowL;
        y = colL;
        next = 1;
        break;
    case RIGHT:
        x = rowL;
        y = 3 - colL;
        next = -1;
        break;
    case UP:
        x = colL;
        y = rowL;
        next = 1;
        break;
    case DOWN:
        x = 3 - colL;
        y = rowL;
        next = -1;
        break;
    }
}

//随机填充
void GameManager::fillMap()
{
    int x, y;
    if (m_isChange == false || isFull() == true)
        return;
    srand((int)time(NULL));
    do
    {
        x = rand() % 4;
        y = rand() % 4;
    } while (map[x][y] != 0);
    map[x][y] = 2;
}

//判断方块是否已满
bool GameManager::isFull() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j] != 0)
                count++;
        }
    }
    if (count == 16) {
        return true;
    }
    else {
        return false;
    }
}

//判断是否合成目标方块
bool GameManager::isWin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j] == m_diffy[m_dSign]) {
                return true;
            }
        }
    }
    return false;
}

//双人模式结果判断
void GameManager::resultJudge(Player *players, int num) {
    int max = 0, count = 0;
    for (int i = 0; i < num; i++) {
        if (players[i].m_totalScore == players[max].m_totalScore) {
            count++;
        }
    }
    if (count == num) {
        cout << "The game ended in a tie." << endl;
    }
    else {
        for (int i = 0; i < num; i++) {
            if (players[i].m_totalScore > players[max].m_totalScore) {
                max = i;
            }
        }
        cout << "The winner is " << players[max].m_name << "." << endl;
    }
}








