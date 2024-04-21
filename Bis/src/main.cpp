#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;


enum class GameState {
    StartMenu,
    Settings,
    SubjectSelection,
    GeographyQuiz,
    MathsQuiz,
    HistoryDisplay
};

GameState currentState = GameState::StartMenu;

static int longText1 = 0;
bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;

#define MAX_FONTS 4
void Settings() {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Settings");

    SetTargetFPS(60);               
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Settings", 350, 20, 20, DARKGRAY);
        DrawLine(220, 50, 590, 50, DARKGRAY);
        DrawText("Hi here you can take tests on different subjects", 120, 100, 20,  DARKGRAY);
        DrawText("to improve your knowledge and you will be graded accordingly", 100, 120, 20, DARKGRAY);

        EndDrawing();
        
    }
    int static currentQuestion = 0;
    DrawText("Press ESC to return", 100, 340, 20, DARKGRAY);

    if (IsKeyDown(KEY_ESCAPE))
    {
        currentQuestion = 0;
        inGame = false;
        currentState = GameState::StartMenu;
    }
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

    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedOption == 0)
        {
            currentState = GameState::SubjectSelection;
        }
        else if (selectedOption == 1){
            Settings();
        }
        else if (selectedOption == 2)
        {
            exitWindow = true;
        }
    }
}

void SubjectSelection()
{
    ClearBackground(RAYWHITE);

    DrawText("Choose subject:", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Geography" : "Geography", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Maths" : "Maths", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> History" : "History", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption > 0)
    {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2)
    {
        selectedOption++;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedOption == 0)
        {
            currentState = GameState::GeographyQuiz;
            inGame = true;
        }
        else if (selectedOption == 1)
        {
            currentState = GameState::MathsQuiz;
            inGame = true;
        }
        else if (selectedOption == 2)
        {
            currentState = GameState::HistoryDisplay;
            inGame = true;
        }
    }
}




const char* geoQuestions[5] = {
    "What is the capital of France?",
    "What is the largest desert in the world?",
    "Where is the Great Barrier Reef located?",
    "Which country is famous for the Amazon Rainforest?",
    "What is the tallest mountain in the world?"
};

const string geoAnswers[5] = {
    "Paris",
    "Sahara",
    "Australia",
    "Brazil",
    "Everest"
};

void GeographyQuiz()
{
    static int currentQuestion = 0;
    static string userAnswers[] = { "", "", "", "", "" };

    ClearBackground(RAYWHITE);

    if (currentQuestion < 5)
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

        for (int i = 0; i < 5; i++)
        {
            string resultText = "Question " + to_string(i + 1) + ": ";
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
            inGame = false;
            currentState = GameState::SubjectSelection;
        }
    }
}

const char* mathQuestions[5] = {
    "What is 15 multiplied by 6?",
    "What is the square root of 144?",
    "How many degrees are there in a right angle?",
    "What is the value of pi (π) to two decimal places?",
    "What is the sum of 87 and 45?"
};

const string mathAnswers[5] = {
    "90",
    "12",
    "90",
    "3.14",
    "132"
};

void MathsQuiz()
{
    static int currentQuestion = 0;
    static string userAnswers[] = { "", "", "", "", "" };

    ClearBackground(RAYWHITE);

    if (currentQuestion < 5)
    {
        DrawText(mathQuestions[currentQuestion], 100, 100, 20, DARKGRAY);
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= '0' && key <= '9' || key == '.' || key == '-')
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
        DrawText("Math Results:", 100, 100, 20, DARKGRAY);

        for (int i = 0; i < 5; i++)
        {
            string resultText = "Question " + to_string(i + 1) + ": ";
            if (userAnswers[i] == mathAnswers[i])
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
            inGame = false;
            currentState = GameState::SubjectSelection;
        }
    }
}


const char* historyQuestions[5] = {
    "In which year did World War II end?",
    "Who was the first President of the United States?",
    "Which ancient civilization built the pyramids of Giza?",
    "What year did Christopher Columbus reach the Americas?",
    "Who wrote 'The Communist Manifesto'?"
};

const string historyAnswers[5] = {
    "1945",
    "George Washington",
    "Ancient Egyptians",
    "1492",
    "Karl Marx"
};

void HistoryQuiz()
{
    static int currentQuestion = 0;
    static string userAnswers[] = { "", "", "", "", "" };

    ClearBackground(RAYWHITE);

    if (currentQuestion < 5)
    {
        DrawText(historyQuestions[currentQuestion], 100, 100, 20, DARKGRAY);
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
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
        DrawText("History Results:", 100, 100, 20, DARKGRAY);

        for (int i = 0; i < 5; i++)
        {
            string resultText = "Question " + to_string(i + 1) + ": ";
            if (userAnswers[i] == historyAnswers[i])
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
            inGame = false;
            currentState = GameState::SubjectSelection;
        }
    }
}


int main()
{
    InitWindow(800, 450, "School Test Program");

    while (!exitWindow)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState)
        {
        case GameState::StartMenu:
            StartMenu();
            break;
        case GameState::Settings:
            Settings();
            break;
        case GameState::SubjectSelection:
            SubjectSelection();
            break;
        case GameState::GeographyQuiz:
            GeographyQuiz();
            break;
        case GameState::MathsQuiz:
            MathsQuiz();
            break;
        case GameState::HistoryDisplay:
            HistoryQuiz();
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
