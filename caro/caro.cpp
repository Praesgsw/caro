#include "Menu.h"
#include "Board.h"
int main() {

	// full screen
	system("color FA");
	SetConsole(1120, 720);
	//playSound(6);
	LoadingGame();
	menu();
	system("pause");
	return 0;
}
