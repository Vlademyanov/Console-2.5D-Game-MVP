#include "Player.h"
#include <iostream>
#include <string>

Player::Player() {

	health;
	attack = 2;
	currentHealth = 100;
	speed = 3.0f;
	position.x = 29;
	position.y = 2;
	directionView = 0.0f;

	FOV = M_PI / 2;
	depthDisplay = 24.0f;
	cameraSpeed = 5.5f;
	jumpSize = 30;
	jumpFringleSize = 30;
}

// Position
void Player::setPosition(Point position) { this->position = position; }
Point Player::getPosition()  { return position; }
void Player::setPositionX(double position)  { this->position.x = position; }
void Player::setPositionY(double position)  { this->position.y = position; }

// DirectionView
void Player::setDirectionView(float directionView) { this->directionView = directionView; }
float Player::getDirectionView() { return directionView; }

// FOV
void Player::setFOV(float FOV)   { this->FOV = FOV; }
float Player::getFOV()   { return FOV; }

// DepthDisplay
void Player::setDepthDisplay(float DepthDisplay) { this->depthDisplay = DepthDisplay; }
float Player::getDepthDisplay() { return depthDisplay; }

// CameraSpeed
void Player::setCameraSpeed(float CameraSpeed) { this->cameraSpeed = CameraSpeed; }
float Player::getCameraSpeed() { return cameraSpeed; }

// Speed
void Player::setSpeed(float speed) { this->speed = speed; }
float Player::getSpeed() { return speed; }

// Jump
void Player::setJump(float jump) { this->jumpSize = jump; }
float Player::getJump() { return jumpSize; }

// JumpFringle
void Player::setJumpFringle(float jumpFringle) { this->jumpFringleSize = jumpFringle; }
float Player::getJumpFringle() { return jumpFringleSize; }