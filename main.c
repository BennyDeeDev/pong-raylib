#include "raylib.h"
#include <stdio.h>

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

    const int paddingX = 48;
    const int paddingY = 48;
    const int moveY = rectangleHeight / 2;

    const int ballRadius = 8;
    const float ballSpeed = 80;

    const Color rectangleColor = LIME;
    const Color ballColor = PURPLE;
    const Color textColor = RAYWHITE;

    Vector2 rectangleLeftPos = {paddingX, screenHeightCenter - (rectangleHeight / 2)};
    Vector2 rectangleRightPos = {screenWidth - paddingX - rectangleWidth, screenHeightCenter - (rectangleHeight / 2)};

    Vector2 ballPos = {screenWidthCenter, screenHeightCenter};
    Vector2 ballVelocity = {4, 4};

    bool isGameStarted = false;
    int leftPlayerScore = 0;
    int rightPlayerScore = 0;
    char leftPlayerScoreText[10];
    char rightPlayerScoreText[10];

    Vector2 leftPlayerScorePos = {paddingX, paddingY};
    Vector2 rightPlayerScorePos = {screenWidth - paddingX, paddingY};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (leftPlayerScore >= 11 || rightPlayerScore >= 11)
        {
            isGameStarted = false;
            leftPlayerScore = 0;
            rightPlayerScore = 0;
        }

        if (IsKeyPressed(KEY_W))
        {
            rectangleLeftPos.y = rectangleLeftPos.y - moveY;
        }
        else if (IsKeyPressed(KEY_S))
        {
            rectangleLeftPos.y = rectangleLeftPos.y + moveY;
        }

        if (IsKeyPressed(KEY_SPACE) && !isGameStarted)
        {
            isGameStarted = true;
        }

        if (isGameStarted)
        {
            ballPos.x = ballPos.x + ballVelocity.x;
            ballPos.y = ballPos.y + ballVelocity.y;
        }
        else
        {
            ballPos.x = screenWidthCenter;
            ballPos.y = screenHeightCenter;
        }

        if (ballPos.x <= 0)
        {
            rightPlayerScore = rightPlayerScore + 1;
            isGameStarted = false;
        }
        else if (ballPos.x >= screenWidth)
        {
            leftPlayerScore = leftPlayerScore + 1;
            isGameStarted = false;
        }
        else if (ballPos.y <= 0)
        {
            ballVelocity.y = -ballVelocity.y;
        }
        else if (ballPos.y >= screenHeight)
        {
            ballVelocity.y = -ballVelocity.y;
        }

        DrawRectangle(rectangleLeftPos.x, rectangleLeftPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        DrawCircle(ballPos.x, ballPos.y, ballRadius, ballColor);

        DrawRectangle(rectangleRightPos.x, rectangleRightPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        sprintf(leftPlayerScoreText, "Score: %d", leftPlayerScore);
        DrawText(leftPlayerScoreText, leftPlayerScorePos.x, leftPlayerScorePos.y, 22, textColor);

        sprintf(rightPlayerScoreText, "Score: %d", rightPlayerScore);

        int rightPlayerScoreTextSize;
        rightPlayerScoreTextSize = MeasureText(rightPlayerScoreText, 22);
        DrawText(rightPlayerScoreText, rightPlayerScorePos.x - rightPlayerScoreTextSize, rightPlayerScorePos.y, 22, textColor);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
