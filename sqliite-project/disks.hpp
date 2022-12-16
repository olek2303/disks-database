#pragma once 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Disks : public vector<vector<string>> { 
public:
	Disks() {};
	Disks(vector<vector<string>> s) {};
	~Disks() {};

};