#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int H = 10000;
set<vector<vector<int>>> resultBoards;

vector<pair<int, int>> FindExtraValues(vector<vector<int>>& board, vector<vector<int>>& extraBoard) {
	int n = board.size();
	int m = board[0].size();

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] >= 0) {
				int x = i + 2;
				int y = j + 2;

				bool xp2 = i + 2 < n;
				bool xm2 = i - 2 >= 0;
				bool yp2 = j + 2 < m;
				bool ym2 = j - 2 >= 0;
				bool xp1 = i + 1 < n;
				bool xm1 = i - 1 >= 0;
				bool yp1 = j + 1 < m;
				bool ym1 = j - 1 >= 0;

				if (xp2 && ym1 && board[i + 2][j - 1] == 0) {
					extraBoard[x][y]++;
				}
				if (xp2 && yp1 && board[i + 2][j + 1] == 0) {
					extraBoard[x][y]++;
				}
				if (xm2 && ym1 && board[i - 2][j - 1] == 0) {
					extraBoard[x][y]++;
				}
				if (xm2 && yp1 && board[i - 2][j + 1] == 0) {
					extraBoard[x][y]++;
				}
				if (xp1 && ym2 && board[i + 1][j - 2] == 0) {
					extraBoard[x][y]++;
				}
				if (xp1 && yp2 && board[i + 1][j + 2] == 0) {
					extraBoard[x][y]++;
				}
				if (xm1 && ym2 && board[i - 1][j - 2] == 0) {
					extraBoard[x][y]++;
				}
				if (xm1 && yp2 && board[i - 1][j + 2] == 0) {
					extraBoard[x][y]++;
				}
			}
		}
	}

	int maxValue = 0;
	pair<int, int> coord;
	vector<pair<int, int>> vecCoord;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			int x = i + 2;
			int y = j + 2;
			if (board[i][j] < 0) {
				extraBoard[x][y] = 1;
			}
			else if (maxValue < extraBoard[x][y]) {
				maxValue = extraBoard[x][y];
				coord.first = i;
				coord.second = j;
			}
		}
	}

	//sort(vecCoord.begin(), vecCoord.end());
	
	
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			int x = i + 2;
			int y = j + 2;
			if (maxValue == extraBoard[x][y]) {
				vecCoord.push_back(make_pair(i, j));
			}
		}
	}
	
	return vecCoord;
}

void PlaceKnight(vector<vector<int>>& board, pair<int, int> coord) {
	int x = coord.first;
	int y = coord.second;
	board[x][y] = -1;

	int n = board.size();
	int m = board[0].size();

	bool xp2 = x + 2 < n;
	bool xm2 = x - 2 >= 0;
	bool yp2 = y + 2 < m;
	bool ym2 = y - 2 >= 0;
	bool xp1 = x + 1 < n;
	bool xm1 = x - 1 >= 0;
	bool yp1 = y + 1 < m;
	bool ym1 = y - 1 >= 0;

	if (xp2 && ym1 && board[x + 2][y - 1] >= 0) {
		board[x + 2][y - 1] = 1;
	}
	if (xp2 && yp1 && board[x + 2][y + 1] >= 0) {
		board[x + 2][y + 1] = 1;
	}
	if (xm2 && ym1 && board[x - 2][y - 1] >= 0) {
		board[x - 2][y - 1] = 1;
	}
	if (xm2 && yp1 && board[x - 2][y + 1] >= 0) {
		board[x - 2][y + 1] = 1;
	}
	if (xp1 && ym2 && board[x + 1][y - 2] >= 0) {
		board[x + 1][y - 2] = 1;
	}
	if (xp1 && yp2 && board[x + 1][y + 2] >= 0) {
		board[x + 1][y + 2] = 1;
	}
	if (xm1 && ym2 && board[x - 1][y - 2] >= 0) {
		board[x - 1][y - 2] = 1;
	}
	if (xm1 && yp2 && board[x - 1][y + 2] >= 0) {
		board[x - 1][y + 2] = 1;
	}
}

void RenewBoard(vector<vector<int>>& board, vector<vector<int>>& extraBoard) {
	for (int i = 0; i < extraBoard.size(); i++) {
		fill(extraBoard[i].begin(), extraBoard[i].end(), 0);
	}

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			int x = i + 2;
			int y = j + 2;
			switch (board[i][j]) {
				case -1: {
					extraBoard[x][y] = 1;
					extraBoard[x + 2][y + 1] = 1;
					extraBoard[x + 2][y - 1] = 1;
					extraBoard[x - 2][y + 1] = 1;
					extraBoard[x - 2][y - 1] = 1;
					extraBoard[x + 1][y - 2] = 1;
					extraBoard[x + 1][y + 2] = 1;
					extraBoard[x - 1][y + 2] = 1;
					extraBoard[x - 1][y - 2] = 1;
					break;
				}
				case -2: {
					extraBoard[x][y] = 1;
				}
			}
		}
	}
}

bool CheckBoard(vector<vector<int>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (!board[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void PrintBoard(const vector<vector<int>>& board, ofstream& fout) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			switch (board[i][j]) {
				case -1: case -2: {
					fout << abs(board[i][j]) << " ";
					break;
				}
				default: {
					fout << "0 ";
				}
			}
		}
		fout << endl;
	}
}

void PrintExtraBoard(vector<vector<int>>& board, ofstream& fout) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			fout << (board[i][j]) << " ";
		}
		fout << endl;
	}
}

void RecountBoard(vector<vector<int>>& board, vector<vector<int>>& extraBoard) {
	for (int i = 0; i < extraBoard.size(); i++) {
		fill(extraBoard[i].begin(), extraBoard[i].end(), 0);
	}

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			int x = i + 2;
			int y = j + 2;
			switch (board[i][j]) {
			case -1: {
				extraBoard[x][y] = -1; //?? 
				extraBoard[x + 2][y + 1]++;
				extraBoard[x + 2][y - 1]++;
				extraBoard[x - 2][y + 1]++;
				extraBoard[x - 2][y - 1]++;
				extraBoard[x + 1][y - 2]++;
				extraBoard[x + 1][y + 2]++;
				extraBoard[x - 1][y + 2]++;
				extraBoard[x - 1][y - 2]++;
				break;
			}
			case -2: {
				extraBoard[x][y] = -2;
			}
			}
		}
	}
}

int DeleteHorses(vector<vector<int>>& board, vector<vector<int>>& extraBoard) {

	int delHorses = 0;

	int n = board.size();
	int m = board[0].size();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int toDelete = true;
			if (board[i][j] == -1) {
				int x = i + 2;
				int y = j + 2;
				int k = 0;

				bool xp2 = i + 2 < n;
				bool xm2 = i - 2 >= 0;
				bool yp2 = j + 2 < m;
				bool ym2 = j - 2 >= 0;
				bool xp1 = i + 1 < n;
				bool xm1 = i - 1 >= 0;
				bool yp1 = j + 1 < m;
				bool ym1 = j - 1 >= 0;

				if (xp2 && ym1) {
					if (extraBoard[x + 2][y - 1] == 1) {
						toDelete = false;
						break;
					}
					else {
						extraBoard[x + 2][y - 1]--;
					}
				}
				else {
					k++;
				}

				if (xp2 && yp1 && extraBoard[x + 2][y + 1] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xm2 && ym1 && extraBoard[x - 2][y - 1] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xm2 && yp1 && extraBoard[x - 2][y + 1] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xp1 && ym2 && extraBoard[x + 1][y - 2] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xp1 && yp2 && extraBoard[x + 1][y + 2] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xm1 && ym2 && extraBoard[x - 1][y - 2] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}

				if (xm1 && yp2 && extraBoard[x - 1][y + 2] == 1) {
					toDelete = false;
					break;
				}
				else {
					k++;
				}
				
				if (toDelete && k != 8) {
					delHorses++;
					board[i][j] = 1;
				}
			}
		}
	}
	return delHorses;
}

void BruteForceMain(vector<vector<int>>& board, vector<vector<int>>& extraBoard, int h);

void BruteForce(vector<vector<int>> board, vector<vector<int>> extraBoard, int h, pair<int, int> coord) {
	PlaceKnight(board, coord);
	h++;
	if (h > H) {
		return;
	}
	if (CheckBoard(board)) {
		RecountBoard(board, extraBoard);
		int delHorse = DeleteHorses(board, extraBoard);
		h -= delHorse;

		if (h < H) {
			H = h;
			resultBoards.clear();
			resultBoards.insert(board);
			return;
		}
		if (h == H) {
			resultBoards.insert(board);
			return;
		}
		return;
	}
	RenewBoard(board, extraBoard);
	BruteForceMain(board, extraBoard, h);
}

void BruteForceMain(vector<vector<int>>& board, vector<vector<int>>& extraBoard, int h) {
	vector<pair<int, int>> vecCoord = FindExtraValues(board, extraBoard);
	for (int i = 0; i < vecCoord.size(); i++) {
		BruteForce(board, extraBoard, h, vecCoord[i]);
	}
}

int main() {

	int n, m, k;
	fin >> n >> m >> k;

	vector<vector<int>> board(n);
	vector<vector<int>> extraBoard((int)n + 4);

	for (int i = 0; i < n; i++) {
		board[i] = vector<int>(m, 0);
	}

	for (int i = 0; i < n + 4; i++) {
		extraBoard[i] = vector<int>((int)m + 4, 0);
	}

	for (int i = 0; i < k; i++) {
		int x, y;
		fin >> x >> y;
		x--;
		y--;
		board[x][y] = -2;
	}
	
	BruteForceMain(board, extraBoard, 0);

	fout << resultBoards.size() << endl << endl;;
	for (auto it = resultBoards.begin(); it != resultBoards.end(); it++)
	{
		PrintBoard(*it, fout);
		fout << endl;
	}

	return 0;
}