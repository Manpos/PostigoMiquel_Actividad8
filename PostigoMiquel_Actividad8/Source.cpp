#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
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
public:
	Agenda();
	void insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion);
	std::list<std::pair<Hora, std::string>>eventosDia(const Fecha &fecha);
	int GetSize() {	return agnd.size();	}
};

Agenda::Agenda(){}


void Agenda::insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion) {
	evt.emplace(hora,descripcion);
	agnd.emplace(fecha, evt);
}

std::list<std::pair<Hora, std::string>> Agenda::eventosDia(const Fecha &fecha) {
	std::list <std::pair<Hora, std::string >> lst;

	for (auto it = agnd[fecha].begin(); it != agnd[fecha].end(); ++it) {
		lst.push_back(std::pair<Hora, std::string> (it->first, it->second));
	}
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		std::cout << it->first.hour << ':' << it->first.minutes << " -> " << it->second << "\n";
	}
	return lst;
}


void main() {
	Agenda agn;
	const Fecha date(11,1,1997);
	const Hora time(12, 50);
	const Fecha date2(11, 2, 1997);
	const Hora time2(12, 55);
	agn.insertarEvento(date,time,"Things to do");
	agn.insertarEvento(date2, time2, "Things to do");
	agn.eventosDia(date);
	std::cout << agn.GetSize();
}