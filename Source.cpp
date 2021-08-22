

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char board[9] = { '1','2','3','4','5','6','7','8','9' };
char player1 = 'X';
char player2 = 'O';
int n; // Counter variable

// Function declarations
void displayBoard();
void displayScorePlayer1(vector<string> score);
void displayScorePlayer2(vector<string> score);
void playerInput();
void computerDefendMove();
void computerRandomMove();
char win();
void displayWinnerPlayer1();
void displayWinnerPlayer2();
void displayWinnerComputer();
void displayDraw();
void resetBoard();
void TogglePlayer(int choice);
void gameHeading();
int gameMenu();
void gameIntro();
void onePlayer();
void twoPlayer();
void writeOutputFile(string result);
void readOutputFile(int choice);

// This function controls all the logic for how
// the game is meant to run
void main()
{
	int choice = 3;		// Sets the choice value as 3
						// as that equals the quit game value
	do
	{		
		choice = gameMenu();
		if (choice == 1)
		{
			system("cls");
			onePlayer();
			resetBoard();
		}
		else if (choice == 2)
		{
			system("cls");
			twoPlayer();
			resetBoard();
		}
	} while (choice != 3);
	cout << endl;
	system("pause");
}

// Function to write which player wins to an output file
void writeOutputFile(string result)
{
	fstream resultFile;
	resultFile.open("Scores.txt", ios::app);
	if (resultFile.is_open())
	{
		resultFile << result << endl;
	}
	resultFile.close();
}

// Function to read the ouput file and display the score
void readOutputFile(int choice)
{
	vector<string> scorePlayer1;
	vector<string> scorePlayer2;
	vector<string> scoreComputer;
	fstream scoreFile;
	scoreFile.open("Scores.txt", ios::in);
	if (scoreFile.is_open())
	{
		string line;
		while (getline(scoreFile, line))
		{
			scoreFile >> line;
			if (line == "X")
			{
				scorePlayer1.push_back(line);
			}
			else if (line == "O")
			{
				scorePlayer2.push_back(line);
			}
			else if (line == "C")
			{
				scoreComputer.push_back(line);
			}
		}
		scoreFile.close();
	}

	// This checks the games state and mode and displays 
	// the correct score accordingly
	displayScorePlayer1(scorePlayer1);
	if (choice == 1)
	{
		displayScorePlayer2(scoreComputer);
	}
	else
	{
		displayScorePlayer2(scorePlayer2);
	}
	cout << endl;
	system("pause");
	system("cls");
}

// Game loop function for game mode 1
// Once game ends, the loop is broken
// and you return to the main menu
void onePlayer()
{
	int choice = 1;		// Sets choice as 1, as this is game mode 1
	string result = " "; // Empty string variable to be modified
	n = 0;
	displayBoard();
	while (true)
	{
		n++;	// Counter variable
		playerInput();
		computerDefendMove();
		displayBoard();
		if (win() == 'X')
		{
			result = "X";	// The winner is X, the result will get stored and written
			writeOutputFile(result);
			displayWinnerPlayer1();
			system("cls");
			readOutputFile(1);	// Displays the player's score
			break;
		}
		else if (win() == 'O')
		{
			result = "C";
			writeOutputFile(result);
			displayWinnerComputer();
			system("cls");
			readOutputFile(1);
			break;
		}
		else if (win() == '/' && n >= 9)
		{
			displayDraw();
			system("cls");
			readOutputFile(1);
			break;
		}
		TogglePlayer(choice);
	}
}

// Game loop function for game mode 2
// Once game ends, the loop is broken
// and you return to the main menu
void twoPlayer()
{
	int choice = 2;		// Sets choice as 2, as this is game mode 2
	string result = " ";	// Empty string variable to be modified
	n = 0;
	displayBoard();
	while (true)
	{
		n++;
		playerInput();
		displayBoard();
		if (win() == 'X')
		{
			result = "X";
			writeOutputFile(result);
			displayWinnerPlayer1();
			system("cls");
			readOutputFile(2);
			break;
		}
		else if (win() == 'O')
		{
			result = "O";
			writeOutputFile(result);
			displayWinnerPlayer2();
			system("cls");
			readOutputFile(2);
			break;
		}
		else if (win() == '/' && n == 9)
		{
			displayDraw();
			system("cls");
			readOutputFile(2);
			break;
		}
		TogglePlayer(choice);
	}
}

// Displays the layout of the board
void displayBoard()
{
	system("cls");
	cout << "	" << "	|	" << "	|	" << endl;
	cout << "	" << board[0] << "	|	" << board[1] << "	|	" << board[2] << endl;
	cout << "	" << "	|	" << "	|	" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "	" << "	|	" << "	|	" << endl;
	cout << "	" << board[3] << "	|	" << board[4] << "	|	" << board[5] << endl;
	cout << "	" << "	|	" << "	|	" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "	" << "	|	" << "	|	" << endl;
	cout << "	" << board[6] << "	|	" << board[7] << "	|	" << board[8] << endl;
	cout << "	" << "	|	" << "	|	" << endl;

	cout << endl;
}

// A function for recieving input from the player
void playerInput()
{
	int a;
	cout << "It's " << player1 << "'s turn. " << endl;
	cout << "Press the number of the field: ";
	cin >> a;

	while (board[a - 1] == player1 || board[a - 1] == player2) {
		cout << "Field is already in use, try again!" << endl;
		cout << "Press the number of the field: ";
		cin >> a;
	}

	board[a - 1] = player1;
}

// A simplified defend function that checks
// for every possible winnning combination 
// so the computer can block the player
// from winning
void computerDefendMove()
{
	// Rows
	// Row 1 - Combination 1
	if (board[0] == 'X' && board[1] == 'X' && board[2] == '3')
	{
		if (board[0] != 'O' && board[1] != 'O' && board[2] == '3')
		{
			board[2] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 1 - Combination 2
	else if (board[0] == 'X' && board[1] == '2' && board[2] == 'X')
	{
		if (board[0] != 'O' && board[1] == '2' && board[2] != 'O')
		{
			board[1] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 1 - Combination 3
	else if (board[0] == '1' && board[1] == 'X' && board[2] == 'X')
	{
		if (board[0] == '1' && board[1] != 'O' && board[2] != 'O')
		{
			board[0] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 2 - Combination 1
	else if (board[3] == 'X' && board[4] == 'X' && board[5] == '6')
	{
		if (board[3] != 'O' && board[4] != 'O' && board[5] == '6')
		{
			board[5] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 2 - Combination 2
	else if (board[3] == 'X' && board[4] == '5' && board[5] == 'X')
	{
		if (board[3] != 'O' && board[4] == '5' && board[5] != 'O')
		{
			board[4] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 2 - Combination 3
	else if (board[3] == '4' && board[4] == 'X' && board[5] == 'X')
	{
		if (board[3] == '4' && board[4] != 'O' && board[5] != 'O')
		{
			board[3] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 3 - Combination 1
	else if (board[6] == 'X' && board[7] == 'X' && board[8] == '9')
	{
		if (board[6] != 'O' && board[7] != 'O' && board[8] == '9')
		{
			board[8] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 3 - Combination 2
	else if (board[6] == 'X' && board[7] == '8' && board[8] == 'X')
	{
		if (board[6] != 'O' && board[7] == '8' && board[8] != 'O')
		{
			board[7] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Row 3 - Combination 3
	else if (board[6] == '7' && board[7] == 'X' && board[8] == 'X')
	{
		if (board[6] == '7' && board[7] != 'O' && board[8] != 'O')
		{
			board[6] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}

	// Columns
	// Column 1 - Combination 1
	else if (board[0] == 'X' && board[3] == 'X' && board[6] == '7')
	{
		if (board[0] != 'O' && board[3] != 'O' && board[6] == '7')
		{
			board[6] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 1 - Combination 2
	else if (board[0] == 'X' && board[3] == '4' && board[6] == 'X')
	{
		if (board[0] != 'O' && board[3] == '4' && board[6] != 'O')
		{
			board[3] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 1 - Combination 3
	else if (board[0] == '1' && board[3] == 'X' && board[6] == 'X')
	{
		if (board[0] == '1' && board[3] != 'O' && board[6] != 'O')
		{
			board[0] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 2 - Combination 1
	else if (board[1] == 'X' && board[4] == 'X' && board[7] == '8')
	{
		if (board[1] != 'O' && board[4] != 'O' && board[7] == '8')
		{
			board[7] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 2 - Combination 2
	else if (board[1] == 'X' && board[4] == '5' && board[7] == 'X')
	{
		if (board[1] != 'O' && board[4] == '5' && board[7] != 'O')
		{
			board[4] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 2 - Combination 3
	else if (board[1] == '2' && board[4] == 'X' && board[7] == 'X')
	{
		if (board[1] == '2' && board[4] != 'O' && board[7] != 'O')
		{
			board[2] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 3 - Combination 1
	else if (board[2] == 'X' && board[5] == 'X' && board[8] == '9')
	{
		if (board[2] != 'O' && board[5] != 'O' && board[8] == '9')
		{
			board[8] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 3 - Combination 2
	else if (board[2] == 'X' && board[5] == '6' && board[8] == 'X')
	{
		if (board[2] != 'O' && board[5] == '6' && board[8] != 'O')
		{
			board[5] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Column 3 - Combination 3
	else if (board[2] == '3' && board[5] == 'X' && board[8] == 'X')
	{
		if (board[2] == '3' && board[5] != 'O' && board[8] != 'O')
		{
			board[2] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}

	// Diagonals
	// Diagonal 1 - Combination 1
	else if (board[0] == 'X' && board[4] == 'X' && board[8] == '9')
	{
		if (board[0] != 'O' && board[4] != 'O' && board[8] == '9')
		{
			board[8] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Diagonal 1 - Combination 2
	else if (board[0] == 'X' && board[4] == '5' && board[8] == 'X')
	{
		if (board[0] != 'O' && board[4] == '5' && board[8] != 'O')
		{
			board[4] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Diagonal 1 - Combination 3
	else if (board[0] == '1' && board[4] == 'X' && board[8] == 'X')
	{
		if (board[0] == '1' && board[4] != 'O' && board[8] != 'O')
		{
			board[0] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Diagonal 2 - Combination 1
	else if (board[2] == 'X' && board[4] == 'X' && board[6] == '7')
	{
		if (board[2] != 'O' && board[4] != 'O' && board[6] == '7')
		{
			board[6] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Diagonal 2 - Combination 2
	else if (board[2] == 'X' && board[4] == '5' && board[6] == 'X')
	{
		if (board[2] != 'O' && board[4] == '5' && board[6] != 'O')
		{
			board[4] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	// Diagonal 2 - Combination 3
	else if (board[2] == '1' && board[4] == 'X' && board[6] == 'X')
	{
		if (board[2] == '1' && board[4] != 'O' && board[6] != 'O')
		{
			board[2] = player2;
		}
		else
		{
			computerRandomMove();
		}
	}
	else
	{
		computerRandomMove();
	}
}

// A function for the computer to make 
// a random move when defending is not
// an option
void computerRandomMove()
{
	srand(time(NULL));
	int boardPos = rand() % 9 + 1;

	if (boardPos == 1)
	{
		if (board[0] == '1')
		{
			board[0] = player2;
		}
	}
	else if (boardPos == 2)
	{
		if (board[1] == '2')
		{
			board[1] = player2;
		}
	}
	else if (boardPos == 3)
	{
		if (board[2] == '3')
		{
			board[2] = player2;
		}
	}
	else if (boardPos == 4)
	{
		if (board[3] == '4')
		{
			board[3] = player2;
		}
	}
	else if (boardPos == 5)
	{
		if (board[4] == '5')
		{
			board[4] = player2;
		}
	}
	else if (boardPos == 6)
	{
		if (board[5] == '6')
		{
			board[5] = player2;
		}
	}
	else if (boardPos == 7)
	{
		if (board[6] == '7')
		{
			board[6] = player2;
		}
	}
	else if (boardPos == 8)
	{
		if (board[7] == '8')
		{
			board[7] = player2;
		}
	}
	else if (boardPos == 9)
	{
		if (board[8] == '9')
		{
			board[8] = player2;
		}
	}
}

// Function for checking all the winning states
char win()
{
	// First Player
	//R ows
	if (board[0] == 'X' && board[1] == 'X' && board[2] == 'X')
		return 'X';
	if (board[3] == 'X' && board[4] == 'X' && board[5] == 'X')
		return 'X';
	if (board[6] == 'X' && board[7] == 'X' && board[8] == 'X')
		return 'X';
	// Columns
	if (board[0] == 'X' && board[3] == 'X' && board[6] == 'X')
		return 'X';
	if (board[1] == 'X' && board[4] == 'X' && board[7] == 'X')
		return 'X';
	if (board[2] == 'X' && board[5] == 'X' && board[8] == 'X')
		return 'X';
	// Diagonals
	if (board[0] == 'X' && board[4] == 'X' && board[8] == 'X')
		return 'X';
	if (board[2] == 'X' && board[4] == 'X' && board[6] == 'X')
		return 'X';

	// Second Player
	// Rows
	if (board[0] == 'O' && board[1] == 'O' && board[2] == 'O')
		return 'O';
	if (board[3] == 'O' && board[4] == 'O' && board[5] == 'O')
		return 'O';
	if (board[6] == 'O' && board[7] == 'O' && board[8] == 'O')
		return 'O';
	// Columns
	if (board[0] == 'O' && board[3] == 'O' && board[6] == 'O')
		return 'O';
	if (board[1] == 'O' && board[4] == 'O' && board[7] == 'O')
		return 'O';
	if (board[2] == 'O' && board[5] == 'O' && board[8] == 'O')
		return 'O';
	// Diagonals
	if (board[0] == 'O' && board[4] == 'O' && board[8] == 'O')
		return 'O';
	if (board[2] == 'O' && board[4] == 'O' && board[6] == 'O')
		return 'O';

	return '/'; // Returns / when there's a draw
}

// Function for resetting the board
void resetBoard()
{
	board[0] = '1';
	board[1] = '2';
	board[2] = '3';
	board[3] = '4';
	board[4] = '5';
	board[5] = '6';
	board[6] = '7';
	board[7] = '8';
	board[8] = '9';
}

// A function for switching between players
// within the game
void TogglePlayer(int choice)
{	
	if (choice == 1)
	{
		if (player1 == 'X')
			player2 = 'O';
		else
			player1 = 'X';
	}
	if (choice == 2)
	{
		if (player1 == 'X')
			player1 = 'O';
		else
			player1 = 'X';
	}
}

void displayScorePlayer1(vector<string> score)
{
	cout << "\t--------------------------------" << endl;
	cout << "\t|     " << "Player 1 High Score: " << score.size() << "   |" << endl;
	cout << "\t--------------------------------" << endl;

	cout << endl;
}

void displayScorePlayer2(vector<string> score)
{
	cout << "\t--------------------------------" << endl;
	cout << "\t|     " << "Player 2 High Score: " << score.size() << "   |" << endl;
	cout << "\t--------------------------------" << endl;

	cout << endl;
}

void displayWinnerPlayer1()
{
	cout << "\t------------------------" << endl;
	cout << "\t|     " << "Player 1 Wins" << "    |" << endl;
	cout << "\t------------------------" << endl;

	cout << endl;
	system("pause");
	cout << endl;
}

void displayWinnerPlayer2()
{
	cout << "\t------------------------" << endl;
	cout << "\t|     " << "Player 2 Wins" << "    |" << endl;
	cout << "\t------------------------" << endl;

	cout << endl;
	system("pause");
	cout << endl;
}

void displayWinnerComputer()
{
	cout << "\t------------------------" << endl;
	cout << "\t|     " << "Computer Wins" << "    |" << endl;
	cout << "\t------------------------" << endl;

	cout << endl;
	system("pause");
	cout << endl;
}

void displayDraw()
{
	cout << "\t------------------" << endl;
	cout << "\t|      " << " Draw" << "     |" << endl;
	cout << "\t------------------" << endl;

	cout << endl;
	system("pause");
	cout << endl;
}

void gameHeading()
{
	cout << "\t-------------------------" << endl;
	cout << "\t|     " << " TIC TAC TOE " << "     |" << endl;
	cout << "\t-------------------------" << endl;

	cout << endl;
}

// This function displays and controls
// the game menu
int gameMenu()
{
	string error = "";	// Sets an empty variable
	bool onePlayer = false;
	bool twoPlayer = false;
	int choice;
	do
	{
		gameHeading();
		cout << "\t\t  Menu" << endl;
		cout << endl;
		cout << "       Enter the number for which game mode" << endl;
		cout << "		you want to play" << endl;
		cout << endl;
		cout << "\t" << "1. " << " 1 Player (Player 1 VS Computer)" << endl;
		cout << "\t" << "2. " << " 2 Player (Player 1 VS Player 2)" << endl;
		cout << "\t" << "3. " << " 3 Quit Game" << endl;
		cout << endl;

		if (error != "")	// Error checking logic so a user
							// can't input a value outside the 
							// game menu range
		{
			cout << "\t" << error;
			error = "";
		}
		cout << "\t Enter choice: ";
		cin >> choice;
		if (choice < 1 || choice > 3)
		{
			error = " --> WRONG: Please enter valid number\n";
			system("cls");
		}
	} while (error != "");
	return choice;
}

void gameIntro()
{
	gameMenu();
}
