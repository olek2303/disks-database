#pragma once 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<string> record;
typedef vector<vector<string>> records;
typedef vector<vector<string>> vecString;

class Disks : public vecString { 
public:
	Disks() {};
	Disks(vecString s) {};
	~Disks() {};
	void buyDisk(records& all, int id, int amount);
	void sellDisk(records& all, int id, int amount);
	void printLog();
};