#include<iostream>
#include <string>
#include<fstream>
#include <ctime>
using namespace std;
void registerUser();
bool loginUser();
int wordLength(string& word);
void playGame(const string& username);
string chooseWord();
void updateGameRecords(const string& username, bool won, int score);
void registerUser()
{
	string username, password, fileUsername, filePassword;
	cout << "Enter username = ";
	getline(cin, username);
	cout << "Enter password = ";
	cin >> password;
	ofstream file("users.txt", ios::app);
	ifstream f1("users.txt");
	if (file.is_open())
	{
		while (f1 >> fileUsername >> filePassword)
		{
			if ((fileUsername == username) && (filePassword == password))
			{
				cout << "A user with that username or password already exists. Try with different credentials!\n\n";
			}
			else
			{
				file << username << "\t" << password << "\n";
				file.close();
				cout << "User registered successfully!\n";
				break;
			}
		}
	}
	else
	{
		cout << "Error opening file for registration.\n";
	}
}
bool loginUser()
{
	string username, password, fileUsername, filePassword;
	cout << "Enter username = ";
	cin >> username;
	cout << "Enter password = ";
	cin >> password;
	ifstream file("users.txt");
	if (file.is_open())
	{
		while (file >> fileUsername >> filePassword)
		{
			if ((fileUsername == username) && (filePassword == password))
			{
				file.close();
				return true;
			}
		}
		file.close();
	}
	else
	{
		cout << "Error opening file for login.\n";
	}
	return false;
}
string chooseWord()
{
	const int MAX_WORDS = 1000;
	string words[MAX_WORDS];
	int wordCount = 0;
	ifstream file("words.txt");
	if (!file.is_open())
	{
		cout << "Error opening words file.\n";
		exit(1);
	}
	while (file >> words[wordCount])
	{
		wordCount++;
		if (wordCount >= MAX_WORDS)
		{
			cout << "Exceeded maximum word limit.\n";
			break;
		}
	}
	file.close();
	if (wordCount == 0)
	{
		cout << "Words file is empty.\n";
		exit(1);
	}
	int randomIndex = rand() % wordCount;
	return words[randomIndex];
}
int wordLength(string& word)
{
	int length = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}
void playGame(const string& username)
{
	string word = chooseWord();
	string guessedWord(wordLength(word), '_');
	int triesLeft = 6;
	bool won = false;
	while (triesLeft > 0 && !won)
	{
		char guess;
		if (triesLeft == 6)
		{
			cout << "\n|\t\t|\n|\n|\n|\n|\n";
		}
		cout << "Current word= " << guessedWord << "\n";
		cout << "Tries left= " << triesLeft << "\n";
		cout << "Enter your guess= ";
		cin >> guess;
		if (guess >= 'A' && guess <= 'Z')
		{
			guess = guess + 32;
		}
		bool correctGuess = false;
		for (int i = 0; i < wordLength(word); i++)
		{
			if (word[i] == guess && guessedWord[i] == '_')
			{
				guessedWord[i] = guess;
				correctGuess = true;
			}
		}
		if (!correctGuess)
		{
			triesLeft--;
			if (triesLeft == 5)
			{
				cout << "\n|\t\t|\n|\t\tO\n|\n|\n|\n";
			}
			else if (triesLeft == 4)
			{
				cout << "\n|\t\t|\n|\t\tO\n|\t\t|\n|\n|\n";
			}
			else if (triesLeft == 3)
			{
				cout << "\n|\t\t|\n|\t\tO\n|              /|\n|\n|\n";
			}
			else if (triesLeft == 2)
			{
				cout << "\n|\t\t|\n|\t\tO\n|              /||\n|\n|\n";
			}
			else if (triesLeft == 1)
			{
				cout << "\n|\t\t|\n|\t\tO\n|              /||\n|              /\n|\n";
			}
		}
		if (guessedWord == word)
		{
			won = true;
		}
	}
	if (won)
	{
		cout << "Congratulations! You guessed the word right. Word = " << word << "\n";
		int score = triesLeft;
		updateGameRecords(username, true, score);
	}
	else
	{
		cout << "Game Over!\nThe word was= " << word << "\n";
		cout << "\n|\t\t|\n|\t\tO\n|              /||\n|              / |\n|\n";
		updateGameRecords(username, false, 0);
	}
	cout << "Do you want to play again? (Y/N)= ";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		playGame(username);
	}
}
void updateGameRecords(const string& username, bool won, int score)
{
	ofstream file("game_records.txt", ios::app);
	if (file.is_open())
	{
		file << "Username" << "\t" << "Game Status" << "\t" << "Score";
		file << username << "\t  " << (won ? "Won" : "Lost") << "\t  " << score << "\n";
		file.close();
	}
	else
	{
		cout << "Error opening game records file.\n";
	}
}
