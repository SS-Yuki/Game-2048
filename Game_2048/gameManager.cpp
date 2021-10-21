#include "gameManager.h"

//���캯��
GameManager::GameManager(int argc, char* const argv[]) : normal(2048), test(64) {
    modeNum = 0;
    vic = normal;
    chImple = '0';
    map = new Map; 
    fp = new File;
    log = NULL;
    bonus = NULL;
    paraProcess(argc, argv);   
}

//��������
GameManager::~GameManager() {
    if (map != NULL)
        delete map;
    if (fp != NULL)
        delete fp;
    if (log != NULL)
        delete log;
    if (bonus != NULL)
        delete bonus;
}

//�����в�������
void GameManager::paraProcess(int argc, char* const argv[]) {
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-') {
            char order = argv[i][1];
            switch (order) {
            case 'i':  fp->setFileNameIn(argv[i + 1]); fp->addFileNameNum(); break;
            case 'o':  fp->setFileNameOut(argv[i + 1]); fp->addFileNameNum(); break;
            case 't':  vic = test; break;
            case 's':  paraMapSize(argc, argv, i); break;
            case 'l':  if (!strcmp("-log", argv[i])) {
                log = new Log(map);
            }
                break;
            case 'p': bonus = new Bonus(map); break;
            default: break;
            }
        }
    if (log != NULL && bonus != NULL)
        bonus->changeLog();
}

//�������������̴�С
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

//�����ļ�����ģʽ
void GameManager::fileTest() {
    if (fp->getFileNameNum() == 2) {
        fp->fileIn();
        fp->fileOut();
        exit(0);
    }  
}

//��Ϸ��ʼ��
void GameManager::gameInit() {
    cout << "Welcome to 2048!!!" << endl << endl;
    cout << "------GAME START------" << endl;
    cout << "Please select the mode: " << endl;
    cout << "1.Single-player mode" << endl;
    cout << "2.Two-player mode" << endl;
    modeChoosing();
    map->mapInit();
}

//��Ϸģʽѡ��
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

//��Ϸģʽ���Ż�ȡ
int GameManager::modeGet() {
    return modeNum;
}

//��Ϸ���У�����ģʽ
void GameManager::gameExecute() {
    int order = 0, num = 1;
    Player* plrs = new Player[1];

    map->printMap();

    bool sign = true;
    while (sign) {
        chImple = getchar();
        cin.ignore(1024, '\n');
        chExecute(sign, num, plrs, order);
    }
    cout << "------Game over!------" << endl;
    delete[] plrs;
}

//��Ϸ���У�˫��ģʽ
void GameManager::gameExecute(const int& num) {
    int order = 0;
    Player* plrs = new Player[num];

    gamePlayerName(num, plrs);

    map->printMap();
    cout << "The player of the first round is " << plrs[0].getName() << "." << endl;

    bool sign = true;
    while (sign) {
        cheatFunc(num, plrs, order);
        chExecute(sign, num, plrs, order);
    }
    resultJudge(num, plrs);
    cout << "------Game over!------" << endl;
    delete[] plrs;
}


//��Ϸ�������
void GameManager::gamePlayerName(const int& playerNum, Player* plrs) {
    for (int i = 0; i < playerNum; i++) {
        cout << "Please enter the name of player" << i + 1 << ": " << endl;
        string tem;
        cin >> tem;
        cin.ignore(1024, '\n');
        plrs[i].setName(tem);
    }
}

//��Ϸָ�����
void GameManager::chExecute(bool& sign, const int& playerNum, Player* plrs, int& order) {
    if (chImple != UP && chImple != LEFT && chImple != RIGHT && chImple != DOWN)
        return;
    else {
        map->getPlayerName(plrs[order].getName()); map->getTime();
        map->moveResult(chImple);
        if (map->getCanMove()) {
            addPlayerScore(plrs, playerNum, order);
            map->appendBlock();
            map->printMap();
            judgeGameOver(sign);
            if (sign && playerNum > 1) {
                order = ((order == playerNum - 1) ? 0 : (order + 1));
                cout << "The player of the next round is " << plrs[order].getName() << "." << endl;
            }
        }
        else
            cout << "Can't move! Please input again!" << endl;
    }
}

//��Ҽӷ�
void GameManager::addPlayerScore(Player* plrs, const int& playerNum, const int& order) {
    plrs[order].addScore(map->getScore());
    for (int i = 0; i < playerNum; i++) {
        cout << plrs[i].getName() << "'s current score is "
            << plrs[i].getTScore() << "." << endl;
    }
}

//�ж���Ϸ����
void GameManager::judgeGameOver(bool& sign) {
    if (map->getFull())
        sign = false;
    if (map->isWin(vic)) {
        cout << "Congratulations, you win!" << endl;
        sign = false;
    }
}

//��Ϸ���ߣ�cheat
void GameManager::cheatFunc(const int& playerNum, Player* plrs, int& order) {
    if (plrs[order].getCheatState() && map->canMoveSum() == 1) {
        char chTrue;
        for (int i = 0; i < 4; i++)
            if (map->getCanDir(i))
                chTrue = direct[i];
        ct.beCheated(chTrue, chImple, &plrs[order]);
    }
    else {
        string input;
        getline(cin, input);
        chImple = input[0];
        if (chImple == 'c' && input[1] == ' ')
            ct.useCheat(plrs, playerNum, order, input, chImple);
    }
}

//˫��ģʽ����ж�
void GameManager::resultJudge(const int& playerNum, Player* plrs) {
    int max = 0, count = 0;
    for (int i = 0; i < playerNum; i++) {
        if (plrs[i].getTScore() == plrs[max].getTScore()) {
            count++;
        }
    }
    if (count == playerNum) 
        cout << "The game ended in a tie." << endl;
    else {
        for (int i = 0; i < playerNum; i++) {
            if (plrs[i].getTScore() > plrs[max].getTScore()) {
                max = i;
            }
        }
        cout << "The winner is " << plrs[max].getName() << "." << endl;
    }
}










