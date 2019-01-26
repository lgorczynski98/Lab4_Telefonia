#include "Tkonto.h"

using namespace std;

Tkonto::Tkonto()
{
	this->login = "";
	this->haslo = "";
	this->nr_tel = "";
	this->imie = "";
	this->nazwisko = "";
	this->plec = Tkonto::kobieta;
	this->dostep = Tkonto::brak;
}

Tkonto::Tkonto(string login, string haslo, string nr_tel, string imie, string nazwisko, Tkonto::Eplec plec, Tkonto::Edostep dostep)
{
	this->login = login;
	this->haslo = haslo;
	this->nr_tel = nr_tel;
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->plec = plec;
	this->dostep = dostep;
}

vector<string> Tkonto::do_wyswietlenia()
{
	vector<string> wypis;
	wypis.push_back(nr_tel);
	wypis.push_back(imie);
	wypis.push_back(nazwisko);
	if (plec == 0)
		wypis.push_back("kobieta");
	else
		wypis.push_back("mezczyzna");
	return wypis;
}

int Tkonto::get_dostep()
{
	return this->dostep;
}