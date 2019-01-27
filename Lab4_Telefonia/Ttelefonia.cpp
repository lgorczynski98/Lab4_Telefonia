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
	sql.wyswietl([&ss]() {ss << "SELECT * FROM uzytkownicy"; return ss.str(); }, vector<int>{0, 2, 3, 4, 5, 6});
}

void Ttelefonia::wyswietl_historie_polaczen()
{
	stringstream ss;
	sql.wyswietl([&ss]() {ss << "SELECT * FROM historia_polaczen"; return ss.str(); }, vector<int>{0, 1, 2, 3, 4});
}

void Ttelefonia::wyswietl_historie_polaczen(string nr_tel)
{
	stringstream ss;
	sql.wyswietl([&ss, nr_tel]() {ss << "SELECT * FROM historia_polaczen WHERE dzwoniacy = '" << nr_tel << "' OR odbierajacy = " << nr_tel ; return ss.str(); }, vector<int>{ 0, 1, 2, 3, 4});
}

int Ttelefonia::zadzwon(string skad, string dokad)
{
	stringstream ss;
	string zwrot = sql.zwroc([&ss]() {ss << "SELECT max(id_polaczenia) FROM historia_polaczen"; return ss.str(); });
	int id = -1;
	ss.clear();
	ss.str("");
	ss << zwrot;
	ss >> id;
	id++;
	ss.clear();
	ss.str("");
	sql.modyfikuj([&ss, id, skad, dokad]() {ss << "INSERT INTO historia_polaczen(id_polaczenia, dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia) VALUES('" << id << "', '" << skad << "', '" << dokad << "', CURRENT_TIME(), CURRENT_TIME())"; return ss.str(); }, "Zadzwoniono");
	return id;
}

void Ttelefonia::koniec_rozmowy(int id)
{
	stringstream ss;
	sql.modyfikuj([&ss, id]() {ss << "UPDATE historia_polaczen SET data_zakonczenia = CURRENT_TIME() WHERE id_polaczenia = " << id; return ss.str(); }, "Rozlaczono");
}

void Ttelefonia::dodaj_do_historii(string dzwoniacy, string odbierajacy, string data_rozpoczecia, string data_zakonczenia)
{
	stringstream ss;
	string zwrot = sql.zwroc([&ss]() {ss << "SELECT max(id_polaczenia) FROM historia_polaczen"; return ss.str(); });
	int id = -1;
	ss.clear();
	ss.str("");
	ss << zwrot;
	ss >> id;
	id++;
	ss.clear();
	ss.str("");
	sql.modyfikuj([&ss, id, dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia]() {ss << "INSERT INTO historia_polaczen(id_polaczenia, dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia) VALUES('" << id << "', '" << dzwoniacy << "', '" << odbierajacy << "', '" << data_rozpoczecia << "', '" << data_zakonczenia << "')"; return ss.str(); }, "Dodawania do hisotrii");
}

void Ttelefonia::plcie()
{
	stringstream ss;
	vector<string> plcie = sql.zwroc_wektor([&ss]() {ss << "SELECT plec FROM uzytkownicy"; return ss.str(); });
	if (plcie.size() == 0)
	{
		cout << "Blad podczas odczytu plci" << endl;
		return;
	}
	int uzytkownicy = plcie.size();
	int kobiety = 0, mezczyzni = 0;
	for (auto it : plcie)
	{
		if (it == "0")
			kobiety++;
		else if (it == "1")
			mezczyzni++;
	}
	//float procent_kobiet = (float(kobiety) / float(uzytkownicy)) * 100.0;
	float procent_kobiet = (static_cast<float>(kobiety) / static_cast<float>(uzytkownicy)) * 100.0;
	float procent_mezczyzn = 100.0 - procent_kobiet;
	cout << "Uzytkownikow lacznie: " << uzytkownicy << endl;
	cout << "Kobiety: " << kobiety << endl;
	cout << "Mezczyzni: " << mezczyzni << endl;
	cout << "Kobiety stanowia " << procent_kobiet << "% wszystkich uzytkownikow" << endl;
	cout << "Mezczyzni stanowia " << procent_mezczyzn << "% wszystkich uzytkownikow" << endl;
}

void Ttelefonia::czasy_rozmow()
{
	stringstream ss;
	string najdluzsza = sql.zwroc([&ss]() {ss << "SELECT TIMEDIFF ( data_zakonczenia , data_rozpoczecia ) as roznica FROM historia_polaczen ORDER BY roznica DESC"; return ss.str(); });
	cout << "Najdluzsza zarejestrowana rozmowa trwala: " << najdluzsza << endl;
	ss.clear();
	ss.str("");

	string najkrotsza = sql.zwroc([&ss]() {ss << "SELECT TIMEDIFF ( data_zakonczenia , data_rozpoczecia ) as roznica FROM historia_polaczen ORDER BY roznica ASC "; return ss.str(); });
	cout << "Najkrotsza zarejestrowana rozmowa trwala: " << najkrotsza << endl;
}

void Ttelefonia::sredni_czas_rozmow()
{
	stringstream ss;
	string srednia = sql.zwroc([&ss]() {ss << "SELECT SEC_TO_TIME(AVG(360 * HOUR(TIMEDIFF(data_zakonczenia, data_rozpoczecia)) + 60 * MINUTE(TIMEDIFF(data_zakonczenia, data_rozpoczecia)) + SECOND(TIMEDIFF(data_zakonczenia, data_rozpoczecia)))) from historia_polaczen"; return ss.str(); });
	cout << "Sredni czas zarejestrowanych rozmow: ";
	for (auto c : srednia)
	{
		if (c == '.')
			break;
		cout << c;
	}
	cout << endl;

}

void Ttelefonia::modyfikuj_polaczenie(int id, string dzwoniacy, string odbierajacy, string data_rozpoczecia, string data_zakonczenia)
{
	stringstream ss;
	sql.modyfikuj([&ss, id, dzwoniacy, odbierajacy, data_rozpoczecia, data_zakonczenia]() {ss << "UPDATE historia_polaczen SET dzwoniacy = '" << dzwoniacy << "', odbierajacy = '" << odbierajacy << "', data_rozpoczecia = '" << data_rozpoczecia << "', data_zakonczenia = '" << data_zakonczenia << "' WHERE id_polaczenia = '" << id << "'"; return ss.str(); }, "Modyfikowanie polaczenia w historii");
}

void Ttelefonia::usun_polaczenie(int id)
{
	stringstream ss;
	sql.modyfikuj([&ss, id]() {ss << "DELETE FROM historia_polaczen WHERE id_polaczenia = " << id; return ss.str(); }, "Usuwanie polaczenia z historii");
}

void Ttelefonia::zmien_dane_logowania(string login, string haslo, string numer)
{
	stringstream ss;
	sql.modyfikuj([&ss, login, haslo, numer]() {ss << "UPDATE uzytkownicy SET login = '" << login << "', haslo = '" << haslo << "' WHERE nr_tel = '" << numer << "'"; return ss.str(); }, "Zmiana danych logowania");
}

void Ttelefonia::zmien_dane_osobowe(string imie, string nazwisko, string numer)
{
	stringstream ss;
	sql.modyfikuj([&ss, imie, nazwisko, numer]() {ss << "UPDATE uzytkownicy SET imie = '" << imie << "', nazwisko = '" << nazwisko << "' WHERE nr_tel = '" << numer << "'"; return ss.str(); }, "Zmiana danych osobowych");
}