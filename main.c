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
    const int moveSpeed = 4;

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
    const int fontSizeWinner = 48;
    const int paddingYWinner = 128;
    const Color winnerColor = GOLD;

    int leftPlayerScore = 0;
    int rightPlayerScore = 0;
    char leftPlayerScoreText[10];
    char rightPlayerScoreText[10];

    char *spacebarText = "Press Spacebar to play!";
    const int fontSizeSpacebar = 36;
    const int paddingYSpacebar = 256;

    const int fontSizeScore = 36;
    const int paddingXScore = 64;
    Vector2 leftPlayerScorePos = {paddingX + paddingXScore, paddingY};
    Vector2 rightPlayerScorePos = {screenWidth - paddingX - paddingXScore, paddingY};
    const int scoreMax = 11;

    srand(time(NULL));

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

        // Move left paddle
        if (IsKeyDown(KEY_W) && rectangleLeftPos.y >= 0)
        {
            rectangleLeftPos.y -= moveSpeed;
        }
        else if (IsKeyDown(KEY_S) && rectangleLeftPos.y <= screenHeight - rectangleHeight)
        {
            rectangleLeftPos.y += moveSpeed;
        }

        // Move right paddle
        if (IsKeyDown(KEY_UP) && rectangleRightPos.y >= 0)
        {
            rectangleRightPos.y -= moveSpeed;
        }
        else if (IsKeyDown(KEY_DOWN) && rectangleRightPos.y <= screenHeight - rectangleHeight)
        {
            rectangleRightPos.y += moveSpeed;
        }

        // Start game
        if (IsKeyPressed(KEY_SPACE) && !didGameStart)
        {
            didGameStart = true;
            winner = 0;
            ballVelocity.x = ballSpeed * (rand() % 2 == 0 ? 1 : -1);
            ballVelocity.y = ballSpeed;
        }

        // Update ball position if the game has started
        if (didGameStart)
        {
            ballPos.x += ballVelocity.x;
            ballPos.y += ballVelocity.y;
        }
        else
        {
            ballPos = (Vector2){screenWidthCenter, screenHeightCenter};
        }

        // Ball collision with left or right wall
        if (ballPos.x <= 0)
        {
            rightPlayerScore++;
            didGameStart = false;
            ballVelocity.x = ballSpeed;
        }
        else if (ballPos.x >= screenWidth)
        {
            leftPlayerScore++;
            didGameStart = false;
            ballVelocity.x = ballSpeed;
        }

        // Ball collision with top or bottom wall
        if (ballPos.y <= 0 || ballPos.y >= screenHeight)
        {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball collision with paddles
        if (CheckCollisionCircleRec(ballPos, ballRadius, RectanglePosToRectangle(rectangleLeftPos, rectangleWidth, rectangleHeight)) ||
            CheckCollisionCircleRec(ballPos, ballRadius, RectanglePosToRectangle(rectangleRightPos, rectangleWidth, rectangleHeight)))
        {
            // Determine where the collision occurred and adjust velocity accordingly
            if (ballPos.y >= rectangleLeftPos.y && ballPos.y <= rectangleLeftPos.y + rectangleHeight ||
                ballPos.y >= rectangleRightPos.y && ballPos.y <= rectangleRightPos.y + rectangleHeight)
            {
                ballVelocity.x = -ballVelocity.x;
            }
            else
            {
                ballVelocity.y = -ballVelocity.y;
            }
        }

        // Draw paddles
        DrawRectangle(rectangleLeftPos.x, rectangleLeftPos.y, rectangleWidth, rectangleHeight, rectangleColor);
        DrawRectangle(rectangleRightPos.x, rectangleRightPos.y, rectangleWidth, rectangleHeight, rectangleColor);

        // Draw ball
        DrawCircle(ballPos.x, ballPos.y, ballRadius, ballColor);

        // Draw scores
        sprintf(leftPlayerScoreText, "Score: %d", leftPlayerScore);
        DrawText(leftPlayerScoreText, leftPlayerScorePos.x, leftPlayerScorePos.y, fontSizeScore, textColor);
        sprintf(rightPlayerScoreText, "Score: %d", rightPlayerScore);
        DrawText(rightPlayerScoreText, rightPlayerScorePos.x - MeasureText(rightPlayerScoreText, fontSizeScore), rightPlayerScorePos.y, fontSizeScore, textColor);

        // Draw winner text
        if (winner)
        {
            sprintf(winnerText, "Player %d won!", winner);
            DrawText(winnerText, screenWidthCenter - (MeasureText(winnerText, fontSizeWinner) / 2), paddingYWinner, fontSizeWinner, winnerColor);
        }

        // Draw spacebar text if game not started
        if (!didGameStart)
        {
            DrawText(spacebarText, screenWidthCenter - (MeasureText(spacebarText, fontSizeSpacebar) / 2), paddingYSpacebar, fontSizeSpacebar, textColor);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
