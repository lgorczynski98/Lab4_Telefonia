#include "Ttelefonia.h"

using namespace std;

void Ttelefonia::dodaj_uzytownika(string login, string haslo, string imie, string nazwisko, string nr_tel, int plec, int dostep)
{
	stringstream ss;
	sql.modyfikuj([&ss, login, haslo, imie, nazwisko, nr_tel, plec, dostep]() {ss << "INSERT INTO uzytkownicy(login, haslo, imie, nazwisko, nr_tel, plec, dostep) VALUES('" << login << "', '" << haslo << "', '" << imie << "', '" << nazwisko << "', '" << nr_tel << "', '" << plec << "', '" << dostep << "')"; return ss.str(); }, "Dodawanie uzytkownika");
}

void Ttelefonia::usun_uzytkownika(std::string nr_tel)
{
	stringstream ss;
	sql.modyfikuj([&ss, nr_tel]() {ss << "DELETE FROM uzytkownicy WHERE nr_tel = " << nr_tel; return ss.str(); }, "Usuwanie uzytkownika");
}

void Ttelefonia::wyswietl_uzytkownikow()
{
	stringstream ss;
	sql.wyswietl([&ss]() {ss << "SELECT * FROM uzytkownicy"; return ss.str(); }, vector<int>{0, 1, 2, 3});
}