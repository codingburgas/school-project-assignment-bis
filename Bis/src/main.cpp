#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "raylib.h"

using namespace std;

enum class GameState {
    StartMenu,
    Settings,
    SubjectSelection,
    GeographyQuiz,
    GeographyTestEasy,
    GeographyTestMedium,
    GeographyTestHard,
    MathsQuiz,
    HistoryDisplay
};

GameState currentState = GameState::StartMenu;

static int longText1 = 0;
bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;
bool musicStarted = false;  // Track if music has started

void Settings() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Settings");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Settings", 350, 20, 20, DARKGRAY);
        DrawLine(220, 50, 590, 50, DARKGRAY);
        DrawText("Hi here you can take tests on different subjects", 120, 100, 20, DARKGRAY);
        DrawText("to improve your knowledge and you will be graded accordingly", 100, 120, 20, DARKGRAY);

        EndDrawing();

        if (IsKeyDown(KEY_ESCAPE)) {
            inGame = false;
            currentState = GameState::StartMenu;
            break;
        }
    }

    DrawText("Press ESC to return", 100, 340, 20, DARKGRAY);

    if (IsKeyDown(KEY_ESCAPE)) {
        inGame = false;
        currentState = GameState::StartMenu;
    }
}

void StartMenu() {
    ClearBackground(RAYWHITE);

    DrawText("School Test Program", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Start" : "Start", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Settings" : "Settings", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> Exit" : "Exit", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption > 0) {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2) {
        selectedOption++;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            currentState = GameState::SubjectSelection;
        }
        else if (selectedOption == 1) {
            currentState = GameState::Settings;
        }
        else if (selectedOption == 2) {
            exitWindow = true;
        }
    }
}

void SubjectSelection() {
    ClearBackground(RAYWHITE);

    DrawText("Choose subject:", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Geography" : "Geography", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Maths" : "Maths", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> History" : "History", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption > 0) {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2) {
        selectedOption++;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            currentState = GameState::GeographyQuiz;
            inGame = true;
        }
        else if (selectedOption == 1) {
            currentState = GameState::MathsQuiz;
            inGame = true;
        }
        else if (selectedOption == 2) {
            currentState = GameState::HistoryDisplay;
            inGame = true;
        }
    }

    if (IsKeyDown(KEY_ESCAPE)) {
        inGame = false;
        currentState = GameState::StartMenu;
    }
}
void GeographyQuiz()
{
    ClearBackground(RAYWHITE);

    DrawText("Choose level:", 100, 100, 40, GRAY);
    DrawText(selectedOption == 0 ? "> Easy" : "Easy", 100, 200, 20, DARKGRAY);
    DrawText(selectedOption == 1 ? "> Medium" : "Medium", 100, 240, 20, DARKGRAY);
    DrawText(selectedOption == 2 ? "> Hard" : "Hard", 100, 280, 20, DARKGRAY);

    if (IsKeyPressed(KEY_UP) && selectedOption > 0) {
        selectedOption--;
    }

    if (IsKeyPressed(KEY_DOWN) && selectedOption < 2) {
        selectedOption++;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            currentState = GameState::GeographyTestEasy;
            inGame = true;
        }
        else if (selectedOption == 1) {
            currentState = GameState::GeographyTestMedium;
            inGame = true;
        }
        else if (selectedOption == 2) {
            currentState = GameState::GeographyTestHard;
            inGame = true;
        }
    }

    if (IsKeyDown(KEY_ESCAPE)) {
        inGame = false;
        currentState = GameState::StartMenu;
    }
}


const char* geoQuestions[30] = {
    "1.What is the capital of France?",
    "2.What is the largest desert in the world?",
    "3.Where is the Great Barrier Reef located?",
    "4.Which country is famous for the Amazon Rainforest?",
    "5.What is the tallest mountain in the world?",
    "6.What is the capital of Japan?",
    "7.Where is the Amazon River located?",
    "8.Which continent is the Sahara Desert in?",
    "9.What is the longest river in the world?",
    "10.In which country would you find the Seregeti National Park?",
    "11.What is the smallest country in the world by land area?",
    "12.Where is the dead sea located?",
    "13.What is the largest island in the world?",
    "14.Which country is known as the Land of the Rising Sun?",
    "15.Where is the Great Wall of China located?",
    "16.What is the highest waterfall in the world?",
    "17.In which country would you find the Andes Mountains?",
    "18.Which ocean is the largest by surface area?",
    "19.What is the capital of Australia?",
    "20.Where is the Grand Canyon located?"

};

const string geoAnswers[30] = {
    "Paris",
    "Sahara",
    "Australia",
    "Brazil",
    "Everest",
    "Tokyo",
    "South America",
    "Africa",
    "Nile River",
    "Tanzania",
    "Vatican City",
    "In the Middle East",
    "Greenland",
    "Japan",
    "China",
    "Angel Falls",
    "South America",
    "Pacific Ocean",
    "Canberra",
    "United States"
};

void GeographyTestEasy()
{
    static int currentQuestion = 0;
    static string userAnswers[30];

    ClearBackground(RAYWHITE);

    if (currentQuestion < 20)
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

        int points = 0;
        for (int i = 0; i < 20; i++)
        {
            string resultText = "Question " + to_string(i + 1) + ": ";
            if (userAnswers[i] == geoAnswers[i])
            {
                resultText += "Correct";
                points++;
            }
            else
            {
                resultText += "Incorrect";
            }
            DrawText(resultText.c_str(), 100, 140 + i * 30, 20, DARKGRAY);
            std::stringstream ss;
            ss << points;
            std::string pointsStr = ss.str();

            // Draw text on the screen without using FormatText
            DrawText("You have: ", 10, 10, 20, BLACK);
            DrawText(pointsStr.c_str(), 140, 10, 20, BLACK); // Draw the string converted from integer
            DrawText(" points", 180, 10, 20, BLACK);
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

int main() {
    InitWindow(800, 450, "School Test Program");

    InitAudioDevice();

    Sound music = LoadSound("music.ogg");  
    Image image = LoadImage("bg.png");
    Texture2D texture = LoadTextureFromImage(image); 
    UnloadImage(image);

    while (!exitWindow) {
        if (!musicStarted && IsKeyPressed(KEY_ENTER)) {
            PlaySound(music);  
            musicStarted = true;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texture, 800 / 2 - texture.width / 2, 450 / 2 - texture.height / 2, WHITE);

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
    UnloadSound(music);     
    CloseAudioDevice();     
    CloseWindow();

}
