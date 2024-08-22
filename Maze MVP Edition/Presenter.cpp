#include "Presenter.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>
#include <algorithm>

#include <string>
#include <windows.h>
#include <vector>
#include <chrono>	
#define _USE_MATH_DEFINES
#include <math.h>

Presenter::Presenter(Player& player, View& view) {
	this->player = player;
	this->view = view;
}

void Presenter::handleUserInput(const std::set<char>& keys, Player& player, Texture &world) {
	for (char key : keys) {
		switch (key) {
		case 87:
			player.setPositionX(player.getPosition().x + sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			player.setPositionY(player.getPosition().y + cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '1') {
				player.setPositionX(player.getPosition().x - sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
				player.setPositionY(player.getPosition().y - cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			}
			break;
		case 65:
			player.setPositionX(player.getPosition().x - cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			player.setPositionY(player.getPosition().y + sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '1') {
				player.setPositionX(player.getPosition().x + cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
				player.setPositionY(player.getPosition().y - sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			}
			break;
		case 83:
			player.setPositionX(player.getPosition().x - sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			player.setPositionY(player.getPosition().y - cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '1') {
				player.setPositionX(player.getPosition().x + sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
				player.setPositionY(player.getPosition().y + cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			}
			break;

		case 68:
			player.setPositionX(player.getPosition().x + cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			player.setPositionY(player.getPosition().y - sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '1') {
				player.setPositionX(player.getPosition().x - cosf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
				player.setPositionY(player.getPosition().y + sinf(player.getDirectionView()) * view.getFPS() * player.getSpeed());
			}
			break;

		case 37:
			if (player.getDirectionView() < 0) player.setDirectionView(2 * M_PI);
			player.setDirectionView(player.getDirectionView() - 0.45f * player.getCameraSpeed() * view.getFPS());
			break;
		case 39:
			if (player.getDirectionView() > 2 * M_PI) player.setDirectionView(0);
			player.setDirectionView(player.getDirectionView() + 0.45f * player.getCameraSpeed() * view.getFPS());
			break;

		case 82:
			player.setPositionX(29.0f);
			player.setPositionY(2.0f);
			player.setDirectionView(0.0f);
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
		}
	}
}
void Presenter::startGame() {

	// ��������� ��������� ������
	view.setWidth(960);
	view.setHeight(227);

	// ������������� ���������������� ���������
	player.setFOV(M_PI / 2);			// ���� ������
	player.setDepthDisplay(24.0f);		// ������� ����������
	player.setCameraSpeed(5.5f);		// �������� �������� ������ (����������������)
	player.setJump(view.getWidth() / 32);
	player.setJumpFringle(view.getHeight() / 32);


	// �������������� �����
	view.initScreen();

	Texture texture;
	Texture world = texture.getTexture("WORLD");
	Texture win = texture.getTexture("WIN");

	// ��������� ��������� �����
	auto firstTime = std::chrono::system_clock::now();
	auto secondTime = std::chrono::system_clock::now();

	/*
		������� ����
	*/
	while (1) {
		// �������� ���������� ������ �������
		firstTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = firstTime - secondTime;
		secondTime = firstTime;
		// �������� FPS ��� Model
		view.setFPS(deltaTime.count());

		// ���������������� ����
		handleUserInput(view.getUserInput(), player, world);

		///*
		//	���������� ��� �����������
		//*/
		for (int x = 0; x < view.getWidth(); x++)
		{
			float angleBite = (player.getDirectionView() - player.getFOV() / 2.0f) + ((float)x / (float)view.getWidth()) * player.getFOV();
			float stepSize = 0.01f;		  								
			float distanceWall = 0.0f;		// ��������� �� �����
			float distanceSlab = 0.0f;		// ��������� �� ���������
			bool isWall = false;			// ��������� � �����
			bool isSlab = false;			// ��������� � ��������
			bool isFringe = false;			// ��������� � �����
			bool isFringeSlab = false;		// ��������� � ����� ���������

			float unitX = sinf(angleBite);	// ����. ���������� ������ �� X ��� �������� ����� ���� ��� �����
			float unitY = cosf(angleBite);	// ����. ���������� ������ �� Y ��� �������� ����� ���� ��� �����

			while (!isWall && distanceWall < player.getDepthDisplay())
			{
				distanceWall += stepSize;
				Point worldPoint;

				worldPoint.x = (int)(player.getPosition().x + distanceWall / cosf(player.getDirectionView() - angleBite) * unitX);
				worldPoint.y = (int)(player.getPosition().y + distanceWall / cosf(player.getDirectionView() - angleBite) * unitY);

				if (worldPoint.x < 0 || worldPoint.x >= world.textureSize.x || worldPoint.y < 0 || worldPoint.y >= world.textureSize.y)
				{
					isWall = true;		
					distanceWall = player.getDepthDisplay();
				}
				else
				{
					if (world.texture[(int)(worldPoint.x * world.textureSize.x + worldPoint.y)] == '1')
					{
						isWall = true;
						std::vector<std::pair<float, float>> vec;
						for (int CoordCornerX = 0; CoordCornerX < 2; CoordCornerX++)
							for (int CoordCornerY = 0; CoordCornerY < 2; CoordCornerY++) {
								float CornerY = worldPoint.y + CoordCornerY - player.getPosition().y;
								float CornerX = worldPoint.x + CoordCornerX - player.getPosition().x;
								float Dist = sqrt(CornerX * CornerX + CornerY * CornerY);
								float DOT = (unitX * CornerX / Dist) + (unitY * CornerY / Dist);
								vec.push_back(std::make_pair(Dist, DOT));
							}
						sort(vec.begin(), vec.end(), [](const std::pair<float, float>& left, const std::pair<float, float>& right) {return left.first < right.first; });
						float fringeAngle = 0.005;
						if (acos(vec.at(0).second) < fringeAngle) isFringe = true;
						if (acos(vec.at(1).second) < fringeAngle) isFringe = true;
					}
				}
			}
			while (!isSlab && distanceSlab < player.getDepthDisplay())
			{
				distanceSlab += stepSize;
				Point worldPoint;

				worldPoint.x = (int)(player.getPosition().x + distanceSlab / cosf(player.getDirectionView() - angleBite) * unitX);
				worldPoint.y = (int)(player.getPosition().y + distanceSlab / cosf(player.getDirectionView() - angleBite) * unitY);
				if (worldPoint.x < 0 || worldPoint.x >= world.textureSize.x || worldPoint.y < 0 || worldPoint.y >= world.textureSize.y)
				{
					isSlab = true;	
					distanceSlab = player.getDepthDisplay();
				}
				else
				{
					if (world.texture[(int)(worldPoint.x * world.textureSize.x + worldPoint.y)] == '2' || world.texture[worldPoint.x * world.textureSize.x + worldPoint.y] == '1')
					{
						isSlab = true;
						std::vector<std::pair<float, float>> vec;
						for (int CoordCornerX = 0; CoordCornerX < 2; CoordCornerX++)
							for (int CoordCornerY = 0; CoordCornerY < 2; CoordCornerY++) {
								float CornerY = worldPoint.y + CoordCornerY - player.getPosition().y;
								float CornerX = worldPoint.x + CoordCornerX - player.getPosition().x;
								float Dist = sqrt(CornerX * CornerX + CornerY * CornerY);
								float DOT = (unitX * CornerX / Dist) + (unitY * CornerY / Dist);
								vec.push_back(std::make_pair(Dist, DOT));
							}
						sort(vec.begin(), vec.end(), [](const std::pair<float, float>& left, const std::pair<float, float>& right) {return left.first < right.first; });
						float fringeAngle = 0.005;
						if (acos(vec.at(0).second) < fringeAngle) isFringeSlab = true;
						if (acos(vec.at(1).second) < fringeAngle) isFringeSlab = true;
					}
				}
			}

			/*�����������*/
			// ����� �� ������� � ���� 
			int sky = (view.getHeight() / 2.0) - view.getHeight() / (distanceSlab);
			int ground = view.getHeight() - sky;
			sky = (view.getHeight() / 2.0) - view.getHeight() / (distanceWall);

			// ������ ������ ��� �����������
			int skySlab = sky + player.getJump();
			if (world.texture[(int)((int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y)] == '2') {
				while (sky < skySlab)
					sky += 1 + player.getSpeed() * (int)view.getFPS();
			}

			short ShadeWall = ' ', ShadeSlab = ' ', ShadeFringle = ' ', ShadeClimb = ' ', ShadeStar = ' ';

			if (distanceWall <= player.getDepthDisplay() / 6.0f)			ShadeFringle = '!';
			else if (distanceWall < player.getDepthDisplay() / 4.0f)		ShadeFringle = '!';
			else if (distanceWall < player.getDepthDisplay() / 3.0f)		ShadeFringle = '!';
			else if (distanceWall < player.getDepthDisplay())				ShadeFringle = '!';
			else															ShadeFringle = ShadeStar;

			if (distanceWall <= player.getDepthDisplay() / 6.0f)			ShadeWall = 'O';
			else if (distanceWall < player.getDepthDisplay() / 4.0f)		ShadeWall = 'Z';
			else if (distanceWall < player.getDepthDisplay() / 3.0f)		ShadeWall = 'V';
			else if (distanceWall < player.getDepthDisplay())				ShadeWall = 'Y';
			else															ShadeWall = ShadeStar;

			if (distanceWall <= player.getDepthDisplay() / 6.0f)			ShadeClimb = '5';
			else if (distanceWall < player.getDepthDisplay() / 4.0f)		ShadeClimb = 'S';
			else if (distanceWall < player.getDepthDisplay() / 3.0f)		ShadeClimb = '4';
			else if (distanceWall < player.getDepthDisplay())				ShadeClimb = 'J';
			else															ShadeClimb = ShadeStar;
			if (isFringe)													ShadeClimb = '!';

			if (distanceSlab <= player.getDepthDisplay() / 6.0f)			ShadeSlab = '5';
			else if (distanceSlab < player.getDepthDisplay() / 4.0f)		ShadeSlab = 'S';
			else if (distanceSlab < player.getDepthDisplay() / 3.0f)		ShadeSlab = '4';
			else if (distanceSlab < player.getDepthDisplay())				ShadeSlab = 'J';
			else															ShadeSlab = ShadeStar;
			if (isFringeSlab)												ShadeSlab = '!';

			for (int y = 0; y < view.getHeight(); y++) {
				if (y <= sky) view.setCharPixel(y, x, ShadeStar);																					// ����
				else if (y > sky && y <= view.getHeight() / 2.0)																					// �����
					view.setCharPixel(y, x, ShadeWall);
				else if (y < (view.getHeight() + player.getJumpFringle()) / 2.0 && y >(view.getHeight() - player.getJumpFringle()) / 2.0			// ����� ���������
					&& world.texture[(int)(player.getPosition().y + (int)player.getPosition().x * world.textureSize.x)] != '2')
					view.setCharPixel(y, x, ShadeFringle);
				else if (y > view.getHeight() / 2.0 && y <= ground - 1) {																			// ��������
					if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '2')
						ground = view.getHeight() - sky + 2 * player.getJump();
						view.setCharPixel(y, x, ShadeWall);
					if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] != '2')
						view.setCharPixel(y, x, ShadeSlab);

				}
				else if (y > ground - 1 && y <= ground) view.setCharPixel(y, x, ShadeFringle);														// �������
				else {																																// �����
					float distantionGround = 1.0f - ((y - view.getHeight() / 2.0f) / (view.getHeight() / 2.0f));
					if (distantionGround < 0.49)		ShadeWall = 'G';																			// 0.66			
					else if (distantionGround < 0.66)	ShadeWall = 'C';																			// 0.745		
					else if (distantionGround < 0.745)	ShadeWall = '3';																			// 0.82			
					else if (distantionGround < 0.95)	ShadeWall = 'L';																			// 0.95			
					else								ShadeWall = ' ';
					view.setCharPixel(y, x, ShadeWall);
				}
				if (world.texture[(int)player.getPosition().x * world.textureSize.x + (int)player.getPosition().y] == '2') {
					if (y < (view.getHeight() + player.getJumpFringle() / 2) / 2.0 + player.getJump() && y >(view.getHeight() - player.getJumpFringle() / 2) / 2.0 + player.getJump()) view.setCharPixel(y, x, ShadeFringle);	// ����� ���������
					if (y > (view.getHeight() + player.getJumpFringle() / 2) / 2.0 + player.getJump() - 1 && y <= ground) view.setCharPixel(y, x, ShadeClimb);																	// ��������
					if (y > ground - 1 && y <= ground) view.setCharPixel(y, x, ShadeFringle);																																	// �������
				}
			}
		}

		if (player.getPosition().y >= 63.0f) {
			for (int y = 0; y < win.textureSize.y; y++)
				for (int x = 0; x < win.textureSize.x; x++)
					view.setCharPixel(y, x, win.texture[y * win.textureSize.x + x]);
			player.setSpeed(0.0f);
			player.setCameraSpeed(0.0f);
		}


		view.setCharPixel(view.getHeight(), -1, '\0');
		view.updateConsole();
	}

}