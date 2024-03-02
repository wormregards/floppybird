#include "../header/player.h"

bool paused = false;
void handleObstacleGen(Rectangle rectangle[], Rectangle player, int x) {
	for (int i = 0; i < 100; i++) {
		if (CheckCollisionRecs(rectangle[i], player)) {
			paused = true;
		}

		if (IsKeyPressed(KEY_R) && paused) {
			paused = false;
			resetPlayer();

			// reset obstacles
			for (int i = 0; i < 100; i++) {
				/// randomNumber = rand() % (1 + 1 - 0) + 0;
				rectangle[i].x = 100 + 80 * i;
				if (x == 1) {
					rectangle[i].y = -GetScreenHeight() - 50;
				}
				else {
					rectangle[i].y = getPlayerPosition().y;
				}
				// obstacleContainer[i].y = getPlayerPosition().y;		
				rectangle[i].height = GetScreenHeight();
				rectangle[i].width = 10;
			}
 
		}

		if (rectangle[i].x < getPlayerPosition().x - (GetScreenWidth() / 2)) {
			rectangle[i].x = rectangle[99].x;
			rectangle[99].x = rectangle[99].x + 80;
		}
		DrawRectangleRec(rectangle[i], WHITE);
	}
}

int main() {
	int screenWidth = 800;
	int screenHeight = 700;
	int targetFPS = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Floppy Birds");
	SetTargetFPS(targetFPS);
	float deltaTime = GetFrameTime();

	loadPlayer();

	Camera2D camera = { 0 };
	camera.zoom = 4.f;
	camera.target = getPlayerPosition();
	camera.offset = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };

	Rectangle obstacleContainer[100] = { 0 };
	Rectangle bottomObstacles[100] = { 0 };
	// populate initial obstacles
	for (int i = 0; i < 100; i++) {
		/// randomNumber = rand() % (1 + 1 - 0) + 0;
		obstacleContainer[i].x = 100 + 80 * i;
		obstacleContainer[i].y = -GetScreenHeight() - 50;
		// obstacleContainer[i].y = getPlayerPosition().y;		
		obstacleContainer[i].height = GetScreenHeight();
		obstacleContainer[i].width = 10;
	}

	for (int i = 0; i < 100; i++) {
		/// randomNumber = rand() % (1 + 1 - 0) + 0;
		bottomObstacles[i].x = 100 + 80 * i;
		// bottomObstacles[i].y = -GetScreenHeight() - 20;
		bottomObstacles[i].y = getPlayerPosition().y;
		bottomObstacles[i].height = GetScreenHeight();
		bottomObstacles[i].width = 10;
	}

	

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground((Color) { 0x17, 0x17, 0x17, 0xFF });
		deltaTime = GetFrameTime();

		// resize event
		if (GetScreenWidth() != screenWidth || GetScreenHeight() != screenHeight) {
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();

			camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
			camera.zoom = 5.f;
		}
		
		if (!paused) {
			playerHop(deltaTime);
		}

		camera.target.x = getPlayerPosition().x;
		BeginMode2D(camera);
			// DrawRectangleRec(getPlayerCollider(), ORANGE);
			handleObstacleGen(obstacleContainer, getPlayerCollider(), 1);
			handleObstacleGen(bottomObstacles, getPlayerCollider(), 2);
			DrawTextureRec(getPlayer(), getPlayerRect(), getPlayerPosition(), WHITE);	
		EndMode2D();
		if (paused) {
			DrawRectangle(0, 0, 300, 20, PINK);
			DrawText("You lose! Press R to restart", 0, 0, 20, WHITE);
		}
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

