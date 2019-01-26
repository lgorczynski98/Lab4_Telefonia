#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>

#include "Ttelefonia.h"
#include "Tsql.h"

using namespace std;

bool nr_good(std::string nr)
{
	if (nr.length() == 9)
	{
		for (auto x : nr)
		{
			if (x < '0' || x > '9')
				return false;
		}
		return true;
	}
	else
		return false;
}

void wahadlo()
{
	cout << "\n";
	char wzorek[25];
	int i = 0;
	bool press;
	while(1)
	{
		for (int k = 0; k < 24; k++)
			wzorek[k] = ' ';

		wzorek[24] = 0;

		int pozycja = 12 * sin(i / 20.0) + 12;
		wzorek[pozycja] = '*';

		cout << wzorek << "\r" << flush;
		i++;
		Sleep(15);
		short int keystate = GetKeyState(VK_RETURN);
		press = (keystate &= 0x1000) == 0x1000;
		if (press)
			break;
	}
	cout << endl;
}

void zadzwon(Tkonto uzytkownik, Ttelefonia &telefonia)
{
	string nr;
	cout << "Numer na ktory chcesz zadzwonic: ";
	cin >> nr;
	if (nr_good(nr))
	{
		cout << "Rozpoczynam rozmowe..." << endl;
		int id = telefonia.zadzwon(uzytkownik.getNr_tel(), nr);
		cout << "...Rozmowa w toku..." << endl;
		cout << "Wcisnij ENTER aby zakonczyc rozmowe";
		cin.ignore();
		wahadlo();
		getchar();
		telefonia.koniec_rozmowy(id);
		cout << "Rozmowa zakonczona" << endl;
	}
	else
		cout << "Wybrany numer jest niepoprawny";
}

void menu(Tkonto &uzytkownik)
{
	Ttelefonia telefonia;
	while (1)
	{
		cout << "Menu uzytkownik" << endl;
		cout << "1. Zadzwon" << endl;
		cout << "2. Historia polaczen" << endl;
		cout << "3. Wyloguj" << endl;

		int wybor = 0;
		cin >> wybor;
		switch (wybor)
		{
			case 1://dzwonienie
			{
				zadzwon(uzytkownik, telefonia);
				break;
			}
			case 2://historia polaczen
			{
				telefonia.wyswietl_historie_polaczen(uzytkownik.getNr_tel());
				break;
			}
			case 3://wyloguj
				return;
		}
		getchar();
		getchar();
	}
}

void menu_admin(Tkonto &uzytkownik)
{
	Ttelefonia telefonia;
	while (1)
	{
		cout << "Menu admin" << endl;
		cout << "1.  Zaloz konto admina" << endl;
		cout << "2.  Zaloz konto uzytkownika" << endl;
		cout << "3.  Usun uzytkownika" << endl;
		cout << "4.  Dodaj polaczenie do historii polaczen" << endl;
		cout << "5.  Zmodyfikuj polaczenie w historii polaczen" << endl;
		cout << "6.  Usun polaczenie z historii polaczen" << endl;
		cout << "7.  Wyswietl uzytkownikow" << endl;
		cout << "8.  Wyswietl historie polaczen" << endl;
		cout << "9.  Procent uzytkownikow" << endl;
		cout << "10. Skrajne czasy rozmow" << endl;
		cout << "11. Sredni czas rozmow" << endl;
		cout << "12. Zadzwon" << endl;
		cout << "13. Wyloguj" << endl;

		int wybor = 0;
		cin >> wybor;
		switch (wybor)
		{
			case 1://zaloz konto admina
			{
				string login, haslo, imie, nazwisko, nr_tel;
				int plec;
				cout << "Imie i nazwisko: ";
				cin >> imie >> nazwisko;
				cout << "Numer telefonu: ";
				cin >> nr_tel;
				cout << "Plec(0 - kobieta, 1 - mezczyzna): ";
				cin >> plec;
				cout << "Login: ";
				cin >> login;
				cout << "Haslo: ";
				cin >> haslo;
				telefonia.dodaj_uzytownika(login, haslo, imie, nazwisko, nr_tel, plec, 1);
				break;
			}
			case 2://zaloz konto uzytkownika
			{
				string login, haslo, imie, nazwisko, nr_tel;
				int plec;
				cout << "Imie i nazwisko: ";
				cin >> imie >> nazwisko;
				cout << "Numer telefonu: ";
				cin >> nr_tel;
				cout << "Plec(0 - kobieta, 1 - mezczyzna): ";
				cin >> plec;
				cout << "Login: ";
				cin >> login;
				cout << "Haslo: ";
				cin >> haslo;
				telefonia.dodaj_uzytownika(login, haslo, imie, nazwisko, nr_tel, plec, 0);
				break;
			}
			case 3://usun uzytkownika
			{
				string nr_tel;
				cout << "Numer telefonu: ";
				cin >> nr_tel;
				telefonia.usun_uzytkownika(nr_tel);
				break;
			}
			case 4://dodaj polaczenie do historii
			{
				string dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia;
				cout << "Numer z ktorego dzwoniono: ";
				cin >> dzwoniacy;
				cout << "Numer na ktory dzowniono: ";
				cin >> odbierajacy;
				cin.ignore();
				if (nr_good(dzwoniacy) && nr_good(odbierajacy))
				{
					cout << "Data rozpoczecia rozmowy: ";
					getline(cin, data_rozpoczecia);
					cout << "Data zakonczenia rozmowy: ";
					getline(cin, data_zakonczenia);
					telefonia.dodaj_do_historii(dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia);
				}
				else
					cout << "Jeden z podanych numerow jest niepoprawny" << endl;
				break;
			}
			case 5://modyfikuj polaczenie z historii
			{
				int id;
				string dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia;
				cout << "ID polaczenia ktore chcesz zodyfikowac: ";
				cin >> id;
				cout << "Numer z ktorego wykonano polaczenie: ";
				cin >> dzwoniacy;
				cout << "Numer na ktory wykonano polaczenie: ";
				cin >> odbierajacy;
				cin.ignore();
				if (nr_good(dzwoniacy) && nr_good(odbierajacy))
				{
					cout << "Data rozpoczecia rozmowy: ";
					getline(cin, data_rozpoczecia);
					cout << "Data zakonczenia rozmowy: ";
					getline(cin, data_zakonczenia);
					telefonia.modyfikuj_polaczenie(id, dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia);
				}
				else
					cout << "Jeden z podanych numerow jest niepoprawny" << endl;
				break;
			}
			case 6://usun polaczenie z historii
			{
				int id;
				cout << "ID polacznia ktore chcesz usunac: ";
				cin >> id;
				telefonia.usun_polaczenie(id);
				break;
			}
			case 7://wyswietl uzytkownika
			{
				telefonia.wyswietl_uzytkownikow();
				break;
			}
			case 8://wyswietl historie polaczen
			{
				telefonia.wyswietl_historie_polaczen();
				break;
			}
			case 9://procent plci uzytkownikow
			{
				telefonia.plcie();
				break;
			}
			case 10://skrajne czasy rozmow
			{
				telefonia.czasy_rozmow();
				break;
			}
			case 11://sredni czas rozmow
			{
				telefonia.sredni_czas_rozmow();
				break;
			}
			case 12://dzwonienie
			{
				zadzwon(uzytkownik, telefonia);
				break;
			}
			case 13:
				return;
		}
		getchar();
		getchar();
	}
}

int main()
{
	Tsql logowanie_sql;
	while (1)
	{
		bool logged = false;
		Tkonto uzytkownik;
		do
		{
			int wybor;
			cout << "1. Logowanie" << endl;
			cout << "2. Zamknij program" << endl;
			cin >> wybor;
			switch (wybor)
			{
				case 1:
				{
					string login, haslo;
					cout << "Login: ";
					cin >> login;
					cout << "Haslo: ";
					cin >> haslo;
					if (logowanie_sql.login_haslo(login, haslo))
					{
						uzytkownik = logowanie_sql.zwroc(login, haslo);
						if (uzytkownik.get_dostep() != 2)
						{
							logged = true;
							cout << "Logowanie pomyslne" << endl;
						}
					}
					if(!logged)
						cout << "Logowanie nie powiodlo sie!" << endl;
					getchar();
					getchar();
					break;
				}
				case 2:
					return 0;
			}
		} while (!logged);

		cout << "Zalogowany uzytkownik to: ";
		for (auto it : uzytkownik.do_wyswietlenia())
		{
			cout << it << " ";
		}
		cout << endl;

		if (uzytkownik.get_dostep())
			menu_admin(uzytkownik);
		else
			menu(uzytkownik);
	}
}
