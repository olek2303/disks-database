#define _CRT_SECURE_NO_WARNINGS
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
	int pz = 0;
	int exit = sqlite3_open("disks.db", &db);
	records all;
	showMenu();
	cout << "Podaj liczbe od 0 do 5: ";
	while(scanf("%d", &pz) != 0 || getchar() != '\n') {
		switch(pz) {
		case 1:
			all = select_stmt(db, "SELECT * FROM tab");
			pokaz_liste(all);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			buyDisk(db);
			break;
		default:
			pz = 0;
			break;
		}
		system("pause");
		system("cls");
		if (pz == 0) {
			cout << "Koncze program." << endl;
			break;
		}
		showMenu();
	}

	sqlite3_close(db);



	return 0;
}


