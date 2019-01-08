#include <iostream>
#include <vector>

#include "Tsql.h"

using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	cout << "Program after commit" << endl;

	Tsql testowy;
	stringstream ss;
	auto lambda = [&ss]() 
	{
		ss << "SELECT * FROM uzytkownicy";
		return ss.str();
	};
	vector<int>co_wypisac{ 0,1,2 };

	testowy.wyswietl(lambda, co_wypisac);

	getchar();
	getchar();
	return 0;
}