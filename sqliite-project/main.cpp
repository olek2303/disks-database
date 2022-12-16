#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "./SQLite/sqlite3.h"
#include "functions.hpp"

using namespace std;

sqlite3* db;
typedef vector<string> record;
typedef vector<vector<string>> records;

int main() {
	int id, il, c1, c2;
	string art, tyt;
	cout << "Podaj ID: ";
	cin >> id;
	cout << "Podaj artyste: ";
	cin >> art;
	cout << "Podaj tytul: ";
	cin >> tyt;
	cout << "Podaj cena1: ";
	cin >> c1;
	cout << "Podaj cena2: ";
	cin >> c2;
	cout << "Podaj ilosc: ";
	cin >> il;
	int exit = sqlite3_open("disks.db", &db);
	insert_to_table(db,id, art, tyt, c1, c2, il);
	records all = select_stmt(db, "SELECT * FROM tab");
	sqlite3_close(db);

	pokaz_liste(all);

	return 0;
}


