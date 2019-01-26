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
	void wyswietl_historie_polaczen();
	void wyswietl_historie_polaczen(std::string nr_tel);
	int zadzwon(std::string skad, std::string dokad);
	void koniec_rozmowy(int id);
	void dodaj_do_historii(std::string dzwoniacy, std::string odbierajacy, std::string data_rozpoczecia, std::string data_zakonczenia);
	void plcie();
	void czasy_rozmow();
	void sredni_czas_rozmow();
	void modyfikuj_polaczenie(int id, std::string dzwoniacy, std::string odbierajacy, std::string data_rozpoczecia, std::string data_zakonczenia);
	void usun_polaczenie(int id);
};