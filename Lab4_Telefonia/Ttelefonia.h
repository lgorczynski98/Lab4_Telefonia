#pragma once

#include <iostream>
#include <sstream>
#include "Tkonto.h"
#include "Tsql.h"

class Ttelefonia
{
	Tsql sql;

public:

	void dodaj_uzytownika(std::string login, std::string haslo, std::string imie, std::string nazwisko, std::string nr_tel, int plec, int dostep);
	void usun_uzytkownika(std::string nr_tel);
	void wyswietl_uzytkownikow();
};