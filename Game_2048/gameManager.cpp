#include "gameManager.h"

//构造函数
GameManager::GameManager(int argc, char* const argv[]) : normal(2048), test(64) {
    modeNum = 0;
    vic = normal;
    chImple = '0';
    map = new Map; 
    fp = new File;
    logSwitch = false;
    bonusSwitch = false;
    paraProcess(argc, argv);   
}

//析构函数
GameManager::~GameManager() {
    if (map != NULL)
        delete map;
    if (fp != NULL)
        delete fp;
    if(logSwitch)
        for(auto l : logs)
            if (l != NULL)  delete l;
    if(bonusSwitch)
        for(auto b : bonuses)
            if (b != NULL) delete b;
    for (auto u : undos) {
        if (u != NULL)
            delete u;
    }
    for (auto a : aExes) {
        if (a != NULL)
            delete a;
    }
    for (auto pl : pls) {
        if (pl != NULL)
            delete pl;
    }
}

//命令行参数处理
void GameManager::paraProcess(int argc, char* const argv[]) {
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-') {
            char order = argv[i][1];
            switch (order) {
            case 'i':  fp->setFileNameIn(argv[i + 1]); fp->addFileNameNum(); break;
            case 'o':  fp->setFileNameOut(argv[i + 1]); fp->addFileNameNum(); break;
            case 't':  vic = test; break;
            case 's':  paraMapSize(argc, argv, i); break;
            case 'l':  
                if (!strcmp("-log", argv[i]))
                    logSwitch = true;
                    break;
            case 'p': bonusSwitch = true; break;
            default: break;
            }
        }
  
}

//命令行设置棋盘大小
void GameManager::paraMapSize(int argc, char* const argv[], const int& i) {
    int size;
    if (atoi(argv[i + 1]) < 6 && atoi(argv[i + 1]) > 1)
        size = atoi(argv[i + 1]);
    else {
        cout << "Please input the \"size\".(2 <= size <= 5) " << endl;
        while (true) {
            cin >> size;
            cin.ignore(1024, '\n');
            if (size < 6 && size > 1) 
                break;
            else 
                cout << "Please input again." << endl;
        }
    }
    map->changeSize(size);
}

//进入文件测试模式
void GameManager::fileTest() {
    if (fp->getFileNameNum() == 2) {
        fp->fileIn();
        fp->fileOut();
        exit(0);
    }  
}

//游戏初始化
void GameManager::gameInit() {
    cout << "Welcome to 2048!!!" << endl << endl;
    cout << "------GAME START------" << endl;
    cout << "Please select the mode: " << endl;
    cout << "1.Single-player mode" << endl;
    cout << "2.Two-player mode" << endl;
    modeChoosing();
    map->mapInit();
}

//游戏模式选择
void GameManager::modeChoosing() {
    while (true) {
        cout << "Please enter the serial number of the corresponding mode: ";
        cin >> modeNum;
        cin.ignore(1024, '\n');
        if (modeNum == 1) {
            cout << "Enter to single-player mode." << endl;
            break;
        }
        else if (modeNum == 2) {
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
    return modeNum;
}

//游戏运行：单人模式
void GameManager::gameExecute() {
    int order = 0, num = 1;
    createObject(num);
    map->printMap();

    bool sign = true;
    while (sign) {
        chImple = getchar();
        cin.ignore(1024, '\n');
        chExecute(sign, num, order);
    }
    cout << "------Game over!------" << endl;
 
}

//游戏运行：双人模式
void GameManager::gameExecute(const int& num) {
    int order = 0;
    createObject(num);
    gamePlayerName(num);

    map->printMap();
    cout << "The player of the first round is " << pls[0]->getName() << "." << endl;

    bool sign = true;
    while (sign) {
        cheatFunc(num, order);
        chExecute(sign, num, order);
    }
    resultJudge(num);
    cout << "------Game over!------" << endl;
}

//玩家关联对象创建
void GameManager::createObject(const int& num) {
    for (int i = 0; i < num; i++) {
        pls.push_back(new Player);
        aExes.push_back(new PlayerActionExecuter(pls[i]));
        undos.push_back(new UndoAction(aExes[i]));
        if (logSwitch)
            logs.push_back(new Log(aExes[i]));
        if (bonusSwitch)
            bonuses.push_back(new Bonus(aExes[i]));
    }
}

//游戏玩家命名
void GameManager::gamePlayerName(const int& playerNum) {
    for (int i = 0; i < playerNum; i++) {
        cout << "Please enter the name of player" << i + 1 << ": " << endl;
        string tem;
        cin >> tem;
        cin.ignore(1024, '\n');
        pls[i]->setName(tem);
    }
}

//游戏指令操作
void GameManager::chExecute(bool& sign, const int& playerNum, int& order) {
    if (chImple != UP && chImple != LEFT && chImple != RIGHT && chImple != DOWN)
        return;
    else {
        if (map->moveTest(chImple)) {
            aExes[order]->executeAction(new PerformMoveAction(pls[order], map, chImple));
            for (int i = 0; i < playerNum; i++) {
                cout << pls[i]->getName() << "'s current score is "
                    << pls[i]->getTScore() << "." << endl;
            }
            map->appendBlock();
            map->printMap();
            bool constOrder = regretResult(playerNum, order);
            judgeGameOver(sign);
            if (sign && playerNum > 1) {
                if(!constOrder)
                    order = ((order == playerNum - 1) ? 0 : (order + 1));
                cout << "The player of the next round is " << pls[order]->getName() << "." << endl;
            }
        }
        else
            cout << "Can't move! Please input again!" << endl;
    }
}

//反悔操作实现
bool GameManager::regretResult(const int& num, int& order) {
    bool constOrder = false;
    if (undos[order]->getUndoNum() > 0) {
        cout << "You still have " << undos[order]->getUndoNum() <<
            " chances to regret the game, do you want to regret it?  y/n" << endl;
        char ch;
        bool flag = true;
        while (flag) {
            cin >> ch;
            cin.ignore(1024, '\n');
            switch (ch) {
            case 'y':
                aExes[order]->executeAction(undos[order]);
                map->printMap();
                cout << "Please continue to input." << endl;
                if (num == 1)
                    regretResult(num, order);
                constOrder = true;
                flag = false;
                break;
            case 'n':
                flag = false;
                cout << "Please enter the direction of movement." << endl;
                break;
            default:
                cout << "Error! Please input again!" << endl;
                break;
            }

        }
    }
    return constOrder;
}

//判断游戏结束
void GameManager::judgeGameOver(bool& sign) {
    if (map->getFull())
        sign = false;
    if (map->isWin(vic)) {
        cout << "Congratulations, you win!" << endl;
        sign = false;
    }
}

//游戏道具：cheat
void GameManager::cheatFunc(const int& playerNum, int& order) {
    if (pls[order]->getCheatState() && map->canMoveSum() == 1) {
        char chTrue;
        for (int i = 0; i < 4; i++)
            if (map->getCanDir(i))
                chTrue = direct[i];
        ct.beCheated(chTrue, chImple, pls[order]);
    }
    else {
        string input;
        getline(cin, input);
        chImple = input[0];
        if (chImple == 'c' && input[1] == ' ')
            ct.useCheat(pls, playerNum, order, input, chImple);
    }
}

//双人模式结果判断
void GameManager::resultJudge(const int& playerNum) {
    int max = 0, count = 0;
    for (int i = 0; i < playerNum; i++) {
        if (pls[i]->getTScore() == pls[max]->getTScore()) {
            count++;
        }
    }
    if (count == playerNum) 
        cout << "The game ended in a tie." << endl;
    else {
        for (int i = 0; i < playerNum; i++) {
            if (pls[i]->getTScore() > pls[max]->getTScore()) {
                max = i;
            }
        }
        cout << "The winner is " << pls[max]->getName() << "." << endl;
    }
}










