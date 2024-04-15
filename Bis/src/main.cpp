#include <string>
#include "raylib.h"

using namespace std;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "School Test Program");

    SetTargetFPS(60);

    string question = "What is the capital of France?";
    string correctAnswer = "Paris";
    string answerInput;

    int resultTimer = 0;
    int resultDuration = 120;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(question.c_str(), 100, 100, 20, DARKGRAY);
        DrawText("Your answer: ", 100, 150, 20, DARKGRAY);
        DrawText(answerInput.c_str(), 250, 150, 20, DARKGRAY);

        int key = GetCharPressed();

        if (key > 0 and answerInput.length() < 99)
            answerInput.push_back((char)key);

        if (IsKeyPressed(KEY_BACKSPACE) and !answerInput.empty())
            answerInput.pop_back();
        

        if (IsKeyPressed(KEY_ENTER))
            resultTimer = resultDuration;
 

        if (resultTimer > 0)
        {
            if (answerInput == correctAnswer)
                DrawText("Correct!", 100, 200, 20, GREEN);
            
            else
                DrawText("Incorrect. Please try again.", 100, 200, 20, RED);
       
            resultTimer--;
        }

        EndDrawing();
    }

    CloseWindow();

}