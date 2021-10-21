#include "cheat.h"

//构造函数
Cheat::Cheat() {
	cheatNum = 1;
	cheatCommand = "";
}

//使用cheat道具
void Cheat::useCheat(Player* plrs, const int& num, const int& order, const string& input, char& ch) {
    if (cheatNum > 0) {
        cout << "using \"cheat \" !" << endl;
        cheatCommand = input.substr(2, input.length() - 2);
        int next = ((order == num - 1) ? 0 : order + 1);
        plrs[next].setCheatState(true);
        cheatNum--;
        cout << "Please input the order." << endl;
        ch = getchar();
        cin.ignore(1024, '\n');
    }
    else {
        cout << "The \"cheat\" have been used up." << endl;
    }
}



//受到cheat攻击
void Cheat::beCheated(const char& chTrue, char& ch, Player* plr) {
    while (true) {
        cout << cheatCommand << endl << "If you agree, please input " << chTrue << endl;
        ch = getchar();
        cin.ignore(1024, '\n');
        if (ch == chTrue) {
            plr->setCheatState(false); 
            break;
        }
    }
}

