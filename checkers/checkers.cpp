#include <iostream>
#include <vector>  
#include <cmath>
#include "checkers.h"

using namespace std;

void checkers::move(vector<vector<char>>& board, char gracz, bool tryb_pracy, int wiersz_, int kolumna_, int wiersz_ruch_, int kolumna_ruch_)//przerabiam funkcje dodajac zmienna tryb pracy i wartosci kolumna, wiersz ruch itd, zaleznie od trybu pracy wykonujemy procedure wpisania pola, bo funkcja bedzie uzywana tez dp rekurencji.
{
back: //wracamy gdy nie zostanie wykonany zaden ruch (zle sa podane ruchy i/lub wybrane pionki)

	int wiersz{ wiersz_ }, kolumna{ kolumna_ }, wiersz_ruch{ wiersz_ruch_ }, kolumna_ruch{ kolumna_ruch_ };   //wiersz, kolumna wspolrzedne ruszanego pionka, _ruch wspolrzedne chcianego ruchu

	if (tryb_pracy == true)
	{
		if (gracz == 'O')
			cout << endl << "!RUCH O!";
		else
			cout << endl << "!RUCH X!";

		char pole[3];

		cout << endl << "Wybierz pionka [np 3A]" << endl;
		cin >> pole;
		wiersz = pole[0] - '0';
		kolumna = int(pole[1]) - 65; // A - 65
		wiersz = 8 - wiersz;
		//cout << endl << wiersz << " " << kolumna;

		cout << endl << "Wybierz ruch [np 4B]" << endl;
		cin >> pole;
		wiersz_ruch = pole[0] - '0';  //zmiana na int  
		kolumna_ruch = int(pole[1]) - 65; //zmiana liter na cyfry 0-8
		wiersz_ruch = 8 - wiersz_ruch; //zmiana na wspolrzedne vectora
		//cout << endl << wiersz_ruch << " " << kolumna_ruch;
	}


	if (gracz == 'O' && board[wiersz][kolumna] == 'O')
	{
		// gdy przesuwamy sie do 'gory', o kolumne jeden w lewo lub prawo, kiedy nie ma pionka na polu stawanym, tylko na 'ciemnych polach'
		if (wiersz_ruch < wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && ((kolumna_ruch == kolumna + 1) || (kolumna_ruch == kolumna - 1)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
		}
		//bicie 
		else if (wiersz_ruch < wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && (board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'X' || board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'Y') && ((kolumna_ruch == kolumna + 2) || (kolumna_ruch == kolumna - 2)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
			board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] = ' ';
		}
		else
			goto back;
	}
	else if (gracz == 'O' && board[wiersz][kolumna] == 'Q')
	{
		//sprawdza czy ruch jest legalny 
		if (board[wiersz_ruch][kolumna_ruch] == ' ' && (abs(kolumna - kolumna_ruch) == abs(wiersz - wiersz_ruch)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			int a{ 0 }, b{ 0 }; //sluzy do ikrementacji i sprawdzania znakow na diagonali po której chcemy sie poruszac
			if (wiersz > wiersz_ruch)
				a = -1;
			else
				a = 1;
			if (kolumna > kolumna_ruch)
				b = -1;
			else
				b = 1;

			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
			{
				// wyrzuca nas gdy obok siebie na diagonali sa dwa pionki lub nasz jeden pionek
				if ((board[w][k] != ' ' && board[w + a][k + b] != ' ') || (board[w][k] == 'O' || board[w][k] == 'Q'))
				{
					goto back;
				}
			}
			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
			{
				if ((board[w][k] == 'X' || board[w][k] == 'Y') && board[w + a][k + b] == ' ')
				{
					board[w][k] = ' ';
				}
			}
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
		}
		else
			goto back;
	}

	// dla X poruszanie sie, analogicznie jak O
	else if (gracz == 'X' && board[wiersz][kolumna] == 'X')
	{
		if (wiersz_ruch > wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && ((kolumna_ruch == kolumna + 1) || (kolumna_ruch == kolumna - 1)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
		}
		else if (wiersz_ruch > wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && (board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'O' || board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'Q') && ((kolumna_ruch == kolumna + 2) || (kolumna_ruch == kolumna - 2)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
			board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] = ' ';
		}
		else
			goto back;
	}
	else if (gracz == 'X' && board[wiersz][kolumna] == 'Y')
	{
		if (board[wiersz_ruch][kolumna_ruch] == ' ' && (abs(kolumna - kolumna_ruch) == abs(wiersz - wiersz_ruch)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			int a{ 0 }, b{ 0 };
			if (wiersz > wiersz_ruch)
				a = -1;
			else
				a = 1;
			if (kolumna > kolumna_ruch)
				b = -1;
			else
				b = 1;

			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
			{
				if ((board[w][k] != ' ' && board[w + a][k + b] != ' ') || (board[w][k] == 'X' || board[w][k] == 'Y'))
					goto back;
			}
			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
			{
				if ((board[w][k] == 'O' || board[w][k] == 'Q') && board[w + a][k + b] == ' ')
					board[w][k] = ' ';
			}
			swap(board[wiersz_ruch][kolumna_ruch], board[wiersz][kolumna]);
		}
		else
			goto back;
	}
	else
		goto back;

	//promocja gdy znajda sie na swoich ostatnich rzedach
	if (wiersz_ruch == 0 && board[wiersz_ruch][kolumna_ruch] == 'O')
		board[wiersz_ruch][kolumna_ruch] = 'Q';
	else if (wiersz_ruch == 7 && board[wiersz_ruch][kolumna_ruch] == 'X')
		board[wiersz_ruch][kolumna_ruch] = 'Y';
}


void checkers::show(vector<vector<char>> board)
{
	int znak{ 65 }; //alfabet
	cout << endl << "    ";
	for (int i{ 0 }; i <= 7; i++)
		cout << char(znak++) << "   ";

	cout << endl;
	for (int k{ 8 }, wiersz{ 0 }, kolumna{ 0 }; k >= 1; k--, wiersz++, kolumna = 0)
	{
		cout << "  ";
		for (int i{ 0 }; i <= 32; i++)
			cout << "-";

		cout << endl << k << " ";

		for (int i{ 0 }; i <= 32; i++)
		{
			if (i % 4 == 0)
				cout << "|";
			else if (i % 4 == 2)
				cout << board[wiersz][kolumna++];
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "  ";
	for (int i{ 0 }; i <= 32; i++)
		cout << "-";
}

int checkers::evaluate(vector<vector<char>> board)
{
	int x_points{ 0 }, o_points{ 0 };
	for (int i = 0; i < board.size(); i++)
	{
		for (int k = 0; k < board.size(); k++)
		{
			if (board[i][k] == 'X')
				x_points += -5;
			if (board[i][k] == 'Y')
				x_points += -50;
			if ((i == 0 || i == 7 || k == 0 || k == 7) && (board[i][k] == 'X' || board[i][k] == 'Y'))
				x_points += -1;
			if ((i == 1 || i == 6 || k == 1 || k == 6) && (board[i][k] == 'X' || board[i][k] == 'Y'))
				x_points += -1;
			if ((i == 6 || i == 7) && board[i][k] == 'X')
				x_points += -20;
			else if ((i == 4 || i == 5) && board[i][k] == 'X')
				x_points += -3;
			else if ((i == 2 || i == 3) && board[i][k] == 'X')
				x_points += -1;

			if (board[i][k] == 'O')
				o_points += 5;
			if (board[i][k] == 'Q')
				o_points += 50;
			if ((i == 0 || i == 7 || k == 0 || k == 7) && (board[i][k] == 'O' || board[i][k] == 'Q'))
				o_points += 1;
			if ((i == 1 || i == 6 || k == 1 || k == 6) && (board[i][k] == 'O' || board[i][k] == 'Q'))
				o_points += 1;
			if ((i == 0 || i == 1) && board[i][k] == 'O')
				o_points += 20;
			else if ((i == 2 || i == 3) && board[i][k] == 'O')
				o_points += 3;
			else if ((i == 4 || i == 5) && board[i][k] == 'O')
				o_points += 1;
		}
	}
	return o_points + x_points;
}

bool checkers::check_move(vector<vector<char>>& board, int wiersz, int kolumna, int wiersz_ruch, int kolumna_ruch, char gracz)
{
	if (gracz == 'O' && board[wiersz][kolumna] == 'O')
	{
		if (wiersz_ruch < wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && ((kolumna_ruch == kolumna + 1) || (kolumna_ruch == kolumna - 1)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
			return true;
		else if (wiersz_ruch < wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && (board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'X' || board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'Y') && ((kolumna_ruch == kolumna + 2) || (kolumna_ruch == kolumna - 2)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
			return true;
		else
			return false;
	}
	else if (gracz == 'O' && board[wiersz][kolumna] == 'Q')
	{
		if (board[wiersz_ruch][kolumna_ruch] == ' ' && (abs(kolumna - kolumna_ruch) == abs(wiersz - wiersz_ruch)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			int a{ 0 }, b{ 0 };
			if (wiersz > wiersz_ruch)
				a = -1;
			else
				a = 1;
			if (kolumna > kolumna_ruch)
				b = -1;
			else
				b = 1;

			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
				if ((board[w][k] != ' ' && board[w + a][k + b] != ' ') || (board[w][k] == 'O' || board[w][k] == 'Q'))
					return false;

			return true;
		}
		else
			return false;
	}

	// dla X poruszanie sie, analogicznie jak O
	else if (gracz == 'X' && board[wiersz][kolumna] == 'X')
	{
		if (wiersz_ruch > wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && ((kolumna_ruch == kolumna + 1) || (kolumna_ruch == kolumna - 1)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
			return true;
		else if (wiersz_ruch > wiersz && board[wiersz_ruch][kolumna_ruch] == ' ' && (board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'O' || board[(wiersz_ruch + wiersz) / 2][(kolumna_ruch + kolumna) / 2] == 'Q') && ((kolumna_ruch == kolumna + 2) || (kolumna_ruch == kolumna - 2)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
			return true;
		else
			return false;
	}
	else if (gracz == 'X' && board[wiersz][kolumna] == 'Y')
	{
		if (board[wiersz_ruch][kolumna_ruch] == ' ' && (abs(kolumna - kolumna_ruch) == abs(wiersz - wiersz_ruch)) && ((wiersz_ruch % 2 == 0 && kolumna_ruch % 2 == 1) || (wiersz_ruch % 2 == 1 && kolumna_ruch % 2 == 0)))
		{
			int a{ 0 }, b{ 0 };
			if (wiersz > wiersz_ruch)
				a = -1;
			else
				a = 1;
			if (kolumna > kolumna_ruch)
				b = -1;
			else
				b = 1;

			for (int w{ wiersz + a }, k{ kolumna + b }; w != wiersz_ruch && k != kolumna_ruch; w += a, k += b)
				if ((board[w][k] != ' ' && board[w + a][k + b] != ' ') || (board[w][k] == 'X' || board[w][k] == 'Y'))
					return false;

			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void checkers::generate_moves(vector<vector<char>>& board, int glebokosc, char gracz, vector<eksperyment>& actual_moves)
{
	int licznik = 0;
	if (glebokosc == 0)
		return;

	char dama{ ' ' }, pion{ ' ' }, przeciwnik{ ' ' }, gracz_dama{ ' ' };
	if (gracz == 'X')
		dama = 'Q', pion = 'O', przeciwnik = 'O', gracz_dama = 'Y';
	else if (gracz == 'O')
		dama = 'Y', pion = 'X', przeciwnik = 'X', gracz_dama = 'Q';

	vector<vector<char>> kopia = board;

	//w, k - pozycje pionkow, wspolrzedna_w wspolrzedna_k - pozycje ruchu
	for (int w{ 0 }; w <= 7; w++)
	{
		for (int k{ 0 }; k <= 7; k++)
		{
			if (board[w][k] == gracz)
			{
				for (int i{ w - 1 }; i <= w + 1; i += 2)
					for (int l{ k - 1 }; l <= k + 1; l += 2) //funkcja szuka ruchow na okolo
					{
						kopia = board;
						int wspolrzedna_w{ i }, wspolrzedna_k{ l };
						if (wspolrzedna_w > 7 || wspolrzedna_w < 0 || wspolrzedna_k > 7 || wspolrzedna_k < 0)
							continue;
						if (board[wspolrzedna_w][wspolrzedna_k] == gracz || board[wspolrzedna_w][wspolrzedna_k] == gracz_dama)
							continue;
						if (board[wspolrzedna_w][wspolrzedna_k] == pion || board[wspolrzedna_w][wspolrzedna_k] == dama) //jesli obok pionek przeciwnika jest to patrzy poz dalej
						{
							wspolrzedna_w += (wspolrzedna_w - w);
							wspolrzedna_k += (wspolrzedna_k - k);
							if (wspolrzedna_w > 7 || wspolrzedna_w < 0 || wspolrzedna_k > 7 || wspolrzedna_k < 0)
								continue;
						}
						if (check_move(board, w, k, wspolrzedna_w, wspolrzedna_k, gracz) == true)
						{
							move(kopia, gracz, false, w, k, wspolrzedna_w, wspolrzedna_k);
							eksperyment zmienna;
							zmienna.poz_w = w;
							zmienna.poz_k = k;
							zmienna.ruch_w = wspolrzedna_w;
							zmienna.ruch_k = wspolrzedna_k;
							zmienna.pion = gracz;
							//if (glebokosc == 1) //jesli jestesmy na ostatnim pietrze dokonujemy oceny pozycji
							zmienna.ocena = evaluate(kopia);
							actual_moves.push_back(zmienna);
							generate_moves(kopia, glebokosc - 1, przeciwnik, actual_moves[licznik].x);
							licznik++;
						}
					}
			}
			else if (board[w][k] == gracz_dama)
			{
				for (int p{ 1 }, q{ 0 }; p <= 8; p++, q += 2)  //sluzy szukaniu na calej diagonali
					for (int i{ w - p }; i <= w + p; i += 2 + q)
						for (int l{ k - p }; l <= k + p; l += 2) //funkcja szuka ruchow na okolo
						{
							kopia = board;
							int wspolrzedna_w{ i }, wspolrzedna_k{ l };
							if (wspolrzedna_w > 7 || wspolrzedna_w < 0 || wspolrzedna_k > 7 || wspolrzedna_k < 0)
								continue;
							if (board[wspolrzedna_w][wspolrzedna_k] == gracz || board[wspolrzedna_w][wspolrzedna_k] == gracz_dama)
								continue;

							if (check_move(board, w, k, wspolrzedna_w, wspolrzedna_k, gracz) == true)
							{
								move(kopia, gracz, false, w, k, wspolrzedna_w, wspolrzedna_k);
								eksperyment zmienna;
								zmienna.poz_w = w;
								zmienna.poz_k = k;
								zmienna.ruch_w = wspolrzedna_w;
								zmienna.ruch_k = wspolrzedna_k;
								zmienna.pion = gracz;
								zmienna.ocena = evaluate(kopia); 
								actual_moves.push_back(zmienna);
								generate_moves(kopia, glebokosc - 1, przeciwnik, actual_moves[licznik].x);
								licznik++;
							}
						}
			}

		}
	}
}

int checkers::evaluate_tree(vector<eksperyment>& actual_moves) //funkcja przyporzadkowywuje wartosci z ostatnich pozycji w gore drzewa  
{
	int min{ 10000 }, max{ -10000 };

	for (int i{ 0 }; i < actual_moves.size(); i++)
	{
		if (actual_moves[i].x.size() == 0)
		{
			// tutaj rozpoczynam zliczanie
			if (actual_moves[i].pion == 'O' && actual_moves[i].ocena >= max)				
				max = actual_moves[i].ocena;
			if (actual_moves[i].pion == 'X' && actual_moves[i].ocena <= min)
				min = actual_moves[i].ocena;
		}
		else
		{
			actual_moves[i].ocena = evaluate_tree(actual_moves[i].x);
			if (actual_moves[i].pion == 'O' && actual_moves[i].ocena >= max)
				max = actual_moves[i].ocena;
			if (actual_moves[i].pion == 'X' && actual_moves[i].ocena <= min)
				min = actual_moves[i].ocena;
		}
	}
	if (actual_moves[0].pion == 'O')
		return max;
	else if (actual_moves[0].pion == 'X')
		return min;
}

void checkers::best_line(vector<vector<char>>& board, vector<eksperyment> actual_moves)
{
	int min{ 10000 };
	eksperyment finito;
	cout << "Ocena (wiersz,kolumna;wiersz ruch,koloumna ruch)";
	for (int i{ 0 }; i < actual_moves.size(); i++)
	{
		cout << endl << "(" << actual_moves[i].poz_w << "," << actual_moves[i].poz_k << ";" << actual_moves[i].ruch_w << "," << actual_moves[i].ruch_k << ") - " << actual_moves[i].ocena;
		if (actual_moves[i].ocena <= min)
		{
			min = actual_moves[i].ocena;
			finito = actual_moves[i];
		}
	}
	move(board, 'X', false, finito.poz_w, finito.poz_k, finito.ruch_w, finito.ruch_k);
}