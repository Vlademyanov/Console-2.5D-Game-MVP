#include "View.h"
#include "Presenter.h"
#include <iostream>

int main() {
	Player player;
	View view;
	Presenter presenter(player, view);
	presenter.startGame();
	return 0;
}