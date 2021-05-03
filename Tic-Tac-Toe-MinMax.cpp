#include             "bits/stdc++.h"
#define ff           first
#define ss           second
#define int          long long
#define endl          '\n'

using namespace std;

vector<vector<char>> game{
	{'_' , '_' , '_'},
	{'_' , '_' , '_'},
	{'_' , '_' , '_'}
};

void carvingBoard() {
	cout << endl << game[0][0] << " | " << game[0][1] << " | "  << game[0][2] << endl; cout << "__  _   __ " << endl;
	cout << endl << game[1][0] << " | " << game[1][1] << " | "  << game[1][2] << endl; cout << "__  _   __ " << endl;
	cout << endl << game[2][0] << " | " << game[2][1] << " | "  << game[2][2] << endl;
}
bool checkWinPlayer() {
	for (int i = 0 ; i < 3; i++) {
		if (game[i][0] == game[i][1] && game[i][1] == game[i][2] && game[i][0] == 'O') return true;
	}
	for (int i = 0 ; i < 3; i++) {
		if (game[0][i] == game[1][i] && game[1][i] == game[2][i] && game[0][i] == 'O') return true;
	}
	if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0] == 'O') return true;
	if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] == 'O') return true;
	return false;
}


bool checkWinComputer() {
	for (int i = 0 ; i < 3; i++) {
		if (game[i][0] == game[i][1] && game[i][1] == game[i][2] && game[i][0] == 'X') return true;
	}

	for (int i = 0 ; i < 3; i++) {
		if (game[0][i] == game[1][i] && game[1][i] == game[2][i] && game[0][i] == 'X') return true;
	}
	if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0] == 'X') return true;
	if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] == 'X') return true;
	return false;
}

bool checkDraw() {
	for (int i = 0; i < 3 ; i++) {
		for (int j = 0 ; j < 3 ; j++) {
			if (game[i][j] != 'X' && game[i][j] != 'O')
				return false;
		}
	}
	return true;
}

int minimax(bool Max, int depth) {
	if (checkWinComputer() == true) return 10;
	else if (checkWinPlayer() == true) return -10;
	else if (checkDraw() == true) return 0;
	if (Max == true) {
		int optimum = INT16_MIN;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game[i][j] == '*') {
					game[i][j] = 'X';
					optimum = max(optimum, minimax(!Max, depth + 1));
					game[i][j] = '*';
				}
			}
		}
		return optimum;
	}
	else {
		int optimum = INT16_MAX;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game[i][j] == '*') {
					game[i][j] = 'O';
					optimum = min(optimum, minimax(!Max , depth + 1));
					game[i][j] = '*';
				}
			}
		}
		return optimum;
	}
}
void Find_Best_Move()
{
	int best_value = INT16_MIN;
	int best_x = -1, best_y = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game[i][j] == '*') {
				game[i][j] = 'X';
				int move_value = minimax(false, 0);
				game[i][j] = '*';
				if (move_value > best_value) {
					best_x = i;
					best_y = j;
					best_value = move_value;
				}
			}
		}
	}
	game[best_x][best_y] = 'X';
}
int32_t main()
{
	int player_score = 0;
	int computer_score = 0;
	char play_again;
	do
	{
		for (int i = 0 ; i < 3 ; i++) {
			for (int j = 0 ; j < 3 ; j++) {
				game[i][j] = '*';
			}
		}
		cout << "TIC - TAC - TOE" << endl;
		cout << endl;
		cout << "USER -> 'O' COMPUTER -> 'X' " << endl;
		cout << endl;
		carvingBoard();
		int x, y;
		while (1)
		{
label1 :
			cout << "ENTER YOUR MOVE(X,Y): ";
			cin >> x >> y;
			if ( game[x - 1][y - 1] == '*' && x < 4 && y < 4) {
				game[x - 1][y - 1] = 'O';
				// carvingBoard();
				// cout << endl;
			}
			else
			{
				cout << "INVALID MOVE" << endl;
				goto label1;
			}
			if (checkWinPlayer() == true) {
				cout << "YOU WON " << endl;
				player_score++;
				break;
			}
			// cout << "CPU MOVE :" << endl;
			Find_Best_Move();
			carvingBoard();
			cout << endl;
			if (checkWinComputer() == true) {
				cout << "YOU LOSE " << endl;
				computer_score++;
				break;
			}
			if (checkDraw() == true) {
				cout << "GAME DRAWN: " << endl;
				break;
			}
		}

		cout << "YOUR SCORE: " << player_score << " COMPUTER SCORE: " << computer_score << endl;
		cout << "DO YOU WANT TO PLAY AGAIN?(Y/N): ";
		cin >> play_again;

	} while (
	    play_again == 'Y'
	);

	cout << "YOUR SCORE: " << player_score << endl;
	cout << "COMPUTER SCORE: " << computer_score << endl;
	return 0;
}
