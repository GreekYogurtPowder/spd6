#include "instancja.h"

using namespace std;

instancja::instancja() {
	long ziarno;

	cout << "Wprowadz ziarno losowania: ";
	cin >> ziarno;
	RandomNumberGenerator generator = RandomNumberGenerator(ziarno);

	cout << "Wprowadz ilosc zadan: ";
	cin >> ilosc_zadan;

	cout << "Wprowadz ilosc operacji/maszyn: ";
	cin >> ilosc_operacji;

	for (int i = 0; i < ilosc_zadan; i++) {
		lista_zadan.push_back(zadanie());
		lista_zadan[i].j = i + 1;

		for (int j = 0; j < ilosc_operacji; j++) {
			lista_zadan[i].p.push_back(generator.nextInt(1, 29));
			lista_zadan[i].sum_p += lista_zadan[i].p[j];
		}
	}

}

void instancja::wypiszTabele() {
	cout << endl << "j: [";
	for (int i = 0; i < ilosc_zadan; i++) {
		cout << lista_zadan[i].j;
		if (i == ilosc_zadan - 1) { //jesli ostatni element
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}

	cout << endl << "p: [";
	for (int i = 0; i < ilosc_zadan; i++) {
		cout << "[";
		for (int j = 0; j < ilosc_operacji; j++) {
			cout << lista_zadan[i].p[j];
			if (j != ilosc_operacji - 1) {
				cout << ", ";
			}
		}
		cout << "]";

		if (i == ilosc_zadan - 1) {
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}
}

vector<long> instancja::domyslnePi() {
	vector<long> pi;
	for (int i = 0; i < ilosc_zadan; i++) {
		pi.push_back(lista_zadan[i].j);
	}
	return pi;
}

void instancja::wypiszPi(vector<long> pi) {
	cout << "Pi: [";
	for (int i = 0; i < pi.size(); i++) {
		cout << pi[i];
		if (i == pi.size() - 1) {
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}
}

long instancja::funkcja_oceny(vector<long> pi) {
	vector<zadanie> posortowana_lista;
	vector<vector<long> > czas_C; //moment zakonczenia

	for (int i = 0; i < pi.size(); i++) {
		posortowana_lista.push_back(lista_zadan[pi[i] - 1]);
		czas_C.push_back(vector<long>());
	}

	for (int j = 0; j < ilosc_operacji; j++) {
		for (int i = 0; i < pi.size(); i++) {

			if (j == 0) {
				if (i == 0) {
					czas_C[i].push_back(posortowana_lista[i].p[j]);
				}
				else {
					czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
				}
			}
			else {
				if (i == 0) {
					czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
				}
				else {
					if (czas_C[i - 1][j] < czas_C[i][j - 1]) {
						czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
					}
					else {
						czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
					}
				}
			}
		}
	}

	return czas_C[pi.size() - 1][ilosc_operacji - 1]; // Cmax jest rowny czasowi zakonczenia ostatniej opracji ostatneigo zadania
}

void instancja::wypiszWyniki(vector<long> pi) {

	vector<zadanie> posortowana_lista;
	vector<vector<long> > czas_C; //moment zakonczenia
	vector<vector<long> > czas_S; //moment rozpoczecia

	for (int i = 0; i < ilosc_zadan; i++) {
		posortowana_lista.push_back(lista_zadan[pi[i] - 1]);
		czas_C.push_back(vector<long>());
		czas_S.push_back(vector<long>());
	}

	for (int j = 0; j < ilosc_operacji; j++) {
		for (int i = 0; i < pi.size(); i++) {

			if (j == 0) {
				if (i == 0) {
					czas_C[i].push_back(posortowana_lista[i].p[j]);
				}
				else {
					czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
				}
			}
			else {
				if (i == 0) {
					czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
				}
				else {
					if (czas_C[i - 1][j] < czas_C[i][j - 1]) {
						czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
					}
					else {
						czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
					}
				}
			}
		}
	}

	for (int i = 0; i < pi.size(); i++) {
		for (int j = 0; j < ilosc_operacji; j++) {
			czas_S[i].push_back(czas_C[i][j] - posortowana_lista[i].p[j]);
		}
	}

	cout << "S: [";
	for (int i = 0; i < pi.size(); i++) {
		cout << "[";
		for (int j = 0; j < ilosc_operacji; j++) {
			cout << czas_S[i][j];
			if (j != ilosc_operacji - 1) {
				cout << ", ";
			}
		}
		cout << "]";

		if (i == pi.size() - 1) {
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}

	cout << endl << "C: [";
	for (int i = 0; i < pi.size(); i++) {
		cout << "[";
		for (int j = 0; j < ilosc_operacji; j++) {
			cout << czas_C[i][j];
			if (j != ilosc_operacji - 1) {
				cout << ", ";
			}
		}
		cout << "]";

		if (i == pi.size() - 1) {
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}

	cout << endl << "Cmax: " << funkcja_oceny(pi) << endl;
}

vector<long> instancja::johnson() {

	vector<long> pi; // wektor z wynikowa kolejnoscia pi
	vector<zadanie> wektor_N; //wektor zadan nieuszeregowanych
	long l = 0;
	long k = ilosc_zadan - 1;

	for (int i = 0; i < ilosc_zadan; i++) { //wypelnienie wektora zadan nieuszeregowanych
		wektor_N.push_back(lista_zadan[i]);
		pi.push_back(0);
	}

	long wartosc_minimalna;
	long indeks_j_minimalnego_zadania;

	while (!wektor_N.empty()) {

		wartosc_minimalna = wektor_N[0].p[0];
		indeks_j_minimalnego_zadania = 0;

		for (int j = 0; j < wektor_N.size(); j++) { //znalezienie najmniejszej operacji z nieprzydzielonych zadan
			if (wektor_N[j].p[0] < wartosc_minimalna) {
				wartosc_minimalna = wektor_N[j].p[0];
				indeks_j_minimalnego_zadania = j;
			}

			if (wektor_N[j].p[ilosc_operacji - 1] < wartosc_minimalna) {
				wartosc_minimalna = wektor_N[j].p[ilosc_operacji - 1];
				indeks_j_minimalnego_zadania = j;
			}
		}

		if (wektor_N[indeks_j_minimalnego_zadania].p[0] < wektor_N[indeks_j_minimalnego_zadania].p[ilosc_operacji - 1]) {
			pi[l] = wektor_N[indeks_j_minimalnego_zadania].j;
			l++;
		}
		else {
			pi[k] = wektor_N[indeks_j_minimalnego_zadania].j;
			k--;
		}

		wektor_N.erase(wektor_N.begin() + indeks_j_minimalnego_zadania);

	}

	return pi;
}

vector<long> instancja::neh(bool czyWypisywac, int wersja) {
	// wersja 0 - bez modyfikacji
	// wersja 1 - Modyfikacja z usuwaniem zadania najczesciej pojawiajacego si� na �cie�sciezce krytycznej
	// wersja 2 - Modyfikacja z usuwaniem zadania z najwieksza suma czasu trwania operacji na sciezce krytycznej

	vector<long> pi; // wektor z wynikowa kolejnoscia pi
	vector<zadanie> wektor_W; //wektor zadan posortowanych malejaco wedlug sumy czasow trwania opracji

	for (int i = 0; i < ilosc_zadan; i++) { //wypelnienie wektora zadan nieuszeregowanych
		wektor_W.push_back(lista_zadan[i]);
	}

	int liczba_elementow = ilosc_zadan; //Sortowanie babelkowe

	while (liczba_elementow > 1) {

		for (int i = 0; i < liczba_elementow - 1; i++) {
			if (wektor_W[i].sum_p < wektor_W[i + 1].sum_p) {
				swap(wektor_W[i], wektor_W[i + 1]);
			}
		}

		liczba_elementow--;
	}

	if (czyWypisywac) {
		cout << endl << "W Pi: [";
		for (int i = 0; i < wektor_W.size(); i++) {
			cout << wektor_W[i].j;
			if (i == wektor_W.size() - 1) {
				cout << "]";
			}
			else {
				cout << ", ";
			}
		}

		cout << endl << "Sum P: [";
		for (int i = 0; i < wektor_W.size(); i++) {
			cout << wektor_W[i].sum_p;
			if (i == wektor_W.size() - 1) {
				cout << "]";
			}
			else {
				cout << ", ";
			}
		}
	}

	long ocena_pomocnicza;
	long najlepsza_ocena;
	int najlepsza_ocena_indeks;
	long usuniete_zadanie;

	if (czyWypisywac) {
		cout << endl;
	}

	for (int i = 0; i < ilosc_zadan; i++) {
		najlepsza_ocena = 2147483647;
		najlepsza_ocena_indeks = -1;

		for (int j = 0; j <= i; j++) {
			pi.insert(pi.begin() + j, wektor_W[i].j);
			ocena_pomocnicza = funkcja_oceny(pi);

			if (czyWypisywac) {
				cout << endl;
				wypiszPi(pi);
				cout << " Ocena: " << ocena_pomocnicza;
			}

			if (ocena_pomocnicza < najlepsza_ocena) {
				najlepsza_ocena = ocena_pomocnicza;
				najlepsza_ocena_indeks = j;
			}

			pi.erase(pi.begin() + j);
		}

		pi.insert(pi.begin() + najlepsza_ocena_indeks, wektor_W[i].j);

		if (czyWypisywac) {
			cout << endl << "Najlepsze ";
			wypiszPi(pi);
			cout << endl;
		}

		//II FAZA
		if (wersja != 0) {

			if (wersja == 1) {
				usuniete_zadanie = najwiekszaIloscOperacjiNaSciezce(pi, wektor_W[i].j);
			}

			if (wersja == 2) {
				usuniete_zadanie = najwiekszaSumaOperacjiNaSciezce(pi, wektor_W[i].j);
			}


			if (usuniete_zadanie != -1) {

				for (int j = 0; j < pi.size(); j++) {
					if (pi[j] == usuniete_zadanie) {
						pi.erase(pi.begin() + j);
						break;
					}
				}

				najlepsza_ocena = 2147483647;
				najlepsza_ocena_indeks = -1;

				for (int j = 0; j <= i; j++) {
					pi.insert(pi.begin() + j, usuniete_zadanie);
					ocena_pomocnicza = funkcja_oceny(pi);

					if (czyWypisywac) {
						cout << endl;
						wypiszPi(pi);
						cout << " Ocena: " << ocena_pomocnicza;
					}

					if (ocena_pomocnicza < najlepsza_ocena) {
						najlepsza_ocena = ocena_pomocnicza;
						najlepsza_ocena_indeks = j;
					}

					pi.erase(pi.begin() + j);
				}

				pi.insert(pi.begin() + najlepsza_ocena_indeks, usuniete_zadanie);

				if (czyWypisywac) {
					cout << endl << "Najlepsze ";
					wypiszPi(pi);
					cout << endl;
				}
			}
		}
	}

	return pi;
}

long instancja::najwiekszaIloscOperacjiNaSciezce(vector<long> pi, long pomijane_zadanie) {

	vector<zadanie> posortowana_lista;
	vector<vector<long> > czas_C; //moment zakonczenia
	vector<long> numer_zadania_operacji; //numery zadan do ktorych naleza poszczegolne czasy zakonczenia

	for (int i = 0; i < pi.size(); i++) {
		posortowana_lista.push_back(lista_zadan[pi[i] - 1]);
		czas_C.push_back(vector<long>());
	}

	for (int j = 0; j < ilosc_operacji; j++) {
		for (int i = 0; i < pi.size(); i++) {

			if (j == 0) {
				if (i == 0) {
					czas_C[i].push_back(posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
				else {
					czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
			}
			else {
				if (i == 0) {
					czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
				else {
					if (czas_C[i - 1][j] < czas_C[i][j - 1]) {
						czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
						numer_zadania_operacji.push_back(i);
					}
					else {
						czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
						numer_zadania_operacji.push_back(i);
					}
				}
			}
		}
	}

	vector<long> sciezka_krytyczna;

	long j_helper = pi.size() - 1;
	long m_helper = ilosc_operacji - 1;
	long cmaxHelper = czas_C[j_helper][m_helper];

	sciezka_krytyczna.push_back(j_helper);
	cmaxHelper -= posortowana_lista[j_helper].p[m_helper];

	while (cmaxHelper > 0) {
		if (j_helper > 0 && czas_C[j_helper - 1][m_helper] == cmaxHelper) {
			j_helper = j_helper - 1;
		}
		else {
			m_helper = m_helper - 1;
		}

		sciezka_krytyczna.push_back(j_helper);
		cmaxHelper -= posortowana_lista[j_helper].p[m_helper];
	}

	long najczestsze_zadanie = -1;
	long ilosc_wystapien_najczestszego_zdania = -1;
	long licznik_wystapien;

	for (int i = 0; i < pi.size(); i++) {
		licznik_wystapien = 0;

		for (int j = 0; j < sciezka_krytyczna.size(); j++) {
			if (sciezka_krytyczna[j] == pi[i]) {
				licznik_wystapien++;
			}
		}

		if (licznik_wystapien > ilosc_wystapien_najczestszego_zdania) {
			if (pi[i] != pomijane_zadanie) {
				ilosc_wystapien_najczestszego_zdania = licznik_wystapien;
				najczestsze_zadanie = pi[i];
			}
		}
	}

	return najczestsze_zadanie;
}

long instancja::najwiekszaSumaOperacjiNaSciezce(vector<long> pi, long pomijane_zadanie) {

	vector<zadanie> posortowana_lista;
	vector<vector<long> > czas_C; //moment zakonczenia
	vector<long> numer_zadania_operacji; //numery zadan do ktorych naleza poszczegolne czasy zakonczenia

	for (int i = 0; i < pi.size(); i++) {
		posortowana_lista.push_back(lista_zadan[pi[i] - 1]);
		czas_C.push_back(vector<long>());
	}

	for (int j = 0; j < ilosc_operacji; j++) {
		for (int i = 0; i < pi.size(); i++) {

			if (j == 0) {
				if (i == 0) {
					czas_C[i].push_back(posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
				else {
					czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
			}
			else {
				if (i == 0) {
					czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
					numer_zadania_operacji.push_back(i);
				}
				else {
					if (czas_C[i - 1][j] < czas_C[i][j - 1]) {
						czas_C[i].push_back(czas_C[i][j - 1] + posortowana_lista[i].p[j]);
						numer_zadania_operacji.push_back(i);
					}
					else {
						czas_C[i].push_back(czas_C[i - 1][j] + posortowana_lista[i].p[j]);
						numer_zadania_operacji.push_back(i);
					}
				}
			}
		}
	}

	vector<long> sciezka_krytyczna;
	vector<long> czasy_trwania_operacji_na_sciezce;

	long j_helper = pi.size() - 1;
	long m_helper = ilosc_operacji - 1;
	long cmaxHelper = czas_C[j_helper][m_helper];

	sciezka_krytyczna.push_back(j_helper);
	czasy_trwania_operacji_na_sciezce.push_back(posortowana_lista[j_helper].p[m_helper]);
	cmaxHelper -= posortowana_lista[j_helper].p[m_helper];

	while (cmaxHelper > 0) {
		if (j_helper > 0 && czas_C[j_helper - 1][m_helper] == cmaxHelper) {
			j_helper = j_helper - 1;
		}
		else {
			m_helper = m_helper - 1;
		}

		sciezka_krytyczna.push_back(j_helper);
		czasy_trwania_operacji_na_sciezce.push_back(posortowana_lista[j_helper].p[m_helper]);
		cmaxHelper -= posortowana_lista[j_helper].p[m_helper];
	}

	long zadanie_z_najwieksza_suma = -1;
	long najwieksza_suma = -1;
	long licznik_sumy;

	for (int i = 0; i < pi.size(); i++) {
		licznik_sumy = 0;

		for (int j = 0; j < sciezka_krytyczna.size(); j++) {
			if (sciezka_krytyczna[j] == pi[i]) {
				licznik_sumy += czasy_trwania_operacji_na_sciezce[j];
			}
		}

		if (licznik_sumy > najwieksza_suma) {
			if (pi[i] != pomijane_zadanie) {
				najwieksza_suma = licznik_sumy;
				zadanie_z_najwieksza_suma = pi[i];
			}
		}
	}

	return zadanie_z_najwieksza_suma;
}

vector<long> instancja::wyzarzanie(double temperatura_poczatkowa, double alfa, int ilosc_epok) {

	double temperatura_aktualna = temperatura_poczatkowa; //ustawienie temperatury poczatkowej
	double temperatura_koncowa = 10; //ustawienie temperatury koncowej

	vector<long> najlepsze_pi; //wektor z najlepsza znaleziona kolejnoscia pi po przejsciu calego algorytmu
	vector<long> nowe_pi; //wektor z nowo znalezionym rozwiazaniem
	vector<long> aktualne_pi; //wektor z rozwiazaniem znalezionym w poprzednim obiegu petli

	for (int i = 0; i < ilosc_zadan; i++) { // inicjalizacja rozwiazania poczatkowego za pomoc permutacji naturalnej
		najlepsze_pi.push_back(lista_zadan[i].j);
		nowe_pi.push_back(lista_zadan[i].j);
		aktualne_pi.push_back(lista_zadan[i].j);
	}

	long cMax_najlepsze_pi = funkcja_oceny(najlepsze_pi); //inicjalizacja zmiennych przechowujacych wartosc cMax rozwiazan
	long cMax_nowe_pi = cMax_najlepsze_pi;
	long cMax_aktualne_pi = cMax_najlepsze_pi;

	srand(time(NULL)); //inicjalizacja ziarna dla generatora liczb losowych

	while (temperatura_aktualna > temperatura_koncowa) { //dopoki temperatura nie spadnie ponizej temperatury koncowej

		for (int k = 0; k < ilosc_epok; k++) { //dla kazdej temperatury wykonywanej jest X epok

			swap(nowe_pi[rand() % (ilosc_zadan - 1) + 0], nowe_pi[rand() % (ilosc_zadan - 1) + 0]); //wykonanie losowego ruchu (1) zamien 
			cMax_nowe_pi = funkcja_oceny(nowe_pi); //wyliczenie wartosci cMax dla nowego PI

			if (cMax_nowe_pi > cMax_aktualne_pi) { //jezeli nowe rozwiazanie jest gorsze od poprzedniego
				double p = pow(exp(1), ((cMax_aktualne_pi - cMax_nowe_pi) / temperatura_aktualna)); //wyliczenie prawdopodbienstwa, ze poprzednie rozwiazanie zostanie zastapione gorszym, ale nowym
				double r = (rand() % 1000) / 1000; //wylosowanie liczby z zakresu 0 - 1
				if (r >= p) {
					for (int i = 0; i < ilosc_zadan; i++) { //jezeli  losowanie sie nie powiedzie to gorsze pi nie zastapi lepszego
						nowe_pi[i] = aktualne_pi[i];
					}
				}
			}

			for (int i = 0; i < ilosc_zadan; i++) { //nowe Pi zastepuje poprzednie
				aktualne_pi[i] = nowe_pi[i];
			}

			cMax_aktualne_pi = funkcja_oceny(aktualne_pi); //wyliczenie wartosci cMax dla aktualnego PI

			if (cMax_najlepsze_pi > cMax_aktualne_pi) { //jezeli aktualne PI jest lepsze to zastepuje najlepsze do tej pory znalezione

				for (int i = 0; i < ilosc_zadan; i++) {
					najlepsze_pi[i] = aktualne_pi[i];
				}

				cMax_najlepsze_pi = cMax_aktualne_pi;
			}

		}

		temperatura_aktualna = temperatura_aktualna * alfa; //ochlodzenie temperatury przez pomnozenie jej razy alfa. Alfa musi by� mniejsza od 1.
	}

	return najlepsze_pi;
}

vector<long> instancja::przeszukiwanie(int itLimit, int kadencja) {

	vector<long> najlepsze_pi; //wektor z najlepsza znaleziona kolejnoscia pi po przejsciu calego algorytmu
	vector<long> nowe_pi; //wektor z nowo znalezionym rozwiazaniem
	vector<long> aktualne_pi; //wektor z rozwiazaniem znalezionym w poprzednim obiegu petli

	for (int i = 0; i < ilosc_zadan; i++) { //inicjalizacja rozwiazania poczatkowego za pomoc permutacji naturalnej
		najlepsze_pi.push_back(lista_zadan[i].j);
		nowe_pi.push_back(lista_zadan[i].j);
		aktualne_pi.push_back(lista_zadan[i].j);
	}

	long cMax_najlepsze_pi = funkcja_oceny(najlepsze_pi); //inicjalizacja zmiennych przechowujacych wartosc cMax rozwiazan
	long cMax_nowe_pi = cMax_najlepsze_pi;
	long cMax_aktualne_pi = cMax_najlepsze_pi;

	long cMax_iteracji;
	int best_j;
	int best_k;

	//int lista_tabu[ilosc_zadan][ilosc_zadan];

	vector<vector<int> > lista_tabu;

	for (int i = 0; i < ilosc_zadan; i++) {
		lista_tabu.push_back(vector<int>());
		for (int j = 0; j < ilosc_zadan; j++) {
			lista_tabu[i].push_back(0); //wypelnienie tablicy tabu zerami
		}
	}

	for (int it = 1; it < itLimit; it++) {

		cMax_iteracji = 2147483647; //inicjalizacja maksymalnej wartosci longa jako najlepsza ocene na poczatek iteracji

		for (int j = 0; j < ilosc_zadan - 1; j++) {
			for (int k = j + 1; k < ilosc_zadan; k++) {
				if (lista_tabu[j][k] < it) { //ruch mozna wykonac tylko jezeli minal czas jego kadencji na liscie tabu

					for (int i = 0; i < ilosc_zadan; i++) {
						nowe_pi[i] = aktualne_pi[i];
					}

					swap(nowe_pi[j], nowe_pi[k]); //wykonanie ruchu zamiany
					cMax_nowe_pi = funkcja_oceny(nowe_pi); //wyliczenie wartosci cMax dla nowego PI

					if (cMax_nowe_pi < cMax_iteracji) { //jezeli nowe rozwiazanie jest najlepszym w tej iteracji to
						cMax_iteracji = cMax_nowe_pi; //zapisz wynik
						best_j = j; //i indeksy zamienionych zadan
						best_k = k;
					}
				}
			}
		}

		swap(aktualne_pi[best_j], aktualne_pi[best_k]); //aktualne rozwiazanie zostaje zastapione najlepszym znalezionym podczas tej iteracji
		lista_tabu[best_j][best_k] = it + kadencja; //kadencja wykonanego ruchu zostaje wpisana do listy tabu
		cMax_aktualne_pi = funkcja_oceny(aktualne_pi); //wyliczenie wartosci cMax dla aktualnego PI

		if (cMax_najlepsze_pi > cMax_aktualne_pi) { //jezeli aktualne PI jest lepsze to zastepuje najlepsze do tej pory znalezione

			for (int i = 0; i < ilosc_zadan; i++) {
				najlepsze_pi[i] = aktualne_pi[i];
			}

			cMax_najlepsze_pi = cMax_aktualne_pi;
		}
	}

	return najlepsze_pi;
}