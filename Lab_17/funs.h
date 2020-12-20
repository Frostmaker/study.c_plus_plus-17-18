#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

struct point {
	double x, y;
};

struct person {
	char fullname[128]{ "no data" };
	char birthday[20];
	char gender{ '_' };
};

void menu();
void fun1(ifstream&);
void fun1_bin(string);
void fun2(ofstream&, person*, int);
void fun2_bin(string, person*, int);
void create_dots_bin(string);
void dots_from_txt_to_dat(string);
void read_employees_from_file_bin(string);
void create_double_file_bin(string);
void read_double_file_bin(string);
void change_firts_and_last_nums(string);