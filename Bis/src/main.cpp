﻿#include <iostream>
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
	MathsTestEasy,
	MathsTestMedium,
	MathsTestHard,

	HistoryDisplay,
	HistoryTestEasy,
	HistoryTestMedium,
	HistoryTestHard,
};

GameState currentState = GameState::StartMenu;

static int longText1 = 0;
bool exitWindow = false;
int selectedOption = 0;
bool inGame = false;
bool musicStarted = false;

void Settings() {

	std::string op = std::string("start ").append("https://github.com/codingburgas/school-project-assignment-bis");
	system(op.c_str());
	currentState = GameState::StartMenu;

}

void StartMenu() {
	ClearBackground(RAYWHITE);

	DrawText("School Test Program", 100, 100, 40, BLACK);
	DrawText(selectedOption == 0 ? "> Start" : "Start", 100, 200, 20, DARKGRAY);
	DrawText(selectedOption == 1 ? "> Our repository" : "Our repository", 100, 240, 20, DARKGRAY);
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

	DrawText("Choose subject:", 100, 100, 40, BLACK);
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

	DrawText("Choose level:", 100, 100, 40, BLACK);
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
	"4.Where is the Amazon Rainforest?",
	"5.What is the tallest mountain in the world?",
	"6.What is the capital of Japan?",
	"7.Where is the Amazon River located?",
	"8.Which continent is the Sahara Desert in?",
	"9.What is the longest river in the world?",
	"10.Where is Serengeti National Park?",

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

const char* geo2Questions[10] = {
	"1.What is the southernmost continent?",
	"2.Which country is known for its windmills, tulips, and canals?",
	"3.What is the name of the strait that separates Europe from Africa?",
	"4.Which two countries share the longest international border?",
	"5.Where is the highest waterfall in the world?",
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

		DrawText(geo2Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

const char* geo3Questions[10] = {
	"1.What is the capital of Mongolia?",
	"2.What is the approximate length of the Great Wall of China?",
	"3.In which U.S. state is the highest peak in North America?",
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

		DrawText(geo3Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Geography Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);

		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

void MathsQuiz()
{
	ClearBackground(RAYWHITE);

	DrawText("Choose level:", 100, 100, 40, BLACK);
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
			currentState = GameState::MathsTestEasy;
			inGame = true;
		}
		else if (selectedOption == 1) {
			currentState = GameState::MathsTestMedium;
			inGame = true;
		}
		else if (selectedOption == 2) {
			currentState = GameState::MathsTestHard;
			inGame = true;
		}
	}

	if (IsKeyDown(KEY_ESCAPE)) {
		inGame = false;
		currentState = GameState::SubjectSelection;
	}
}

const char* MathsQuestions[10] = {
	"1.What is 15 + 27?",
	"2.What is 6 * 12?",
	"3.What is 112 divided by 4?",
	"4.What is the value of π (pi) to two decimal places?",
	"5.What is the square root of 25?",
	"6.How much is 30% of 500?",
	"7.What is the next number in the sequence: 2, 4, 6, 8, ...?",
	"8.What is the sum of the angles in a triangle?",
	"9.What is the area of a square with a side length of 6 units?",
	"10.What is the perimeter of a rectangle with dimensions 4 units by 8 units?",

};

const string MathsAnswers[10] = {
	"42",
	"72",
	"28",
	"3.14",
	"5",
	"150",
	"10",
	"180 degrees",
	"36",
	"24",

};
void MathsTestEasy()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(MathsQuestions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Maths Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == MathsAnswers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

const char* Maths2Questions[10] = {
	"1.Solve for x: 2x + 5 = 15.",
	"2.What is the greatest common divisor (GCD) of 24 and 36?",
	"3.What is the volume of a cube with side length 3 units?",
	"4.What is the slope of the line passing through the points (2, 4) and (6, 10)?",
	"5.What is the value of 3 on square + 4 on square?",
	"6.If a = 3 and b = 5, what is the value of a on square + b on square?",
	"7.What is the product of the first 5 prime numbers?",
	"8.Solve for x: 3x - 7 = 11.",
	"9.What is the circumference of a circle with a diameter of 10 units?",
	"10.What is the area of a triangle with base 8 units and height 6 units?",

};

const string Maths2Answers[10] = {
	"5",
	"12",
	"27",
	"1",
	"25",
	"34",
	"2310",
	"6",
	"31.42",
	"24",

};

void MathsTestMedium()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(Maths2Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Maths Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == Maths2Answers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}


const char* Maths3Questions[10] = {
	"1.What is the value of 2 on fourth square ÷ (3 × 4) + 5?",
	"2.What is the decimal of the fraction 3/7 to three decimal places?",
	"3.Solve for x: log₄(x) = 2.",
	"4.What is (2 + root(3))on square - (2 - √3)on square?",
	"5.How many degrees are in the interior angles of a hexagon?",
	"6.What is the value of the expression (sin 30) / (cos 30)?",
	"7.Solve for x: 2x3 - 5x2 + 3x - 7 = 0.",
	"8.The sum of the first 10 numbers here: 3, 7, 11, 15, ...? are?",
	"9.What is the value of i on square, where i is the imaginary unit (root(-1))?",
	"10.What is the value of the expression root(16 + 9) - root(16 - 9)?",

};

const string Maths3Answers[10] = {
	"3",
	"0.429",
	"16",
	"8",
	"720",
	"1",
	"2",
	"280",
	"-1",
	"5",

};
void MathsTestHard()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(Maths3Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("Maths Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == Maths3Answers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}


void HistoryDisplay()
{

	ClearBackground(RAYWHITE);

	DrawText("Choose level:", 100, 100, 40, BLACK);
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
			currentState = GameState::HistoryTestEasy;
			inGame = true;
		}
		else if (selectedOption == 1) {
			currentState = GameState::HistoryTestMedium;
			inGame = true;
		}
		else if (selectedOption == 2) {
			currentState = GameState::HistoryTestHard;
			inGame = true;
		}
	}

	if (IsKeyDown(KEY_ESCAPE)) {
		inGame = false;
		currentState = GameState::SubjectSelection;
	}
}

const char* HistoryQuestions[10] = {
	"1.Who was the first President of the United States?",
	"2.In what year did World War II end?",
	"3.What ancient civilization built the Great Pyramids of Giza?",
	"4.Who was the famous queen of ancient Egypt known for her beauty?",
	"5.What event marked the beginning of the Renaissance in Europe?",
	"6.Who is credited with discovering America in 1492?",
	"7.What was the name of the ship that carried the Pilgrims to America in 1620?",
	"8.Who was the first man to set foot on the moon?",
	"9.Who was the leader of the Soviet Union during the Cuban Missile Crisis?",
	"10.What year did the Berlin Wall fall, marking the end of the Cold War?",

};

const string HistoryAnswers[10] = {
	"George Washington",
	"1945",
	"Ancient Egyptians",
	"Cleopatra",
	"The fall of Constantinople (1453)",
	"Christopher Columbus",
	"Mayflower",
	"Neil Armstrong",
	"Nikita Khrushchov",
	"1989",

};

void HistoryTestEasy()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(HistoryQuestions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("HIstory Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == HistoryAnswers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

const char* History2Questions[10] = {
	"1.Who is the first permanent English settlement in North America?",
	"2.Who was the longest-reigning monarch in British history?",
	"3.What was the significance of the Battle of Waterloo in 1815?",
	"4.Who was the founder of the Mongol Empire in the 13th century?",
	"5.What was the Treaty of Versailles, and what were its consequences?",
	"6.Who was the first female Prime Minister of the United Kingdom?",
	"7.What was the ancient trade route that connected Europe to China?",
	"8.What event sparked World War I?",
	"9.Who was the Roman general responsible for the conquest of Gaul?",
	"10.What was the significance of the Louisiana Purchase in 1803?",

};

const string History2Answers[10] = {
	"Jamestown",
	"Queen Victoria",
	"The final defeat of Napoleon Bonaparte",
	"Genghis Khan",
	"It ended World War I and imposed harsh penalties on Germany, leading to economic instability and contributing to the rise of Nazi Germany",
	"Margaret Thatcher",
	"Silk Road",
	"The assassination of Archduke Franz Ferdinand of Austria-Hungary",
	"Julius Caesar",
	"It doubled the size of the United States and opened up vast western territories for expansion",

};


void HistoryTestMedium()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(History2Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("HIstory Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == History2Answers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

const char* History3Questions[10] = {
	"1.What was the primary cause of the Peloponnesian War?",
	"2.Who was the architect of the Terror during the French Revolution?",
	"3.What event triggered the beginning of World War I?",
	"4.Who was the last emperor of Russia before the Bolshevik Revolution?",
	"5.What was the significance of the Battle of Stalingrad during World War II?",
	"6.Who was the first female ruler of Russia?",
	"7.What was the main cause of the Irish Potato Famine in the 19th century?",
	"8.Who wrote 'The Communist Manifesto' with Karl Marx?",
	"9.What was the name of the treaty that ended the Korean War in 1953?",
	"10.Who was the primary architect of the unification of Italy?",

};

const string History3Answers[10] = {
	"Athenian imperialism",
	"Maximilien Robespierre",
	"Assassination of Archduke Franz Ferdinand",
	"Nicholas II",
	"Turning point, Soviet victory",
	"Catherine the Great",
	"Potato blight",
	"Friedrich Engels",
	"Armistice Agreement",
	"Giuseppe Garibaldi",

};


void HistoryTestHard()
{
	static int currentQuestion = 0;
	static string userAnswers[30];

	ClearBackground(RAYWHITE);

	if (currentQuestion < 10)
	{

		DrawText(History3Questions[currentQuestion], 100, 100, 20, DARKGRAY);

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

		DrawRectangle(100, 200, 100, 40, SKYBLUE);
		DrawText("Next", 120, 210, 20, DARKBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), { 100, 200, 100, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			currentQuestion++;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			currentQuestion++;
		}
	}
	else
	{

		DrawText("HIstory Results:", 100, 100, 20, DARKBLUE);
		DrawText("Press ESC to return", 400, 40, 20, BLACK);

		int points = 0;
		for (int i = 0; i < 10; i++)
		{

			string resultTextCorrect = "Question " + to_string(i + 1) + ": ";
			string resultTextIncorrect = "Question " + to_string(i + 1) + ": ";

			if (userAnswers[i] == History3Answers[i])
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

		DrawText("You have: ", 30, 30, 20, BLACK);
		DrawText(to_string(points).c_str(), 140, 30, 20, BLACK);
		DrawText(" points", 170, 30, 20, BLACK);
		if (points >= 9)
			DrawText("Your mark is: 6", 30, 500, 20, BLACK);

		if (points == 8)
			DrawText("Your mark is: 5", 30, 500, 20, BLACK);

		if (points == 7)
			DrawText("Your mark is: 4", 30, 500, 20, BLACK);

		if (points == 6 or points == 5)
			DrawText("Your mark is: 3", 30, 500, 20, BLACK);

		if (points < 5)
			DrawText("Your mark is: 2", 30, 500, 20, BLACK);

		if (IsKeyDown(KEY_ESCAPE))
		{
			currentQuestion = 0;
			inGame = false;
			currentState = GameState::SubjectSelection;
		}
	}
}

int main() {
	InitWindow(900, 550, "School Test Program");

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

		DrawTexture(texture, 900 / 2 - texture.width / 2, 550 / 2 - texture.height / 2, WHITE);

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
		case GameState::MathsTestEasy:
			MathsTestEasy();
			break;
		case GameState::MathsTestMedium:
			MathsTestMedium();
			break;
		case GameState::MathsTestHard:
			MathsTestHard();
			break;
		case GameState::HistoryDisplay:
			HistoryDisplay();
			break;
		case GameState::HistoryTestEasy:
			HistoryTestEasy();
			break;
		case GameState::HistoryTestMedium:
			HistoryTestMedium();
			break;
		case GameState::HistoryTestHard:
			HistoryTestHard();
			break;
		}

		EndDrawing();
	}
	UnloadSound(music);
	CloseAudioDevice();
	CloseWindow();

}