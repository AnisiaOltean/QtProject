#include "Lab10Qt.h"
#include <QtWidgets/QApplication>

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "UI.h"
#include "GUI.h"
#include "ListaActivitati.h"
#include "ListGUI.h"
#include "GUIModel.h"
#include <iostream>

using namespace std;

void TestAll() {
	TesteDomain();
	testeRepo();
	testeService();
	testeLista();
}

void runGUI(int argc, char* argv[]) {
	QApplication a(argc, argv);
	//ActivitateRepo repo;
	RepoFile repo{ "activities.txt" };
	ActivitateValidator val;
	ActivitateService srv{ repo, val };

	//GUI gui{ srv };
	//gui.show();

	//ListaGUI g{ srv };
	//g.show();

	GUIModel g{ srv };
	g.show();

	a.exec();
}

/*void startApp() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService srv{ repo, val };
	ConsoleUI ui{ srv };

	ui.run();
}
*/

int main(int argc, char *argv[])
{
	TestAll();
	runGUI(argc, argv);

	return 0;
}
