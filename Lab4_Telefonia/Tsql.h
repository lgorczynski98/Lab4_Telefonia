#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <mysql.h>
#include <sstream>
#include <vector>

class Tsql
{
	MYSQL *connection;

public:

	Tsql();
	~Tsql();
	void wyswietl(std::function<std::string()>fun, std::vector<int>co_wypisac);
};