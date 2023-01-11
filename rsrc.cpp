#include "rsrc.h"


//--------- Helping Functions ---------//

void psw_in(string &a) {
	bool valid = false;
	do {
		a.clear();
		char c;
		do {
			c = (char)_getch();
			if (c == '\b') {
				if (!a.empty()) {
					cout << "\b \b";
					a.erase(a.length() - 1);
				}
			}
			else {
				if (c != '\r') {
					cout << '*';
					a += c;
				}
			}
		} while (c != '\r');
		bool alpha, num, spcl;
		alpha = num = spcl = false;
		for (int i = 0; i < a.length(); i++) {
			c = a.at(i);
			if (c >= '0' && c <= '9') num = true;
			else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) alpha = true;
			else spcl = true;
			if (alpha && spcl && num && a.length() >= 8) {
				valid = true;
				break;
			}
		}
		if (!valid) {
			for (int i = 0; i < a.length(); i++) cout << '\b';
			for (int i = 0; i < a.length(); i++) cout << ' ';
			for (int i = 0; i < a.length(); i++) cout << '\b';
			cout << "\aInvalid Password";
			Sleep(1000);
			for (int i = 0; i < 16; i++) cout << '\b';
			for (int i = 0; i < 16; i++) cout << ' ';
			for (int i = 0; i < 16; i++) cout << '\b';
		}
	} while (!valid);
	cout << "\r\n";
	for (int i = 0; i < a.length(); i++) {
		a.at(i) = ((a.at(i) + 4) % a.length()) + 1;
	}
}


void num_in(string& a) {
	a.clear();
	char c;
	do {
		do {
			c = (char)_getch();
		} while ((c <'0' || c > '9') && c != '\r' && c != '\b');
		if (c == '\b') {
			if (!a.empty()) {
				cout << "\b \b";
				a.erase(a.length() - 1);
			}
		}
		else {
			if (c != '\r') {
				cout << c;
				a += c;
			}
		}
	} while (c != '\r');
	cout << "\r\n";
}

template <class td>
bool find(list<td> &l, td s) {
	list<td>::iterator i;
	for (i = l.begin(); i != l.end(); i++) {
		if (*i == s) return true;
	}
	return false;
}


//--------- Contact Functions ---------//

contact::contact() {
	// NO CODE HERE
}

bool contact::operator==(contact & b)
{
	if (name == b.name && address == b.address && cnic == b.cnic && number == b.number)return true;
	return false;
}

string contact::str()
{
	string t;
	t += name;
	t += "\r\n";
	t += cnic;
	t += "\r\n";
	t += number;
	t += "\r\n";
	t += address;
	t += "\r\n";
	return t;
}

istream& operator >> (istream& in, contact& a) {
	cout << "Full name:\t\t";
	getline(cin,a.name);
	cout << "CNIC:\t\t\t";
	num_in(a.cnic);
	cout << "Phone Number:\t\t";
	num_in(a.number);
	cout << "Address:\t\t";
	getline(cin, a.address);
	if (a.cnic.length() > 13) a.cnic.erase(13);
	if (a.number.length() > 11) a.number.erase(11);
	return in;
}


ostream& operator << (ostream& out, contact& a) {
	out << "Full Name:\t\t" << a.name;
	out << endl << "CNIC:\t\t\t" << a.cnic;
	out << endl << "Phone Number:\t\t" << a.number << endl;
	out << "Address:\t\t" << a.address << endl;

	return out;
}

//--------- Date Functions ---------//

date::date() {
	day = 1;
	month = 1;
	year = 2000;
}

string date::str()
{
	string tmp;
	char t = (day / 10) + '0';
	tmp += t;
	t = (day % 10) + '0';
	tmp += t;
	t = (month / 10) + '0';
	tmp += t;
	t = (month % 10) + '0';
	tmp += t;
	int T = year % 100;
	t = (T / 10) + '0';
	tmp += t;
	t = (year % 10) + '0';
	tmp += t;
	return tmp;
}

bool date::operator==(date & b)
{
	if (day == b.day && month == b.month && year == b.year)return true;
	return false;
}

istream& operator >> (istream& in, date& a) {
	cout << "Enter year:\t\t";
	in >> a.year;
	if (a.year < 2000)a.year = 2000;
	if (a.year > 2099)a.year = 2099;
	int mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (a.year % 4 == 0)mon[1]++;
	cout << "Enter month:\t\t";
	in >> a.month;
	if (a.month < 1)a.month = 1;
	if (a.month > 12)a.month = 12;
	cout << "Enter day:\t\t";
	in >> a.day;
	if (a.day < 1)a.day = 1;
	if (a.day > mon[a.month - 1])a.day = mon[a.month - 1];
	return in;
}

ostream& operator << (ostream& out, date& a) {
	out << a.day << '/' << a.month << '/' << a.year;
	return out;
}

//--------- Rservation Functions ---------//

reservation::reservation()
{
	// NO CODE HERE
}

int reservation::base_fare;

void reservation::in(list<string> stations)
{
	do {
		cout << "Enter your source:\t";
		do {
			getline(cin, source);
		} while (source.empty());
		if (!find(stations, source)) cout << "No such station available in the record\n";
	} while (!find(stations, source));
	do {
		cout << "Enter your destination:\t";
		do {
			getline(cin, destination);
		} while (destination.empty());
		if (destination == source)cout << "Enter some different  destination\n";
		if (!find(stations, destination)) cout << "No such station available in the record\n";
	} while (destination == source || !find(stations, destination));
	cout << "In which class do you want to travel?" << endl;
	cout << "E. Economy" << endl;
	cout << "A. AC Standard" << endl;
	cout << "P. AC Parlour" << endl;
	do {
		clas = _getch();
	} while (clas != 'A' && clas != 'E' && clas != 'P');
	cout << "Your choice:\t\t" << clas << endl;
	switch (clas) {
	case'E':
		fare = base_fare;
		break;
	case'A':
		fare = 2 * base_fare;
		break;
	case'P':
		fare = 3 * base_fare;
		break;
	}
	cin >> reserver;
	cout << "Enter date of arrival" << endl;
	cin >> arrival_date;
	ticket_no.clear();
	ticket_no += source.at(0);
	ticket_no += destination.at(0);
	ticket_no += arrival_date.str();
	ticket_no += clas;
	cout << "Ticket no.\t\t" << ticket_no << endl;
	system("pause");
	//return in;
}




istream& operator >> (istream& in, user& a) {
	cout << "Input username: ";
	in >> a.name;
	cout << "Input password: ";
	psw_in(a.psw);
	return in;
}


ofstream& operator << (ofstream& out, user& a) {
	int l = a.name.length();
	out.write((char*)&l, sizeof(int));
	for (int i = 0; i < l; i++)out.write((char*)&a.name[i], 1);
	l = a.psw.length();
	out.write((char*)&l, sizeof(int));
	for (int i = 0; i < l; i++)out.write((char*)&a.psw[i], 1);
	return out;
}


void reservation::put(ofstream& out)
{
	out.write((char*)&fare, sizeof(int));
	out << ticket_no << endl;
	out << source << endl;
	out << destination << endl;
	out << reserver.str();
	out << arrival_date << endl;
	out << "-------------------------------" << endl;
}

string reservation::ticket()
{
	return ticket_no;
}

bool reservation::operator==(reservation b)
{
	if (ticket_no != b.ticket_no) return false;
	if (source != b.source) return false;
	if (destination != b.destination) return false;
	if (ticket_no != b.ticket_no) return false;
	if (!(reserver == b.reserver)) return false;
	if (clas != b.clas) return false;
	if (!(arrival_date == b.arrival_date)) return false;
	if (fare != b.fare)return false;
	return true;
}

void reservation::set_base_fare(int f)
{
	base_fare = f;
}

int reservation::get_base_fare()
{
	return base_fare;
}

ostream& operator << (ostream& out, reservation& r) {
	out << "Ticket No\t\t" << r.ticket_no << endl;
	out << r.reserver;
	out << "Source:\t\t\t" <<  r.source << endl;
	out << "Destination:\t\t" << r.destination << endl;
	out << "Class:\t\t\t";
	switch (r.clas) {
	case 'E':
		cout << "Economy\t\tRs. " << r.fare << endl;
		break;
	case 'A':
		cout << "AC Standard\tRs. " << r.fare << endl;
		break;
	case 'P':
		cout << "AC Parlour\tRs. " << r.fare << endl;
		break;
	}
	out << "Date of arrival:\t" << r.arrival_date << endl;
	return out;
}

/*

*/

