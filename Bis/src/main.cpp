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
        DrawText("to improve your knowledge and you will be graded accordingly.", 100, 130, 20, DARKGRAY);
        DrawText("If you can do our hard test with more than 8 points you will success", 70, 160, 20, DARKGRAY);
        DrawText("GOOD LUCK!!!", 335, 190, 20, RED);

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
        currentState = GameState::SubjectSelection;
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
    "10.In which country would you find the Serengeti National Park?",
    
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
    
};

void GeographyTestEasy()
{
    static int currentQuestion = 0;
    static string userAnswers[30];

    ClearBackground(RAYWHITE);

    if (currentQuestion < 10)
    {
        // Draw the question
        DrawText(geoQuestions[currentQuestion], 100, 100, 20, DARKGRAY);
        // Draw an input box for the user's answer
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        // Draw the user's answer inside the input box
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= 32 && key <= 126)
        {
            // Append the pressed key to the user's answer
            userAnswers[currentQuestion] += key;
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && !userAnswers[currentQuestion].empty())
        {
            // Remove the last character from the user's answer when backspace is pressed
            userAnswers[currentQuestion].pop_back();
        }

        // Draw the "Next" button
        DrawRectangle(100, 200, 100, 40, SKYBLUE);
        DrawText("Next", 120, 210, 20, DARKBLUE);

        // Check if the "Next" button is clicked
        if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Proceed to the next question
            currentQuestion++;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            currentQuestion++;
        }
    }
    else
    {
        // Draw the results
        DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
        DrawText("Press ESC to return", 10, 40, 20, GRAY);

        int points = 0;
        for (int i = 0; i < 10; i++)
        {
            // Draw each question's result
            string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
            string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

            if (userAnswers[i] == geoAnswers[i])
            {
                resultTextCorrect += "Correct";
                points++;
                DrawText(resultTextCorrect.c_str(), 100, 140 + i * 30, 20, GREEN);
            }
            else
            {
                resultTextIncorrect += "Incorrect";
                DrawText(resultTextIncorrect.c_str(), 100, 140 + i * 30, 20, RED);
            }
        }

        // Draw the total points
        DrawText("You have: ", 10, 10, 20, GRAY);
        DrawText(to_string(points).c_str(), 140, 10, 20, GRAY);
        DrawText(" points", 180, 10, 20, GRAY);


        // Check if the ESC key is pressed to return to the main menu
        if (IsKeyDown(KEY_ESCAPE))
        {
            currentQuestion = 0;
            inGame = false;  // Assuming inGame is a global variable
            currentState = GameState::SubjectSelection;  // Assuming currentState is an enum representing the game state
        }
    }
}
const char* geo2Questions[10] = {
    "1.What is the southernmost continent?",
    "2.Which European country is known for its windmills, tulips, and canals?",
    "3.What is the name of the strait that separates Europe from Africa?",
    "4.Which two countries share the longest international border?",
    "5.What is the highest waterfall in the world, and in which country is it located?",
    "6.Which African country is famous for its Maasai Mara National Reserve?",
    "7.What is the name of the world's largest coral reef system?",
    "8.What is the capital of Canada?",
    "9.Which two countries are separated by the Strait of Gibraltar?",
    "10.What is the largest island in the Mediterranean Sea?",

};

const string geo2Answers[10] = {
    "Antarctica",
    "Netherlands",
    "Strait if Gibraltar",
    "Canada and the United States",
    "Angel Falls",
    "Kenya",
    "Great Barrier Reef",
    "Ottawa",
    "Spain and Morocco",
    "Silicy",

};
void GeographyTestMedium()
{
    static int currentQuestion = 0;
    static string userAnswers[30];

    ClearBackground(RAYWHITE);

    if (currentQuestion < 10)
    {
        // Draw the question
        DrawText(geo2Questions[currentQuestion], 100, 100, 20, DARKGRAY);
        // Draw an input box for the user's answer
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        // Draw the user's answer inside the input box
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= 32 && key <= 126)
        {
            // Append the pressed key to the user's answer
            userAnswers[currentQuestion] += key;
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && !userAnswers[currentQuestion].empty())
        {
            // Remove the last character from the user's answer when backspace is pressed
            userAnswers[currentQuestion].pop_back();
        }

        // Draw the "Next" button
        DrawRectangle(100, 200, 100, 40, SKYBLUE);
        DrawText("Next", 120, 210, 20, DARKBLUE);

        // Check if the "Next" button is clicked
        if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Proceed to the next question
            currentQuestion++;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            currentQuestion++;
        }
    }
    else
    {
        // Draw the results
        DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
        DrawText("Press ESC to return", 10, 40, 20, GRAY);

        int points = 0;
        for (int i = 0; i < 10; i++)
        {
            // Draw each question's result
            string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
            string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

            if (userAnswers[i] == geo2Answers[i])
            {
                resultTextCorrect += "Correct";
                points++;
                DrawText(resultTextCorrect.c_str(), 100, 140 + i * 30, 20, GREEN);
            }
            else
            {
                resultTextIncorrect += "Incorrect";
                DrawText(resultTextIncorrect.c_str(), 100, 140 + i * 30, 20, RED);
            }
        }

        // Draw the total points
        DrawText("You have: ", 10, 10, 20, GRAY);
        DrawText(to_string(points).c_str(), 140, 10, 20, GRAY);
        DrawText(" points", 180, 10, 20, GRAY);


        // Check if the ESC key is pressed to return to the main menu
        if (IsKeyDown(KEY_ESCAPE))
        {
            currentQuestion = 0;
            inGame = false;  // Assuming inGame is a global variable
            currentState = GameState::SubjectSelection;  // Assuming currentState is an enum representing the game state
        }
    }
}

const char* geo3Questions[10] = {
    "1.What is the capital of Mongolia?",
    "2.What is the approximate length of the Great Wall of China?",
    "3.In which U.S. state would you find Denali, the highest peak in North America?",
    "4.What is the capital of Bhutan?",
    "5.Which country has the largest number of time zones?",
    "6.What is the name of the sea that lies between Iran and Saudi Arabia?",
    "7.What is the only country in the world that is also an entire continent?",
    "8.Which mountain range separates Europe from Asia?",
    "9.What is the largest country by area in South America?",
    "10.What is the name of the second-highest mountain in the world?",

};

const string geo3Answers[10] = {
    "Ulaanbaatar",
    "21,196 kilometers",
    "Alaska",
    "Thimphu",
    "Russia",
    "Persian Gulf",
    "Australia",
    "Ural Mountains",
    "Brazil",
    "K2",

};

void GeographyTestHard()
{
    static int currentQuestion = 0;
    static string userAnswers[30];

    ClearBackground(RAYWHITE);

    if (currentQuestion < 10)
    {
        // Draw the question
        DrawText(geo3Questions[currentQuestion], 100, 100, 20, DARKGRAY);
        // Draw an input box for the user's answer
        DrawRectangle(100, 130, 200, 30, LIGHTGRAY);
        // Draw the user's answer inside the input box
        DrawText(userAnswers[currentQuestion].c_str(), 110, 135, 20, MAROON);

        char key = GetCharPressed();
        if (key >= 32 && key <= 126)
        {
            // Append the pressed key to the user's answer
            userAnswers[currentQuestion] += key;
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && !userAnswers[currentQuestion].empty())
        {
            // Remove the last character from the user's answer when backspace is pressed
            userAnswers[currentQuestion].pop_back();
        }

        // Draw the "Next" button
        DrawRectangle(100, 200, 100, 40, SKYBLUE);
        DrawText("Next", 120, 210, 20, DARKBLUE);

        // Check if the "Next" button is clicked
        if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Proceed to the next question
            currentQuestion++;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            currentQuestion++;
        }
    }
    else
    {
        // Draw the results
        DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
        DrawText("Press ESC to return", 10, 40, 20, GRAY);

        int points = 0;
        for (int i = 0; i < 10; i++)
        {
            // Draw each question's result
            string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
            string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

            if (userAnswers[i] == geo3Answers[i])
            {
                resultTextCorrect += "Correct";
                points++;
                DrawText(resultTextCorrect.c_str(), 100, 140 + i * 30, 20, GREEN);
            }
            else
            {
                resultTextIncorrect += "Incorrect";
                DrawText(resultTextIncorrect.c_str(), 100, 140 + i * 30, 20, RED);
            }
        }

        // Draw the total points
        DrawText("You have: ", 10, 10, 20, GRAY);
        DrawText(to_string(points).c_str(), 140, 10, 20, GRAY);
        DrawText(" points", 180, 10, 20, GRAY);


        // Check if the ESC key is pressed to return to the main menu
        if (IsKeyDown(KEY_ESCAPE))
        {
            currentQuestion = 0;
            inGame = false;  // Assuming inGame is a global variable
            currentState = GameState::SubjectSelection;  // Assuming currentState is an enum representing the game state
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
        case GameState::GeographyTestEasy:
            GeographyTestEasy();
            break;
        case GameState::GeographyTestMedium:
            GeographyTestMedium();
            break;
        case GameState::GeographyTestHard:
            GeographyTestHard();
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
