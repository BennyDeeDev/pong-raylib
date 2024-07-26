#include "raylib.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pong Raylib C");
    SetTargetFPS(60);

    const int screenWidthCenter = 1280 / 2;
    const int screenHeightCenter = 720 / 2;
    const int rectangleWidth = 14;
    const int rectangleHeight = 64;
    const int paddingX = 40;
    const int moveY = rectangleHeight / 2;
    const int ballRadius = 8;

    const Color rectangleColor = LIME;
    const Color ballColor = PURPLE;

    Vector2 rectangleLeftPos = {paddingX, screenHeightCenter - (rectangleHeight / 2)};
    Vector2 ballPos = {paddingX + rectangleWidth + ballRadius, screenHeightCenter};
    Vector2 rectangleRightPos = {screenWidth - paddingX - rectangleWidth, screenHeightCenter - (rectangleHeight / 2)};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_W))
        {
            rectangleLeftPos.y = rectangleLeftPos.y - moveY;
        }
        else if (IsKeyPressed(KEY_S))
        {
            rectangleLeftPos.y = rectangleLeftPos.y + moveY;
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
                }

        DrawRectangle(rectangleLeftPos.x, rectangleLeftPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        DrawCircle(ballPos.x, ballPos.y, ballRadius, ballColor);

        DrawRectangle(rectangleRightPos.x, rectangleRightPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
