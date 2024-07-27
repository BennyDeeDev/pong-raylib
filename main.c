#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Rectangle RectanglePosToRectangle(Vector2 rectanglePos, int rectangleWidth, int rectangleHeight)
{
    return (Rectangle){rectanglePos.x,
                       rectanglePos.y,
                       rectangleWidth,
                       rectangleHeight};
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pong Raylib C");
    SetTargetFPS(60);

    const int screenWidthCenter = screenWidth / 2;
    const int screenHeightCenter = screenHeight / 2;

    const int rectangleWidth = 14;
    const int rectangleHeight = 64;

    const int paddingX = 48;
    const int paddingY = 48;
    const int moveY = 4;

    const Color rectangleColor = LIME;
    const Color ballColor = PURPLE;
    const Color textColor = RAYWHITE;

    Vector2 rectangleLeftPos = {paddingX, screenHeightCenter - (rectangleHeight / 2)};
    Vector2 rectangleRightPos = {screenWidth - paddingX - rectangleWidth, screenHeightCenter - (rectangleHeight / 2)};

    const int ballRadius = 8;
    const float ballSpeed = 4;
    Vector2 ballPos = {screenWidthCenter, screenHeightCenter};
    Vector2 ballVelocity = {ballSpeed, ballSpeed};

    bool didGameStart = false;

    // 0 => No Winner
    // 1 => Player 1 won!
    // 2 => Player 2 won!
    int winner = 0;

    char winnerText[50];
    int fontSizeWinner = 48;
    int paddingYWinner = 128;
    const Color winnerColor = GOLD;

    int leftPlayerScore = 0;
    int rightPlayerScore = 0;
    char leftPlayerScoreText[10];
    char rightPlayerScoreText[10];

    char *spacebarText = "Press Spacebar to play!";
    int fontSizeSpacebar = 36;
    int paddingYSpacebar = 256;

    int fontSizeScore = 36;
    int paddingXScore = 64;
    Vector2 leftPlayerScorePos = {paddingX + paddingXScore, paddingY};
    Vector2 rightPlayerScorePos = {screenWidth - paddingX - paddingXScore, paddingY};
    int scoreMax = 11;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (leftPlayerScore >= scoreMax || rightPlayerScore >= scoreMax)
        {
            didGameStart = false;
            // TODO: Don't set it to 0 so you can see the Score when someone wins
            leftPlayerScore = 0;
            rightPlayerScore = 0;

            winner = leftPlayerScore >= scoreMax ? 1 : 2;
        }

        if (IsKeyDown(KEY_W) && rectangleLeftPos.y >= 0)
        {
            rectangleLeftPos.y = rectangleLeftPos.y - moveY;
        }
        else if (IsKeyDown(KEY_S) && rectangleLeftPos.y <= screenHeight - rectangleHeight)
        {
            rectangleLeftPos.y = rectangleLeftPos.y + moveY;
        }

        if (IsKeyDown(KEY_UP) && rectangleRightPos.y >= 0)
        {
            rectangleRightPos.y = rectangleRightPos.y - moveY;
        }
        else if (IsKeyDown(KEY_DOWN) && rectangleRightPos.y <= screenHeight - rectangleHeight)
        {
            rectangleRightPos.y = rectangleRightPos.y + moveY;
        }

        if (IsKeyPressed(KEY_SPACE) && !didGameStart)
        {
            didGameStart = true;
            winner = 0;

            srand(time(NULL));

            if (rand() % 2 == 0)
            {
                ballVelocity.x = -ballVelocity.x;
            }
        }

        if (didGameStart)
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
            didGameStart = false;
        }
        else if (ballPos.x >= screenWidth)
        {
            leftPlayerScore = leftPlayerScore + 1;
            didGameStart = false;
        }
        else if (ballPos.y <= 0)
        {
            ballVelocity.y = -ballVelocity.y;
        }
        else if (ballPos.y >= screenHeight)
        {
            ballVelocity.y = -ballVelocity.y;
        }
        else if (CheckCollisionCircleRec(ballPos, ballRadius, RectanglePosToRectangle(rectangleLeftPos, rectangleWidth, rectangleHeight)) ||
                 CheckCollisionCircleRec(ballPos, ballRadius, RectanglePosToRectangle(rectangleRightPos, rectangleWidth, rectangleHeight)))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        DrawRectangle(rectangleLeftPos.x, rectangleLeftPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        DrawCircle(ballPos.x, ballPos.y, ballRadius, ballColor);

        DrawRectangle(rectangleRightPos.x, rectangleRightPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        sprintf(leftPlayerScoreText, "Score: %d", leftPlayerScore);
        DrawText(leftPlayerScoreText, leftPlayerScorePos.x, leftPlayerScorePos.y, fontSizeScore, textColor);

        sprintf(rightPlayerScoreText, "Score: %d", rightPlayerScore);

        DrawText(rightPlayerScoreText, rightPlayerScorePos.x - MeasureText(rightPlayerScoreText, fontSizeScore), rightPlayerScorePos.y, fontSizeScore, textColor);

        if (winner)
        {
            sprintf(winnerText, "Player %d won!", winner);
            int winnerTextSize;

            DrawText(winnerText, screenWidthCenter - (MeasureText(winnerText, fontSizeWinner) / 2), paddingYWinner, fontSizeWinner, winnerColor);
        }

        if (!didGameStart)
        {
            DrawText(spacebarText, screenWidthCenter - (MeasureText(spacebarText, fontSizeSpacebar) / 2), paddingYSpacebar, fontSizeSpacebar, textColor);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
