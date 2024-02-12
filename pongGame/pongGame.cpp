#include "pongGame.h"

using namespace game;

int main()
{
	// Initialization
	InitWindow(screenWidth, screenHeight, "pongGame");

	ballPosition = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
	ballSpeed = { 5.0f, 4.0f };
	ballRadius = 10;

	playerOne = { 20, GetScreenHeight() / 2.f - 100 / 2, 10, 100 };
	scorePlayerOne = 0;

	playerTwo = { GetScreenWidth() - 30.f, GetScreenHeight() / 2.f - 100, 10, 100 };
	scorePlayerTwo = 0;

	playerSpeed = 4;

	goalPlayerOne = { 0, 0, 1, (float)GetScreenHeight() };
	goalPlayerTwo = { GetScreenWidth() - 1.f, 0, 1, (float)GetScreenHeight() };

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		playerMovement();
		ballMovement();
		checkGoal();

		// Draw
		draw();
	}

	// De-Initialization
	CloseWindow();        // Close window and OpenGL context
	return 0;
}

void draw() {
	BeginDrawing();
	ClearBackground(BLACK);

	DrawRectangleRec(playerOne, WHITE);
	DrawRectangleRec(playerTwo, WHITE);
	DrawRectangleRec(goalPlayerOne, GREEN);
	DrawRectangleRec(goalPlayerTwo, RED);

	DrawCircleV(ballPosition, (float)ballRadius, WHITE);

	DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);

	// Score drawing
	DrawText(
		TextFormat("%d", scorePlayerOne),
		(GetScreenWidth() / 2) - 40 - MeasureText(TextFormat("%d", scorePlayerOne), 20),
		40,
		20,
		WHITE
	);
	DrawText(TextFormat("%d", scorePlayerTwo), (GetScreenWidth() / 2) + 40, 40, 20, WHITE);

	EndDrawing();
}

void playerMovement() {
	if (IsKeyDown(KEY_W) && playerOne.y >= 0)
		playerOne.y -= playerSpeed;

	if (IsKeyDown(KEY_S) && playerOne.y <= (GetScreenHeight() - playerOne.height))
		playerOne.y += playerSpeed;

	if (IsKeyDown(KEY_UP) && playerTwo.y >= 0)
		playerTwo.y -= playerSpeed;

	if (IsKeyDown(KEY_DOWN) && playerTwo.y <= (GetScreenHeight() - playerTwo.height))
		playerTwo.y += playerSpeed;
}

void ballMovement() {
	ballPosition.x += ballSpeed.x;
	ballPosition.y += ballSpeed.y;

	if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius))
		ballSpeed.x *= -1.0f;

	if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius))
		ballSpeed.y *= -1.0f;

	if (CheckCollisionCircleRec(ballPosition, ballRadius, playerOne))
		ballSpeed.x *= -1.0f;

	if (CheckCollisionCircleRec(ballPosition, ballRadius, playerTwo))
		ballSpeed.x *= -1.0f;
}

void checkGoal() {
	if (CheckCollisionCircleRec(ballPosition, ballRadius, goalPlayerOne)) {
		scorePlayerTwo++;
		ballSpeed.x++;
		ballSpeed.y++;
		reset();
	}

	if (CheckCollisionCircleRec(ballPosition, ballRadius, goalPlayerTwo)) {
		scorePlayerOne++;
		ballSpeed.x++;
		ballSpeed.y++;
		reset();
	}

}

void reset() {
	playerOne.x = 20;
	playerOne.y = GetScreenHeight() / 2.f - 100;

	playerTwo.x = GetScreenWidth() - 30.f;
	playerTwo.y = GetScreenHeight() / 2.f - 100;

	ballPosition = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
}