#include <iostream>
#include "raylib.h"

bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;

void Geography()
{
    exitWindow = true;
}

void Maths()
{
    exitWindow = true;
}

void History()
{
    exitWindow = true;
}


void Settings()
{
    exitWindow = true;
}
void SecondMenu() {

    ClearBackground(RAYWHITE);

    DrawText("School Subjects", 100, 100, 40, GRAY);

    const char* subjects[] = { "Geography", "Maths", "History" };

    for (int i = 0; i < 3; i++) {
        DrawText(selectedOption == i ? (std::string("> ") + subjects[i]).c_str() : subjects[i], 100, 200 + i * 40, 20, DARKGRAY);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedOption == 0) {
            Geography();
        }
        else if (selectedOption == 1) {
            Maths();
        }
        else if (selectedOption == 2) {
            History();
        }
    }

    if (IsKeyPressed(KEY_UP) && selectedOption > 0) {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2) {
        selectedOption++;
    }
}
void StartMenu() {

    ClearBackground(RAYWHITE);

    DrawText("School Test Program", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Start" : "Start", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Settings" : "Settings", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> Exit" : "Exit", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) and selectedOption >= 0)
        selectedOption--;

    if (IsKeyPressed(KEY_DOWN) and selectedOption <= 2)
        selectedOption++;
}

int main()
{
    InitWindow(800, 450, "School test program");

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
            if (selectedOption == 0)
            {
                inGame = true;
            }
            else if (selectedOption == 1)
            {
               Settings();
            }
            else if (selectedOption == 2)
            {
                exitWindow = true;
            }
        }

        if (IsKeyDown(KEY_ESCAPE)) {
            exitWindow = true;
        }

        EndDrawing();
    }
}