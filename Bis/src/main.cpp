#include <iostream>
#include <string>
#include "raylib.h"

bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;

const int NUM_QUESTIONS = 6;

const char* questions[NUM_QUESTIONS] = {
    "What is 2 + 2?",
    "What is 5 * 3?",
    "What is 10 / 2?",
    "What is 8 - 4?",
    "What is 3 + 7?",
    "What is 12 / 3?"
};

const std::string answers[NUM_QUESTIONS] = {
    "4",
    "15",
    "5",
    "4",
    "10",
    "4"
};

void Maths()
{
    static int currentQuestion = 0;
    static std::string userAnswers[NUM_QUESTIONS];

    ClearBackground(RAYWHITE);

    if (currentQuestion < NUM_QUESTIONS)
    {
        DrawText(questions[currentQuestion], 100, 100, 20, DARKGRAY);
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= 32 && key <= 126)
        {
            userAnswers[currentQuestion] += key;
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && !userAnswers[currentQuestion].empty())
        {
            userAnswers[currentQuestion].pop_back();
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            currentQuestion++;
        }
    }
    else
    {
        ClearBackground(RAYWHITE);
        DrawText("Results:", 100, 100, 20, DARKGRAY);

        for (int i = 0; i < NUM_QUESTIONS; i++)
        {
            std::string resultText = "Question " + std::to_string(i + 1) + ": ";
            if (userAnswers[i] == answers[i])
            {
                resultText += "Correct";
            }
            else
            {
                resultText += "Incorrect";
            }

            DrawText(resultText.c_str(), 100, 140 + i * 30, 20, DARKGRAY);
        }

        DrawText("Press ESC to return", 100, 320, 20, DARKGRAY);

        if (IsKeyDown(KEY_ESCAPE))
        {
            currentQuestion = 0;
            for (int i = 0; i < NUM_QUESTIONS; i++)
            {
                userAnswers[i].clear();
            }
            inGame = false;
        }
    }
}

const int NUM_GEO_QUESTIONS = 5;

const char* geoQuestions[NUM_GEO_QUESTIONS] = {
    "What is the capital of France?",
    "What is the largest desert in the world?",
    "Where is the Great Barrier Reef located?",
    "Which country is famous for the Amazon Rainforest?",
    "What is the tallest mountain in the world?"
};

const std::string geoAnswers[NUM_GEO_QUESTIONS] = {
    "Paris",
    "Sahara",
    "Australia",
    "Brazil",
    "Everest"
};

void Geography()
{
    static int currentQuestion = 0;
    static std::string userAnswers[NUM_GEO_QUESTIONS];

    ClearBackground(RAYWHITE);

    if (currentQuestion < NUM_GEO_QUESTIONS)
    {
        DrawText(geoQuestions[currentQuestion], 100, 100, 20, DARKGRAY);
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= 32 && key <= 126)
        {
            userAnswers[currentQuestion] += key;
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && !userAnswers[currentQuestion].empty())
        {
            userAnswers[currentQuestion].pop_back();
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            currentQuestion++;
        }
    }
    else
    {
        ClearBackground(RAYWHITE);
        DrawText("Geography Results:", 100, 100, 20, DARKGRAY);

        for (int i = 0; i < NUM_GEO_QUESTIONS; i++)
        {
            std::string resultText = "Question " + std::to_string(i + 1) + ": ";
            if (userAnswers[i] == geoAnswers[i])
            {
                resultText += "Correct";
            }
            else
            {
                resultText += "Incorrect";
            }

            DrawText(resultText.c_str(), 100, 140 + i * 30, 20, DARKGRAY);
        }

        DrawText("Press ESC to return", 100, 340, 20, DARKGRAY);

        if (IsKeyDown(KEY_ESCAPE))
        {
            currentQuestion = 0;
            for (int i = 0; i < NUM_GEO_QUESTIONS; i++)
            {
                userAnswers[i].clear();
            }
            inGame = false;
        }
    }
}

void History()
{
    std::cout << "History function called!" << std::endl;
}

void Settings()
{
    std::cout << "Settings function called!" << std::endl;
}


void StartMenu()
{
    ClearBackground(RAYWHITE);

    DrawText("School Test Program", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Start" : "Start", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Settings" : "Settings", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> Exit" : "Exit", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption > 0)
    {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2)
    {
        selectedOption++;
    }

    if (IsKeyDown(KEY_ESCAPE))
    {
        if (inGame)
        {
            inGame = false;
        }
        else
        {
            exitWindow = true;
        }
    }
}

void SecondMenu()
{
    ClearBackground(RAYWHITE);

    DrawText("School Subjects", 100, 100, 40, GRAY);

    const char* subjects[] = { "Geography", "Maths", "History" };

    for (int i = 0; i < 3; i++)
    {
        DrawText(selectedOption == i ? (std::string("> ") + subjects[i]).c_str() : subjects[i], 100, 200 + i * 40, 20, DARKGRAY);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedOption == 0)
        {
            inGame = true;
        }
        else if (selectedOption == 1)
        {
            inGame = true;
        }
        else if (selectedOption == 2)
        {
            History();
        }
    }

    if (IsKeyPressed(KEY_UP) && selectedOption > 0)
    {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2)
    {
        selectedOption++;
    }
}

int main()
{
    InitWindow(800, 450, "School test program");

    while (!exitWindow)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!inGame)
        {
            SecondMenu();
        }
        else
        {
            if (selectedOption == 0)
            {
                Geography();
            }
            else if (selectedOption == 1)
            {
                Maths();
            }
        }

        if (IsKeyDown(KEY_ESCAPE))
        {
            if (inGame)
            {
                inGame = false;
            }
            else
            {
                exitWindow = true;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
