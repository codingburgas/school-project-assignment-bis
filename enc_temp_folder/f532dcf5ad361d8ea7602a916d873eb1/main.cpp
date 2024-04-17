#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;

struct Question
{
    string questionText;
    string correctAnswer;
};

enum MenuOption
{
    START,
    EXIT,
    FULLSCREEN
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int questionFontSize = 20;
    const int numQuestions = 5;

    InitWindow(screenWidth, screenHeight, "Beautiful Menu");

    SetTargetFPS(60);

    MenuOption selectedOption = START;
    Question questions[numQuestions] = {
        {"Question 1: What is the capital of France?", "Paris"},
        {"Question 2: Which country is known as the Land of the Rising Sun?", "Japan"},
        {"Question 3: What is the largest ocean on Earth?", "Pacific Ocean"},
        {"Question 4: What is the hottest continent?", "Africa"},
        {"Question 5: Where is the Great Barrier Reef located?", "Australia"}
    };

    string answerInput;
    int currentQuestion = 0;
    int correctAnswers = 0;
    int spacing = 40;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (selectedOption == START)
        {
            for (int i = 0; i < numQuestions; ++i)
            {
                DrawText(questions[i].questionText.c_str(), 100, 100 + i * spacing, questionFontSize, DARKGRAY);

                if (currentQuestion == i)
                {
                    DrawText(answerInput.c_str(), 100, 130 + i * spacing, questionFontSize, DARKGRAY);
                }
            }

            if (currentQuestion < numQuestions)
            {
                int key = GetKeyPressed();

                if (key > 0 && answerInput.length() < 99)
                    answerInput.push_back((char)key);

                if (IsKeyPressed(KEY_ENTER))
                {
                    if (answerInput == questions[currentQuestion].correctAnswer)
                        correctAnswers++;

                    answerInput = "";
                    currentQuestion++;
                }
            }
            else
            {
                DrawText("Test Completed", 100, 100 + numQuestions * spacing, questionFontSize, DARKGRAY);
                DrawText(("Correct Answers: " + to_string(correctAnswers)).c_str(), 100, 130 + numQuestions * spacing, questionFontSize, DARKGRAY);

                // Reset variables for next test
                currentQuestion = 0;
                correctAnswers = 0;
                selectedOption = EXIT;
            }
        }
        else
        {
            DrawText("Menu:", 100, 100, questionFontSize, DARKGRAY);
            DrawText("1. Start Test", 100, 130, questionFontSize, DARKGRAY);
            DrawText("2. Toggle Fullscreen (Press F)", 100, 160, questionFontSize, DARKGRAY);
            DrawText("3. Exit (Press ESC)", 100, 190, questionFontSize, DARKGRAY);

            int key = GetKeyPressed();

            if (key == '1')
            {
                selectedOption = START;
                currentQuestion = 0; // Reset current question when starting a new test
                correctAnswers = 0; // Reset correct answers count
            }
            else if (key == '2')
            {
                ToggleFullscreen();
                selectedOption = START;
            }
            else if (key == '3' || IsKeyDown(KEY_ESCAPE))
                selectedOption = EXIT;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}