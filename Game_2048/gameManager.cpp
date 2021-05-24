#include "gameManager.h"
#include "player.h"

//构造函数
GameManager::GameManager(int argc, char *const argv[]) {
    m_diffy[0] = 64;
    m_diffy[1] = 2048;     
    m_dSign = 1;
    size = 4;
    filenum = 0;
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-') {
            char order = argv[i][1];
            switch (order) {
                case 'i' :  in = argv[i + 1]; filenum++; break;
                case 'o' :  out = argv[i + 1]; filenum++; break;
                case 't' :  m_dSign = 0; break;
                case 's' :  if (atoi(argv[i + 1]) < 6 && atoi(argv[i + 1]) > 1)
                                size = atoi(argv[i + 1]);     
                            else {
                                cout << "Please input the \"size\".(2 <= size <= 5) " << endl;
                                while (true) {
                                    cin >> size;
                                    fflush(stdin);
                                    if (size < 6 && size > 1) 
                                        break;
                                    else {
                                        cout << "Please input again." << endl;
                                    }
                                }
                            }
                default : break;          
            }
        }
    map.resize(size);
    for (int i = 0; i < map.size(); i++)
        map[i].resize(size, 0);
    m_modeNum = 0;
    m_score = 0;
    m_isChange = false;
    endSign = false;
    cheatnum = 1;
    command = "";
}

//游戏模式选择
void GameManager::modeChoosing() {
    cout << "Welcome to 2048!!!" << endl << endl;
    cout << "------GAME START------" << endl;
    cout << "Please select the mode: " << endl;
    cout << "1.Single-player mode" << endl;
    cout << "2.Two-player mode" << endl;
    while(true){
        cout << "Please enter the serial number of the corresponding mode: ";
        cin >> m_modeNum;
        fflush(stdin);
        if (m_modeNum == 1) {
            cout << "Enter to single-player mode." << endl;
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
        char ch = getchar();
        fflush(stdin);
        if (impleMap(ch, 1) && !endSign) {
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
        cin >> plrs[i].m_name;
        fflush(stdin);
    }
    gameInit();
    cout << "The player of the first round is " << plrs[0].m_name << "." << endl;
    int order = 0;

    while (!endSign) {
        char ch = 0;
        //受到cheat攻击
        if (plrs[order].m_cheat == true && directionOnly() != 0) {
            while(true) {
                cout << command << endl << "If you agree, please input " << directionOnly() << endl;
                ch = getchar();
                fflush(stdin);
                if (ch == directionOnly()) {
                    plrs[order].m_cheat = false;
                    break;
                }   
            }     
        }
        //未受cheat攻击
        else {
            string input;
            getline(cin, input);
            ch = input[0];
            if (ch == 'c' && input[1] == ' ') {
                if (cheatnum > 0) {
                    cout << "using \"cheat \" !" << endl;
                    command = input.substr(2, input.length() - 2);
                    int next = ((order == num - 1) ? 0 : order + 1);
                    plrs[next].m_cheat = true;
                    cheatnum--;
                    cout << "Please input the order." << endl;
                    ch = getchar();
                    fflush(stdin);
                }
                else {
                    cout << "The \"cheat\" have been used up." << endl;
                }
            }
        }
        if (impleMap(ch, 1) && !endSign) {
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
            order = ((order == num - 1) ? 0 : (order + 1));
            cout << "The player of the next round is " << plrs[order].m_name << "." << endl;
        }
    }
    resultJudge(plrs, num);
    cout << "------Game over!------" << endl;
    delete[] plrs;
}

//打印数盘
void GameManager::printMap() {
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            cout << "+-----";
        cout << endl;
        for (k = 0; k < size + 1; k++)
            (map[i][k] != 0 && k < size) ? cout << "|" << setw(5) << map[i][k] : cout << "|     ";
        cout << endl;
    }
    for (j = 0; j < size; j++)
        cout << "+-----";
    cout << endl;   
}

//游戏初始化
void GameManager::gameInit() {
    int x1, x2, y1, y2;
    srand((int)time(NULL));
    do{
        x1 = rand() % size;
        y1 = rand() % size;
        x2 = rand() % size;
        y2 = rand() % size;
    } while (x1 == x2 && y1 == y2);
    map[x1][y1] = 2;
    map[x2][y2] = 2;
    printMap();
}

//实现方块移动
/*当sign = 0时，函数作为可否移动的判断函数；
  当sign = 1时，函数还发挥实际操作的功能。*/
int GameManager::impleMap(char ch, int sign) {
    int ret = 0;
    if (ch != UP && ch != DOWN && ch != LEFT && ch != RIGHT) {
            cout << "Please input again!" << endl;
        }
    else{
        int rowL, times, colL, x, y, next, tem;
        m_isChange = false;
        m_score = 0;

        vector<vector <int>> mapt = map;

        for (rowL = 0; rowL < size; rowL++) {

            for (times = 0; times < size - 1; times++) {
                for (colL = 0; colL < size - 1; colL++) {
                    directionJudge(rowL, colL, x, y, next, ch);
                    if (mapt[x][y] == 0) {
                        if (ch == LEFT || ch == RIGHT) {
                            tem = mapt[x][y + next];
                            mapt[x][y + next] = 0;
                        }
                        else {
                            tem = mapt[x + next][y];
                            mapt[x + next][y] = 0;
                        }
                        mapt[x][y] = tem;
                    }
                }
            }

            for (colL = 0; colL < size - 1; colL++) {
                directionJudge(rowL, colL, x, y, next, ch);
                if (ch == LEFT || ch == RIGHT) {
                    if (mapt[x][y] == mapt[x][y + next]) {
                        mapt[x][y] *= 2;
                        m_score += mapt[x][y];
                        mapt[x][y + next] = 0;
                    }
                }
                else {
                    if (mapt[x][y] == mapt[x + next][y]) {
                        mapt[x][y] *= 2;
                        m_score += mapt[x][y];
                        mapt[x + next][y] = 0;
                    }
                }
            }

            for (colL = 0; colL < size - 1; colL++) {
                directionJudge(rowL, colL, x, y, next, ch);
                if (mapt[x][y] == 0) {
                    if (ch == LEFT || ch == RIGHT) {
                        tem = mapt[x][y + next];
                        mapt[x][y + next] = 0;
                    }
                    else {
                        tem = mapt[x + next][y];
                        mapt[x + next][y] = 0;
                    }
                    mapt[x][y] = tem;
                }
            }

        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (map[i][j] != mapt[i][j]) {
                    ret = 1;
                    m_isChange = true;
                }
            }
        }

        if (sign == 1) {
            map = mapt;
            if (isFull())
                endSign = true;
        }  
    }
    return ret;
}

//判断只有唯一方向可走
char GameManager::directionOnly() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += impleMap(direct[i]);
    }
    if (count == 1) {
        for (int i = 0; i < 4; i++) 
            if (impleMap(direct[i]) == 1) 
                return direct[i];    
    }
    return 0;
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
        y = size - 1 - colL;
        next = -1;
        break;
    case UP:
        x = colL;
        y = rowL;
        next = 1;
        break;
    case DOWN:
        x = size - 1 - colL;
        y = rowL;
        next = -1;
        break;
    }
}

//随机填充
void GameManager::fillMap() {
    int x, y;
    if (m_isChange == false || isFull() == true)
        return;
    srand((int)time(NULL));
    do
    {
        x = rand() % size;
        y = rand() % size;
    } while (map[x][y] != 0);
    map[x][y] = 2;
}

//判断方块是否已满
bool GameManager::isFull() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (map[i][j] != 0)
                count++;
        }
    }
    if (count == size * size) {
        return true;
    }
    else {
        return false;
    }
}

//判断是否合成目标方块
bool GameManager::isWin() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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

//文件输入
void GameManager::fileIn() {
    ifstream ifs;
    ifs.open(in, ios::in);
    ifs >> size;
    map.resize(size);
    for (int i = 0; i < map.size(); i++)
        map[i].resize(size);
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            ifs >> map[i][j];
        }
    ifs.get();
    filedir = ifs.get();
    ifs.close();
}

//文件输出
void GameManager::fileOut() {
    int test[4] = {0};
    int count = 0, x, y;
    for (int i = 0; i < 4; i++) {
        if (impleMap(direct[i])) {
            count++;
            test[i] = 1;
        }
    }
    impleMap(filedir, 1);
    srand((int)time(NULL));
    do {
        x = rand() % size;
        y = rand() % size;
    } while (map[x][y] != 0);
    ofstream ofs;
    ofs.open(out, ios::out);
    ofs << count;
    for (int i = 0; i < 4; i++) {
        if (test[i]) 
            ofs << " " << direct[i];
    }
    ofs << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ofs << map[i][j];
            if (j != size - 1) 
                ofs << " ";
            else
                ofs << endl;
        }
    }
    ofs << "2" << endl;
    ofs << x << " " << y << endl;
    ofs << m_score << endl;
    ofs.close();
}

//文件输入输出模式
bool GameManager::fileMode() {
    if (filenum == 2) {
        return true;
    }
    else 
        return false;
}









