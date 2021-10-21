#include "log.h"

Log::Log(PlayerActionExecuter* aExe) :aExe(aExe) {
	aExe->addActionObserver(this);
	logName = "log.txt";
}

Log::~Log() {
	aExe->removeObserver(this);
}
void Log::actionPerformed(PlayerAction* action) {
	fstream ofs;
	ofs.open(logName, ios::out | ios::app);
	ofs << action->getName() << " ";
	tm* t = action->getTime();
	ofs << 1900 + t->tm_year << "/" << 1 + t->tm_mon << "/" << t->tm_mday <<
		"/" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << " ";
	switch (action->getType()) {
	case 0:
		ofs << -(action->getScore()) << endl;break;
	case 1:
		ofs << dirE(dynamic_cast <PerformMoveAction*> (action)->getDir()) << " " << action->getScore() << endl;
		break;
	case 2:
		ofs << dynamic_cast <ObtainBounsAction*> (action)->getTimeDur() << " " << action ->getScore() << endl;
		break;
	default: break;
	}
	ofs.close();
}

string Log::dirE(const char& dir) {
	switch (dir) {
	case 'w': return "UP";
	case 'z':return "DOWN";
	case 'a':return "LEFT";
	case 's':return "RIGHT";
	default:return "";
	}
}

