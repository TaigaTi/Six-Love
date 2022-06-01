#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include <cmath>

using namespace std;

// Class storing player information
class player
{
	private:

	public: 
		string name = "name";
		string level= "rookie";
		int digitsToRemove = 0;
		int hints = 0;
		int totalPoints = 20;
};


int originalBoard[6][6];
int progressBoard[6][6];

// Function to randomly generate board
void generateBoard()
{
	int row = 0;
	int col = 0; 
	int rowCheck = 0;
	int colCheck = 0;
	int varToInsert = 0;
	bool canPlace;

	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			do
			{
				varToInsert = rand() % 6 + 1;
				canPlace = true;

				if (row != 0)
				{
					for (rowCheck = row - 1; rowCheck >= 0; rowCheck--)
					{
						if (originalBoard[rowCheck][col] == varToInsert)
							canPlace = false;
					}
				}

				if (col != 0)
				{
					for (colCheck = col - 1; colCheck >= 0; colCheck--)
					{
						if (originalBoard[row][colCheck] == varToInsert)
							canPlace = false;
					}
				}
			} while (canPlace == false);

			originalBoard[row][col] = varToInsert;
			progressBoard[row][col] = varToInsert;
		}
	}
}

// Function to print in progress board
void printBoard()
{
	int row;
	int col;

	cout << endl;

	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			if (progressBoard[row][col] != 0)
			{
				if (col < 1)
					cout << " ";

				cout << progressBoard[row][col];

				if (col < 5)
					cout << " |  ";
			}
			else if (progressBoard[row][col] == 0)
			{
				if (col < 1)
					cout << " ";

				cout << " ";

				if (col < 5)
					cout << " |  ";
			}
		}

		if (row < 5)
			cout << endl << "----------------------------" << endl;
	}
	
	cout << endl;
}

// Function to print completed board
void printBoard(int id)
{

	int row;
	int col;

	cout << endl;

	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			if (originalBoard[row][col] != 0)
			{
				if (col < 1)
					cout << " ";

				cout << originalBoard[row][col];

				if (col < 5)
					cout << " |  ";
			}
			else if (originalBoard[row][col] == 0)
			{
				if (col < 1)
					cout << " ";

				cout << " ";

				if (col < 5)
					cout << " |  ";
			}
		}

		if (row < 5)
			cout << endl << "----------------------------" << endl;
	}

	cout << endl;
}

int main()
{
	bool newGame = true;

	do
	{
		int i = 0, num = 0;
		int hintPlace = 0;
		int usedHints = 0;
		string answer = "";
		string hintRequest = ""; 
		bool valid = false;
		bool numInserted = false;
		bool removedBefore = false;
		bool gameOver = false;
		

		player player;

		// Generation of random numbers was causing an infinite loop
		// These seeds have finite run time so I manually created "random" seeds
		int seed[5] = { 1636661343, 1636661527, 1636661672, 1636661808 };
		srand(time(NULL));

		// Choose a seed randomly from pre-generated list
		int randomseed = rand() % 3 + 0;

		// Insert selected seed as random number generater seed
		srand(seed[randomseed]);

		// Print game instructions
		cout << " Welcome to Six Love. A 6x6 game board will be generated with numbers from 1 to 6 filling the spaces. However, some of these places will be empty." << endl;
		cout << " Your job is to fill in the correct numbers from 1 to 6, making sure that there is only one instance of this number in each row and column." << endl; //Print actual instructions
		cout << " You will choose a skill level and the numbers removed as well as your number of hints will be based on this level." << endl;
		cout << " However, I must warn you that points will be deducted for each hint used! Now before we get started, what's your name?";
		cout << endl << endl;

		cout << " Name: ";
		cin >> player.name;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << " Nice to meet you " << player.name << ", please enter a skill level." << endl << endl;
		
		// Enter skill level and check to make sure it is valid
		do
		{
			cout << " Levels" << endl << " ------" << endl;
			cout << " Rookie" << endl;
			cout << " Tuff Gong" << endl;
			cout << " Hard Seed" << endl << endl;
			cout << " Level: ";
		
			getline(cin, player.level);
			cout << endl;
		
			if (player.level == "Rookie" || player.level == "rookie" || player.level == "Tuff Gong" || player.level == "tuff gong" || player.level == "Hard Seed" || player.level == "hard seed")
			{
				valid = true;
			}
			else if (player.level != "Rookie" || player.level != "rookie" || player.level != "Tuff Gong" || player.level != "tuff gong" || player.level != "Hard Seed" || player.level != "hard seed")
			{
				valid = false;
				cout << " Level not valid. Please enter one of the following skill levels." << endl;
			}

			cout << endl;

		} while (valid == false);
		
		// Call on the function to generate game board
		generateBoard();

		// Assign number of hints and number of digits to be removed based on skill level
		if (player.level == "Rookie" || player.level == "rookie")
		{
			player.digitsToRemove = 10;
			player.hints = 1;
		}
		else if (player.level == "Tuff Gong" || player.level == "tuff gong")
		{
			player.digitsToRemove = 15;
			player.hints = 2;
		}
		else if (player.level == "Hard Seed" || player.level == "hard seed")
		{
			player.digitsToRemove = 20;
			player.hints = 3;
		}

		for (i = 0; i < player.digitsToRemove; i++)
		{
			do
			{
				int randRow, randCol;

				randRow = rand() % 6 + 1;
				randCol = rand() % 6 + 1;
				removedBefore = false;

				if (progressBoard[randRow][randCol] == 0)
				{
					removedBefore = true;
				}
				else
				{
					removedBefore = false;
					progressBoard[randRow][randCol] = 0;
				}
			} while (removedBefore == true);
		}

		do
		{
			printBoard();

			// Ask the user if they wish to get a hint or quit the game
			cout << endl;
			cout << " Would you like a hint? You have " << player.hints << " hints left.";
			cout << endl;
			cout << " Enter 'yes' or 'no'.";
			cout << " Enter 'quit' to forfeit the game: ";
			cin >> hintRequest;
			cout << endl;

			// Allow user to enter play if they do not request a hint
			if (hintRequest == "no" || hintRequest == "No")
			{
				do
				{
					int rowSelect = 0, colSelect = 0;
					cout << " What number would you like to enter?: ";
					cin >> num;
					cout << " Where would you like to put it?" << endl;
					cout << " Rows: 1 - 6 || Columns : 1 - 6" << endl;
					cout << " Row: ";
					cin >> rowSelect;
					cout << " Col: ";
					cin >> colSelect;

					if (progressBoard[rowSelect - 1][colSelect - 1] == 0)
					{
						if (num == originalBoard[rowSelect - 1][colSelect - 1])
						{
							progressBoard[rowSelect - 1][colSelect - 1] = num;
							numInserted = true;
							player.digitsToRemove--;
						}
						else if (num != originalBoard[rowSelect - 1][colSelect - 1])
						{
							numInserted = false;
							cout << " Incorrect. Please try again.";
							cout << endl << endl;
						}
					}

					else if (progressBoard[rowSelect - 1][colSelect - 1] != 0)
					{
						numInserted = false;
						cout << " Invalid location. Please try again.";
						cout << endl << endl;
					}
				} while (numInserted == false);
			}

			// Give the user a hint in a randomly generated slot on the board
			else if (hintRequest == "yes" || hintRequest == "Yes")
			{
				int hintCheck = 0;

				if (player.hints == 0)
				{
					gameOver = true;
					player.hints--;
				}
				else if (player.hints > 0)
				{
					hintPlace = rand() % player.digitsToRemove + 1;
					player.hints--;
					usedHints++;

					for (int row = 0; row <= 5; row++)
					{
						for (int col = 0; col <= 5; col++)
						{
							if (progressBoard[row][col] == 0)
							{
								hintCheck++;

								if (hintCheck == hintPlace)
								{
									progressBoard[row][col] = originalBoard[row][col];
									player.digitsToRemove--;
								}
							}
						}
					}
				}

			}

			// Allow the user to forfeit the current game
			else if (hintRequest == "quit" || hintRequest == "Quit")
			{
				gameOver = true;
			}

			// Terminate the game if there are no more empty slots on the board
			if (player.digitsToRemove == 0)
			{
				gameOver = true;
			}
		} while (gameOver != true);

		// Check to see which end of game message should be displayed
		if (player.hints < 0)
		{
			player.totalPoints = 0;
			cout << " Game Over" << endl;
			cout << " Your total score is " << player.totalPoints << "." << endl;

			printBoard(2);
			cout << endl;
		}
		else if (hintRequest == "quit" || hintRequest == "Quit")
		{
			player.totalPoints = 0;
			cout << " Game Over" << endl;
			cout << " Your total score is " << player.totalPoints << "." << endl;

			printBoard(2);
			cout << endl;
		}
		else if (player.digitsToRemove == 0)
		{
			printBoard();
			cout << endl; 

			player.totalPoints = player.totalPoints - pow(2, usedHints);
			cout << " Congratulations " << player.name << "!";
			cout << endl;
			cout << " Your total score is " << player.totalPoints << ".";
			cout << endl << endl;
		}

		// Ask the user if they wish to play again
		cout << " Would you like to play again?: ";
		cin >> answer;

		// Check if answer is yes and start a new game or terminate program if answer is no
		if (answer == "yes" || answer == "Yes")
			newGame = true;
		else
			newGame = false;
		
		cout << endl;
	} while (newGame == true);

	cout << " Thanks for playing, come back soon!" << endl;

	return 0;
}