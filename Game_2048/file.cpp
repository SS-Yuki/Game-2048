#include "file.h"

//���캯��
File::File() {
    map = new Map;
	in = "";
	out = "";
    fileNum = 0;
    fileDir = '0';
}

//��������
File::~File() {
    if (map != NULL)
        delete map;
}

//����������
void File::setFileNameIn(const string& fIn) {
    in = fIn;
}

//���������
void File::setFileNameOut(const string& fOut) {
    out = fOut;
}

//�鿴���Ʋ�����Ŀ
int File::getFileNameNum() {
    return fileNum;
}

//�������Ʋ�����Ŀ
void File::addFileNameNum() {
    fileNum++;
}

//�ļ�����
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

//�ļ����
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
