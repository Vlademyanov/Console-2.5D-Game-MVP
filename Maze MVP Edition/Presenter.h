#ifndef _PRESENTER_H
#define _PRESENTER_H


#pragma once

#include "View.h"
#include "Player.h"
#include "Texture.h"


class Presenter
{
public:
	Presenter(Player &player, View &view);
	void startGame();
	void handleUserInput(const std::set<char>& keys, Player& player, Texture &world);

private:
	Player player;
	View view;
	float step = 0.1f;
};



#endif // _PRESENTER_H
