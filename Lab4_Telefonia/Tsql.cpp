#include "Tsql.h"

typedef MYSQL_ROW rzad;
typedef MYSQL_RES* rezultat;

using namespace std;

Tsql::Tsql()
{
	this->connection = mysql_init(0);
	connection = mysql_real_connect(connection, "127.0.0.1", "root", "", "telefonia", 3306, NULL, 0);
	if (connection)
		cout << "Polaczono z baza danych" << endl;
	else
	{
		cout << "Blad podczas laczenia z baza danych" << endl;
		exit(0);
	}
}

Tsql::~Tsql()
{
	mysql_close(connection);
}

void Tsql::wyswietl(function<string()>fun, vector<int>co_wypisac)
{
	rzad row;
	rezultat res;
	int qstate = 0;
	string query = fun();
	const char *q = query.c_str();
	qstate = mysql_query(connection, q);
	if (!qstate)
	{
		res = mysql_store_result(connection);
		while (row = mysql_fetch_row(res))
		{
			//cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << endl;
			int j = -1;
			for (int i = 0; i < co_wypisac.size(); i++)
			{
				j = co_wypisac[i];
				cout << row[j] << " ";
			}
			cout << endl;
		}
	}
	else
		cout << "Blad podczas wyswietlania" << endl;
}

void Tsql::modyfikuj(function<string()>fun, string komunikat)
{
	int qstate = 0;
	string query = fun();
	const char *q = query.c_str();
	qstate = mysql_query(connection, q);
	if (!qstate)
	{
		cout << komunikat << " - pomyslne" << endl;
	}
	else
		cout << komunikat << " - niepowodzenie!" << endl;
}

string Tsql::zwroc(function<string()>fun)
{
	rzad row;
	rezultat res;
	int qstate = 0;
	string query = fun();
	const char *q = query.c_str();
	qstate = mysql_query(connection, q);
	if (!qstate)
	{
		res = mysql_store_result(connection);
		if (row = mysql_fetch_row(res))
		{
			return row[0];
		}
		return "";
	}
	else
	{
		cout << "Blad podczas zwracania" << endl;
		return "";
	}
}

bool Tsql::login_haslo(string login, string haslo)
{
	rzad row;
	rezultat res;
	int qstate = 0;
	stringstream ss;
	ss << "SELECT count(*) FROM uzytkownicy WHERE login = '" << login << "' AND haslo = '" << haslo << "'";
	string query = ss.str();
	const char *q = query.c_str();
	qstate = mysql_query(connection, q);
	if (!qstate)
	{
		res = mysql_store_result(connection);
		if (row = mysql_fetch_row(res))
		{
			stringstream s;
			s << row[0];
			int count = 0;
			s >> count;
			if (count)
				return true;
			else
				return false;
		}
		return false;
	}
	else
	{
		cout << "Blad podczas sprawdzania loginu i hasla" << endl;
		return false;
	}
}

Tkonto Tsql::zwroc(string login, string haslo)
{
	rzad row;
	rezultat res;
	int qstate = 0;
	stringstream ss;
	ss << "SELECT * FROM uzytkownicy WHERE login = '" << login << "' AND haslo = '" << haslo << "'";
	string query = ss.str();
	const char *q = query.c_str();
	qstate = mysql_query(connection, q);
	if (!qstate)
	{
		res = mysql_store_result(connection);
		while (row = mysql_fetch_row(res))
		{
			int plec;
			int dostep;
			stringstream s;
			s << row[5] << " " << row[6];
			s >> plec >> dostep;
			return Tkonto(row[0], row[1], row[4], row[2], row[3], Tkonto::Eplec(plec), Tkonto::Edostep(dostep));
		}
		return Tkonto();
	}
	else
	{
		cout << "Blad podczas uzyskiwania uzytkownika" << endl;
		return Tkonto();
	}
}