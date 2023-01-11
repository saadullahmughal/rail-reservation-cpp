#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <list>
#include <Windows.h>

using namespace std;
//--------- Helping Functions ---------//
void psw_in(string& a);
void num_in(string& a);
template <class td>
bool find(list<td> &l, td s);

//--------- Structures and Classes ---------//

struct user {
	string name, psw;
};

class contact {
protected:
	string name, address, number, cnic;
public:
	contact();
	bool operator == (contact& b);
	friend istream& operator >> (istream& in, contact& a);
	friend ostream& operator << (ostream& out, contact& a);
	friend void get();
	friend void put();
	string str();
};


class date {
protected:
	int day, month, year;
public:
	date();
	string str();
	bool operator == (date& b);
	friend istream& operator >> (istream& in, date& a);
	friend ostream& operator << (ostream& out, date& a);
	friend void get();
	friend void put();
};


class reservation {
protected:
	contact reserver;
	string source, destination;
	date arrival_date;
	string ticket_no;
	char clas;
	int fare;
public:
	static int base_fare;
	reservation();
	void in(list<string> stations);
	void put(ofstream& out);
	friend ostream& operator << (ostream& out, reservation& a);
	friend void get();
	friend void put();
	string ticket();
	bool operator == (reservation b);
	static void set_base_fare(int f);
	static int get_base_fare();
};

//--------- Friend Functions ---------//


istream& operator >> (istream& in, user& a);
ofstream& operator << (ofstream& out, user& a);

istream& operator >> (istream& in, contact& a);
ostream& operator << (ostream& out, contact& a);

istream& operator >> (istream& in, date& a);
ostream& operator << (ostream& out, date& a);

ostream& operator << (ostream& out, reservation& a);

