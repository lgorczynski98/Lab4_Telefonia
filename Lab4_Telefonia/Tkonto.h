#pragma once

#include <string>
#include <vector>

class Tkonto
{
public:
	
	enum Eplec{kobieta, mezczyzna};
	enum Edostep{uzytkownik, admin, brak};
	
private:

	std::string login;
	std::string haslo;
	std::string imie;
	std::string nazwisko;
	std::string nr_tel;
	Edostep dostep;
	Eplec plec;

public:

	Tkonto();
	Tkonto(std::string login, std::string haslo, std::string nr_tel, std::string imie, std::string nazwisko, Eplec plec, Edostep dostep);
	std::vector<std::string> do_wyswietlenia();
	int get_dostep();
	std::string getNr_tel();
};
