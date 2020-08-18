#include <iostream>

using namespace std;

char matrix[3][3] = { '1','2','3','4','5','6','7','8','9' };
char player = 'X';
void Draw()
{
	cout << "Tic Tac Toe VERSION 0.0 - FUCK EDITION" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Input()
{
	cout << "It's " << player << " turn. " << endl;
	char a;
	cout << "Press the number of the field: " << endl;
	cin >> a;
	{
		if (a == '1')
		{

		}
	}
}

void TogglePlayer()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

char Win()
{
	//Player
	if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X')
		return 'X';
	if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X')
		return 'X';
	if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X')
		return 'X';
	if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X')
		return 'X';
	if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
		return 'X';
	if (matrix[0][2] == 'X' && matrix[1][1] == 'X' && matrix[2][0] == 'X')
		return 'X';

	//TogglePlayer
	if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O')
		return 'O';
	if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O')
		return 'O';
	if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O')
		return 'O';
	if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O')
		return 'O';
	if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
		return 'O';
	if (matrix[0][2] == 'O' && matrix[1][1] == 'O' && matrix[2][0] == 'O')
		return 'O';



	/*
	00 01 02
	10 11 12
	20 21 22
		*/
	return '/';
}

int main()
{
	int n = 0;
	Draw();
	while (1)
	{
		n++;
		Input();
		Draw();
		if (Win() == 'X')
		{
			cout << "X wins!" << endl;;
			break;
		}
		else if (Win() == 'O')
		{
			cout << "O wins!" << endl;;
			break;
		}
		else if (Win() == '/' && n == 9)
		{
			cout << "It's a Draw!" << endl;;
			break;
		}
		TogglePlayer();
	}
	system("pause");
	return 0;
}