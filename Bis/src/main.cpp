﻿#include <iostream>
#include "raylib.h"

void StartMenu();
void SecondMenu();
void Game();
void Settings();

bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;


void StartMenu() {

    ClearBackground(RAYWHITE);

    DrawText("School Test Program", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Start" : "Start", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Settings" : "Settings", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> Exit" : "Exit", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption >= 0)
        selectedOption--;

    if (IsKeyPressed(KEY_DOWN) && selectedOption <= 2)
        selectedOption++;
}
void SecondMenu() {
    ClearBackground(RAYWHITE);
    selectedOption = 0;
    DrawText("School Subjects", 100, 100, 40, GRAY);
    
    DrawText(selectedOption == 0 ? "> Geography" : "Geography", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Maths" : "Maths", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> History" : "History", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption >= 0)
        selectedOption--;

    if (IsKeyPressed(KEY_DOWN) && selectedOption <= 2)
        selectedOption++;

    
}
void Game()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    static const char* question = "What is the capital of France?";
    static const char* correctAnswer = "Paris";
    static std::string answer = "";

    DrawText(question, 100, 100, 30, DARKGRAY);
    DrawText("Your Answer: ", 100, 150, 20, DARKGRAY);

    DrawRectangleLines(300, 150, 200, 30, DARKGRAY);
    DrawText(answer.c_str(), 305, 155, 20, DARKGRAY);


    if (!IsKeyDown(KEY_ENTER))
    {
        char keyPressed = GetKeyPressed();

        if (keyPressed != 0)
        {
            answer += keyPressed;
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (answer == correctAnswer)
            DrawText("Correct!", 100, 200, 20, GREEN);
        else
            DrawText("Incorrect! The correct answer is Paris.", 100, 200, 20, RED);
    }

//    EndDrawing();
}

void Settings()
{
    exitWindow = true;
}

int main()
{
    InitWindow(1920, 1080, "School test program");
    SetWindowState(FLAG_FULLSCREEN_MODE);


    while (!exitWindow)
    {
        BeginDrawing();

        if (!inGame) {
            StartMenu();
        }
        else {
            SecondMenu();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            switch (selectedOption)
            {
            case 0:
                inGame = true;
                break;
            case 1:
                Settings();
                break;
            case 2:
                exitWindow = true;
                break;
            }
        }
        
        EndDrawing();
    }
    CloseWindow();

    return 0;
}