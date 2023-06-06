#include <iostream>
#include <vector>  
#include <cmath>
#include "checkers.h"

using namespace std;

/*
DZIALANIE PROGRAMU
program oblicza wszytskie warianty ruchow i dokonuje ich oceny w funkcji generate_moves
potem z najnizszych ocen w gore sa wyciagane odpowiednio najlepsze wartosci
best line wybiera najnizsza ocene z juz zuzpelnionych wartosci ocen

Zasady: bicie nie jest obowiazkowe, dozwolone tylko jedno bicie w jednym ruchu,
damka moze zrobic wiele bic ale tylko w jednej linii gdy pionki sa przdzielone przerwa..
*/




int main()
{
	checkers gra_1;
	cout << "1 - gra z czlowiekiem\n2 - gra z komputerem\nwybor: ";
	int game{ 0 };
	cin >> game;
	switch (game)
	{
	case 1:
		while (true)
		{
			gra_1.show(gra_1.bierki);
			cout << endl << "Ocena: " << gra_1.evaluate(gra_1.bierki);   // dodatnie dla O, ujemne dla X
			gra_1.move(gra_1.bierki, 'O', true, 0, 0, 0, 0);
			gra_1.show(gra_1.bierki);
			cout << endl << "Ocena: " << gra_1.evaluate(gra_1.bierki);
			gra_1.move(gra_1.bierki, 'X', true, 0, 0, 0, 0);
		}
		break;
	case 2:
		while (true) 
		{
			gra_1.show(gra_1.bierki);
			gra_1.move(gra_1.bierki, 'O', true, 0, 0, 0, 0);
			gra_1.show(gra_1.bierki);
			gra_1.generate_moves(gra_1.bierki, 5, 'X', gra_1.all_moves);
			cout << "\n1";
			gra_1.evaluate_tree(gra_1.all_moves);
			cout << "\n2";
			gra_1.best_line(gra_1.bierki, gra_1.all_moves);
			cout << "\n3";
			gra_1.all_moves.clear();
		}
		break;

	default:

		return 0;
	}
	
	
}