#include <iostream>
#include <vector>

#include "Ttelefonia.h"
#include "Tsql.h"

using namespace std;

void menu_uzytkownik()
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
			case 1:
			{

				break;
			}
			case 2:
			{

				break;
			}
			case 3:
				return;
		}
	}
}

void menu_admin()
{
	Ttelefonia telefonia;
	while (1)
	{
		cout << "Menu admin" << endl;
		cout << "1. Zaloz konto admina" << endl;
		cout << "2. Zaloz konto uzytkownika" << endl;
		cout << "3. Usun uzytkownika" << endl;
		cout << "4. Wyswietl uzytkownikow" << endl;
		cout << "5. Wyswietl historie polaczen" << endl;
		cout << "6. Wyloguj" << endl;

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
			case 4://wyswietl uzytkownika
			{
				telefonia.wyswietl_uzytkownikow();
				break;
			}
			case 5://wyswietl historie polaczen
			{
				break;
			}
			case 6:
				return;
		}
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
						logged = true;
				}
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
			menu_admin();
		else
			menu_uzytkownik();
	}
}
