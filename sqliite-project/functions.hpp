#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include "./SQLite/sqlite3.h"

using namespace std;

typedef vector<string> record;
typedef vector<vector<string>> records;

void showMenu();
ostream& naglowek(ostream& b);
ostream& stopka(ostream& b);
ostream& operator<<(ostream& b, record& r);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
int select_callback(void* p_data, int num_fields, char** p_fields, char** p_col_names);
void create_table(sqlite3* db, string name);
void insert_to_table(sqlite3* db, int i, string a, string t, int pg, int ps, int am);
records select_stmt(sqlite3* db, const char* stmt);
void sql_stmt(sqlite3* db, const char* stmt);
void pokaz_liste(records& r);
void buyDisk(sqlite3* db);