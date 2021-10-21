#include "file.h"

//构造函数
File::File() {
    map = new Map;
	in = "";
	out = "";
    fileNum = 0;
    fileDir = '0';
}

//析构函数
File::~File() {
    if (map != NULL)
        delete map;
}

//设置输入名
void File::setFileNameIn(const string& fIn) {
    in = fIn;
}

//设置输出名
void File::setFileNameOut(const string& fOut) {
    out = fOut;
}

//查看名称参数数目
int File::getFileNameNum() {
    return fileNum;
}

//增加名称参数数目
void File::addFileNameNum() {
    fileNum++;
}

//文件输入
void File::fileIn() {
    int num;
    ifstream ifs;
    ifs.open(in, ios::in);
    ifs >> num;
    map->changeSize(num);
    for (int i = 0; i < map->getSize(); i++)
        for (int j = 0; j < map->getSize(); j++) 
            ifs >> map->setNum(i, j);
    ifs.get();
    fileDir = ifs.get();
    ifs.close();
}

//文件输出
void File::fileOut() {
    ofstream ofs;
    ofs.open(out, ios::out);
    ofs << map->canMoveSum();
    for (int i = 0; i < 4; i++) {
        if (map->getCanDir(i))
            ofs << " " << direct[i];
    }
    ofs << endl;
    map->moveResult(fileDir);
    int score = map->getScore();
    for (int i = 0; i < map->getSize(); i++) 
        for (int j = 0; j < map->getSize(); j++) {
            ofs << map->setNum(i, j);
            if (j != map->getSize() - 1)
                ofs << " ";
            else
                ofs << endl;
        }
    Coor val = map->appendBlock();
    ofs << "2" << endl << val.x << " " << val.y << endl << score << endl;
    ofs.close();
}
