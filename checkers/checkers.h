#ifndef CHECKERS_HPP
#define CHECKERS_HPP
#include <iostream>
#include <vector>

using namespace std;

class eksperyment  //sluzy do przechowywania wszytskich kombinacji ruchow
{
public:
	int ruch_w;
	int ruch_k;
	int poz_w;
	int poz_k;
	int ocena{ -500 };
	char pion;
	vector<eksperyment> x;
};

class checkers
{
public:
	vector<vector<char>> bierki
	{
		{' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
		{'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '},
		{' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'O', ' ', 'O', ' ', 'O', ' ', 'O', ' '},
		{' ', 'O', ' ', 'O', ' ', 'O', ' ', 'O'},
		{'O', ' ', 'O', ' ', 'O', ' ', 'O', ' '}
	};
	vector<eksperyment> all_moves;

	void move(vector<vector<char>>& board, char gracz, bool tryb_pracy, int wiersz_, int kolumna_, int wiersz_ruch_, int kolumna_ruch_);
	void show(vector<vector<char>> board);
	int evaluate(vector<vector<char>> board);   //ocenia pozycje 
	bool check_move(vector<vector<char>>& board, int wiersz, int kolumna, int wiersz_ruch, int kolumna_ruch, char gracz); //sprawdza czy ruch jest legalny
	void generate_moves(vector<vector<char>>& board, int glebokosc, char gracz, vector<eksperyment>& actual_moves); //generuje wszystkie ruchy
	int evaluate_tree(vector<eksperyment>& actual_moves); //funkcja przyporzadkowywuje wartosci z ostatnich pozycji w gore drzewa  
	void best_line(vector<vector<char>>& board, vector<eksperyment> actual_moves); //funkcja wybiera najlepszy dla x wariant
};


#endif CHECKERS_HPP