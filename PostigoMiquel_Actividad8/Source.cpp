#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <list>
class Fecha {
private:
	int day;
	int month;
	int year;
public:
	Fecha(int d, int m, int y);
	friend inline bool operator< (const Fecha& fch, const Fecha& fch2);
	friend inline bool operator==(const Fecha &fch, const Fecha& fch2);
	friend class Agenda;

};

inline bool operator< (const Fecha& fch, const Fecha& fch2) {
	if (fch.year < fch2.year) { return true; }
	else if (fch.month < fch2.month) { return true; }
	else if (fch.day < fch2.day) { return true; }

	else return false;
}

inline bool operator==(const Fecha &fch, const Fecha& fch2) {
	if (fch.year == fch2.year) { return true; }
	else if (fch.month == fch2.month) { return true; }
	else if (fch.day == fch2.day) { return true; }

	else return false;
}

Fecha::Fecha(int d, int m, int y){
	day = d;
	month = m;
	year = y;
}

class Hora {
private:
	int hour;
	int minutes;
public:
	Hora(int h, int m);
	friend inline bool operator< (const Hora& hr, const Hora& hr2);
	friend inline bool operator== (const Hora& hr, const Hora& hr2);
	friend class Agenda;
};

Hora::Hora(int h, int m) {
	hour = h;
	minutes = m;
}

inline bool operator< (const Hora& hr, const Hora& hr2) {
	if (hr.hour < hr2.hour) { return true; }
	else if (hr.minutes < hr2.minutes) { return true; }
	else return false;
}

inline bool operator== (const Hora& hr, const Hora& hr2) {
	if (hr.hour == hr2.hour) { return true; }
	else if (hr.minutes == hr2.minutes) { return true; }
	else return false;
}



class Agenda {
private:
	std::map <const Hora, const std::string> evt;
	std::map <const Fecha, std::map <const Hora, const std::string>> agnd;
	std::map <const Fecha, std::map <const Hora, const std::string>>::iterator itr1;
	std::map <const Hora, const std::string>::iterator itr2;
public:
	Agenda();
	void insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion);
	std::list<std::pair<Hora, std::string>>eventosDia(const Fecha &fecha);
	int GetSize() {	return agnd.size();	}
	int GetEvtSize() { return evt.size(); }
};

Agenda::Agenda(){}


void Agenda::insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion) {
	evt.insert(std::pair<const Hora&, const std::string&> (hora, descripcion));
	agnd[fecha] =  evt;
}

std::list<std::pair<Hora, std::string>> Agenda::eventosDia(const Fecha &fecha) {
	std::list <std::pair<Hora, std::string >> lst;
	int count = 0;
	
	for (auto it = agnd[fecha].begin(); it != agnd[fecha].end(); ++it) {
		lst.push_back(std::pair<Hora, std::string> (it->first, it->second));

	}

	for (auto it = lst.begin(); it != lst.end(); ++it) {
		count++;
		std::cout << count << " " << it->first.hour << ':' << it->first.minutes << " -> " << it->second << "\n";
	}
	std::cout << "list size: "<< lst.size()<< "\n";
	return lst;
}


void main() {
	Agenda agn;
	const Fecha date(11,1,1997);
	const Hora time(12, 50);
	const Fecha date3(11, 1, 1997);
	const Hora time3(12, 57);
	const Fecha date2(11, 1, 1997);
	const Hora time2(12, 55);
	agn.insertarEvento(date3, time3, "Things to do");
	agn.insertarEvento(date,time,"Things to do");
	agn.insertarEvento(date2, time2, "Things to do");
	agn.eventosDia(date);
	std::cout << agn.GetSize() << "\n";
	std::cout << agn.GetEvtSize() << "\n";
}