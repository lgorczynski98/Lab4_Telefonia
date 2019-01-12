#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <mysql.h>
#include <sstream>
#include <vector>
#include "Tkonto.h"

class Tsql
{
	MYSQL *connection;

public:

	Tsql();
	~Tsql();
	void wyswietl(std::function<std::string()>fun, std::vector<int>co_wypisac);
	void modyfikuj(std::function<std::string()>fun, std::string komunikat);
	std::string zwroc(std::function<std::string()>fun);
	bool login_haslo(std::string login, std::string haslo);
	Tkonto zwroc(std::string login, std::string haslo);
};