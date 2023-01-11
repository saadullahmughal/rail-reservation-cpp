#include "rsrc.h"
user a, usr;
list<string> stations;
list<reservation> reservations;

void get() {
	ifstream in;
	string u, p;
	int l;
	char tmp;
	in.open("user.dat", ios::binary);
	list<string>::iterator i;
	if (in.is_open()) {
		in.read((char*)&l, sizeof(int));
		u.clear();
		for (int i = 0; i < l; i++) {
			in.read((char*)&tmp, 1);
			u += tmp;
		}
		a.name = u;
		in.read((char*)&l, sizeof(int));
		p.clear();
		for (int i = 0; i < l; i++) {
			in.read((char*)&tmp, 1);
			p += tmp;
		}
		a.psw = p;
		in.read((char*)&l, sizeof(int));
		u.clear();
		for (int i = 0; i < l; i++) {
			in.read((char*)&tmp, 1);
			u += tmp;
		}
		usr.name = u;
		in.read((char*)&l, sizeof(int));
		p.clear();
		for (int i = 0; i < l; i++) {
			in.read((char*)&tmp, 1);
			p += tmp;
		}
		usr.psw = p;
	}
	in.close();
	in.open("adm.bin", ios::binary);
	if (in.is_open()) {
		in.read((char*)&l, sizeof(int));
		reservation::set_base_fare(l);
		int s;
		in.read((char*)&s, sizeof(int));
		for (int k = 0; k < s; k++) {
			in.read((char*)&l, sizeof(int));
			string s;
			if (l != 0)
				for (int j = 0; j < l; j++) {
					in.read((char*)&tmp, 1);
					s += tmp;
				}
			stations.push_back(s);
		}
		in.close();
		stations.unique();
		stations.sort();
	}
	in.close();
	in.open("resrv.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			reservation r;
			in.read((char*)&r.fare, sizeof(int));
			in >> r.ticket_no;
			if(!r.ticket_no.empty())r.clas = r.ticket_no.at(r.ticket_no.length() - 1);
			getline(in, u);
			getline(in, r.source);
			getline(in, r.destination);
			getline(in, r.reserver.name);
			in >> r.reserver.cnic;
			in >> r.reserver.number;
			getline(in, u);
			getline(in, r.reserver.address);
			in >> r.arrival_date.day;
			in >> tmp;
			in >> r.arrival_date.month;
			in >> tmp;
			in >> r.arrival_date.year;
			getline(in, u);
			getline(in, u);
			reservations.push_back(r);
		}
		reservations.pop_back();
	}
	else reservation::set_base_fare(100);
}

void put() {
	char tmp;
	list<string>::iterator i;
	int l;
	ofstream out("adm.bin", ios::binary);
	l = reservation::get_base_fare();
	out.write((char*)&l, sizeof(int));
	int s = stations.size();
	out.write((char*)&s, sizeof(int));
	for (i = stations.begin(); i != stations.end(); i++) {
		l = (*i).length();
		if (l != 0) out.write((char*)&l, sizeof(int));
		for (int j = 0; j < l; j++) {
			tmp = (*i).at(j);
			out.write((char*)&tmp, 1);
		}
	}
	out.close();
	out.open("resrv.txt");
	list<reservation>::iterator j;
	for (j = reservations.begin(); j != reservations.end(); j++) {
		(*j).put(out);
	}
	out.close();
}


void admin() {
	system("CLS");
	ifstream in;
	string u, p;
	int l, n;
	char tmp;
	
	list<string>::iterator i;
	list<reservation>::iterator r;
	do {
		system("CLS");
		cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
		cout << "0. Log out" << endl;
		cout << "1. Add new station" << endl;
		cout << "2. Delete a station" << endl;
		cout << "3. Display all stations" << endl;
		cout << "4. Display all reservations" << endl;
		cout << "5. Update fares" << endl;
		do {
			tmp = _getch();
		} while (tmp<'0' || tmp>'5');
		string s;
		switch (tmp) {
		case '0':
			break;
		case '1':
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "Enter station's name: ";
			do {
				getline(cin, s);
			} while (s.empty());
			stations.push_back(s);
			break;
		case '2':
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "Enter station's name: ";
			do {
				getline(cin, s);
			} while (s.empty());
			stations.remove(s);
			break;
		case '3':
			stations.unique();
			stations.sort();
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "Sr#\tStation" << endl;
			cout << "--------------------------------" << endl;
			n = 0;
			if (stations.empty()) {
				cout << "\tNO RECORDS FOUND" << endl;
				break;
			}
			for (i = stations.begin(); i != stations.end(); i++) {
				n++;
				if (n < 100) cout << ' ';
				if (n < 10) cout << ' ';
				cout << n << ".\t" << (*i) << endl;
				if (n % 20 == 0) {
					tmp = _getch();
					if (tmp == 27)break;
					system("CLS");
					cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
					cout << "Sr#\tStation" << endl;
					cout << "--------------------------------" << endl;
				}
			}
			break;
		case '4':
			n = 0;
			for (r = reservations.begin(); r != reservations.end(); r++) {
				system("CLS");
				cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
				n++;
				cout << (*r);
				tmp = _getch();
				if (tmp == 27)break;
			}
			if (reservations.empty())cout << "NO RECORDS FOUND" << endl;
			break;
		case '5':
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "Input new base fare: ";
			cin >> n;
			reservation::set_base_fare(n);
			break;
		}
		if (tmp != 27) {
			cout << "--------------------------------" << endl;
			system("pause");
		}
	} while (tmp != '0');
	put();
}

void dat_entr() {
	char tmp;
	string s, t;
	reservation r;
	list<reservation>::iterator ri;
	do {
		system("CLS");
		cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
		cout << "0. Log out" << endl;
		cout << "1. Reserve your seat" << endl;
		cout << "2. Cancel your reservation" << endl;
		do {
			tmp = _getch();
		} while (tmp<'0' || tmp>'3');
		switch (tmp) {
		case '0':
			break;
		case '1':
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			r.in(stations);
			reservations.push_back(r);
			break;
		case '2':
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "Input ticket no:\t";
			cin >> s;
			bool f = false;
			for (ri = reservations.begin(); ri != reservations.end(); ri++) {
				t = (*ri).ticket();
				if (t == s) {
					f = true;
					r = *ri;
					cout << r;
					cout << "Do you want to cancel it? (Y/N)";
					do {
						tmp = _getch();
					} while (tmp != 'Y' && tmp != 'N');
					if (tmp == 'Y') {
						cout << endl << "This seat has been cancelled" << endl;
						reservations.remove(r);
					}
					else {
						cout << endl << "This seat hasn't been cancelled" << endl;
					}
					break;
				}
			}
			if (!f)cout << "No such data found." << endl;
			break;
		}
		put();
		cout << "--------------------------------" << endl;
		system("pause");
	} while (tmp != '0');
}

int main() {
	system("COLOR 1F");
	get();
	char tmp = '1';
	do {
		system("CLS");
		cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
		cout << "0. Exit" << endl;
		cout << "1. Log In" << endl;
		do {
			tmp = _getch();
		} while (tmp > '1' || tmp < '0');
		if (tmp == '0') return 0;
		user tp;
		if (a.name.empty() && a.psw.empty()) {
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cout << "No past user records available\nEnter new data for further use\n";
			ofstream out("user.dat", ios::binary);
			cout << "--------------------------------" << endl;
			cout << "Input admin credentials" << endl;
			cin >> tp;
			out << tp;
			a = tp;
			cout << "--------------------------------" << endl;
			cout << "Input user credentials" << endl;
			cin >> tp;
			out << tp;
			usr = tp;
			out.close();
			continue;
		}
		do {
			system("CLS");
			cout << "Pak Rail Reservation Systems 1.0" << endl << "--------------------------------" << endl;
			cin >> tp;
			if ((tp.name != a.name || tp.psw != a.psw) && (tp.name != usr.name || tp.psw != usr.psw)) {
				cout << "\aWRONG Password";
				Sleep(1000);
			}
		} while ((tp.name != a.name || tp.psw != a.psw) && (tp.name != usr.name || tp.psw != usr.psw));

		if (tp.name == a.name)admin();
		else if (tp.name == usr.name) dat_entr();
		put();
	} while (tmp != '0');
	return 0;
}


int copy() {
	ifstream in("Railway Stations.txt", ios::in);
	ofstream out("adm.bin", ios::binary);
	int l = 0, n = 0;
	out.write((char*)&l, sizeof(int));
	string s;
	while (!in.eof()) {
		getline(in, s);
		n++;
		l = s.size();
		if(l != 0)out.write((char*)&l, sizeof(int));
		char tmp;
		for (int i = 0; i < l; i++) {
			tmp = s.at(i);
			out.write((char*)&tmp, 1);
		}
	}
	in.close();

	out.seekp(out.beg);
	out.write((char*)&n, sizeof(int));
	out.close();
	return 0;
}
