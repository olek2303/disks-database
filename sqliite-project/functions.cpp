#include "functions.hpp"

ostream& naglowek(ostream& b) {
	b << "+-----------------------------------------------------------------------------------------------------------------------------------------+" << endl;
	b << "|";
	b << setw(22);
	b << left << "ID" << "|";
	b << setw(22);
	b << left << "ARTIST" << "|";
	b << setw(22);
	b << left << "TITLE" << "|";
	b << setw(22);
	b << left << "PRICE_GET" << "|";
	b << setw(22);
	b << left << "PRICE_SELL" << "|";
	b << setw(22);
	b << left << "AMOUNT" << "|";
	b << endl;
	b << "+-----------------------------------------------------------------------------------------------------------------------------------------+" << endl;
	return b;
}

ostream& stopka(ostream& b) {
	b << "+-----------------------------------------------------------------------------------------------------------------------------------------+" << endl;
	return b;
}

ostream& operator<<(ostream& b, record& r) {
	record::iterator it = r.begin();
	while (it != r.end()) {
		b << "|";
		b << setw(22);
		//b << "| ";
		b << left << *it;
		it++;
	}
	b << "|";
	b << endl;
	return b;
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	cout << "\n";
	return 0;
}

int select_callback(void* p_data, int num_fields, char** p_fields, char** p_col_names) {
	records* all = static_cast<records*>(p_data);
	try {
		all->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) { return 1; }
	return 0;
}

void create_table(sqlite3* db, string name) {
	int r;
	char* err_msg;
	string sql = "CREATE TABLE ";
	sql += name;
	sql += "("
		"ID INT PRIMARY KEY     NOT NULL, "
		"ARTIST           TEXT    NOT NULL, "
		"TITLE          TEXT     NOT NULL, "
		"PRICE_GET            INT     NOT NULL, "
		"PRICE_SELL        INT     NOT NULL, "
		"AMOUNT         INT     NOT NULL);";
	r = sqlite3_exec(db, sql.c_str(), NULL, 0, &err_msg); //creating database
	if (r != SQLITE_OK) {
		cerr << "Error Create Table" << endl;
		sqlite3_free(err_msg);
	}
	else
		cout << "Table created Successfully" << endl;
}

void insert_to_table(sqlite3* db, int i, string a, string t, int pg, int ps, int am) {
	int exit = 0;
	char* err_msg;
	string kon_a, kon_t;
	kon_a += "'";
	kon_a += a;
	kon_a += "'";
	kon_t += "'";
	kon_t += t;
	kon_t += "'";
	string add = "insert into tab (ID, ARTIST, TITLE, PRICE_GET, PRICE_SELL, AMOUNT) values (";
	add += std::to_string(i);
	add += ", ";
	add += kon_a;
	add += ", ";
	add += kon_t;
	add += ", ";
	add += to_string(pg);
	add += ", ";
	add += to_string(ps);
	add += ", ";
	add += to_string(am);
	add += ")";
	cout << "ADD: " << add;
	exit = sqlite3_exec(db, add.c_str(), callback, 0, &err_msg);
	if (exit != SQLITE_OK) {
		cerr << "Error Adding Insert" << endl;
		sqlite3_free(err_msg);
	}
	else
		cout << "Insert made successfully" << endl;
}

records select_stmt(sqlite3* db, const char* stmt) {
	records all;
	char* err_msg;
	int ret = sqlite3_exec(db, stmt, select_callback, &all, &err_msg);
	if (ret != SQLITE_OK) {
		cerr << "Error in select statement " << stmt << "[" << err_msg << "]" << endl;
	}
	else {
		cerr << all.size() << "records returned. " << endl;
	}
	return all;
}

void sql_stmt(sqlite3* db, const char* stmt) {
	char* err_msg;
	int ret = sqlite3_exec(db, stmt, 0, 0, &err_msg);
	if (ret != SQLITE_OK) {
		cerr << "Error in select statement " << stmt << "[" << err_msg << "]" << endl;
	}
}

void pokaz_liste(records& all) {
	cout << naglowek;
	records::iterator it = all.begin();
	while (it != all.end()) {
		cout << *it;
		it++;
	}
	cout << stopka;
}

/*
void openandcos(sqlite3* db, const int STATEMENTS, const char* pSQL[], int rc, char* zErrMsg) {
	if (rc) {
		cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
	}
	else {
		cout << "Open database successfully\n\n";
	}

	pSQL[0] = "create table myTable (Artist varchar(30), Title varchar(30), Amount smallint, PriceGet varchar(30), PriceSell varchar(30))";
	pSQL[1] = "insert into myTable (Artist, Title, Amount, PriceGet, PriceSell) values ('RHCP', 'Californication', 5, '20.00', '32.30')";
	pSQL[2] = "insert into myTable (Artist, Title, Amount, PriceGet, PriceSell) values ('RHCP', 'ROTDC', 5, '20.00', '52.90')";
	pSQL[3] = "insert into myTable (Artist, Title, Amount, PriceGet, PriceSell) values ('RHCP', 'Unlimited love', 5, '20.00', '25.00')";
	pSQL[4] = "insert into myTable (Artist, Title, Amount, PriceGet, PriceSell) values ('RHCP', 'BSSM', 5, '20.00', '35.50')";
	pSQL[5] = "select * from myTable";
	pSQL[6] = "delete from myTable";
	pSQL[7] = "drop table myTable";

	for (int i = 0; i < STATEMENTS; i++) {
		rc = sqlite3_exec(db, pSQL[i], callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			cout << "SQL error: " << sqlite3_errmsg(db) << "\n";
			sqlite3_free(zErrMsg);
			break;
		}
	}
	sqlite3_close(db);
}
*/