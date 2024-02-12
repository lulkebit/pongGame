#pragma once
#include "raylib.h"

namespace game {
	const int screenWidth = 800;
	const int screenHeight = 450;

	Vector2 ballPosition;
	Vector2 ballSpeed;
	int ballRadius;

	Rectangle playerOne;
	int scorePlayerOne;

	Rectangle playerTwo;
	int scorePlayerTwo;

	int playerSpeed;

	Rectangle goalPlayerOne;
	Rectangle goalPlayerTwo;
}

void draw();

void playerMovement();

void ballMovement();

void checkGoal();

void reset();