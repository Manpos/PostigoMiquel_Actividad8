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
	std::list<std::pair<Hora, std::string>>eventosDia(const Fecha& fecha, const Hora& desde, const Hora& hasta);
	void elminarEventos(const Fecha &desde_fecha, const Hora& desde_hora, const Fecha& hasta_fecha, const Hora& hasta_hora);
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

std::list<std::pair<Hora, std::string>> Agenda::eventosDia(const Fecha& fecha, const Hora& desde, const Hora& hasta) {
	std::list <std::pair<Hora, std::string>> lst;
	for (auto it = agnd[fecha].begin(); it != agnd[fecha].end(); ++it) {
		if (desde < it->first && it->first < hasta) {
			lst.push_back(std::pair<Hora, std::string>(it->first, it->second));
		}
	}
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		std::cout << it->first.hour << ':' << it->first.minutes << " -> " << it->second << "\n";
	}
	return lst;
}

void Agenda::elminarEventos(const Fecha &desde_fecha, const Hora& desde_hora, const Fecha& hasta_fecha, const Hora& hasta_hora) {
	for (auto it = agnd.begin(); it != agnd.end(); ++it) {
		if (desde_fecha < it->first && it->first < hasta_fecha) {
			for (auto it2 = agnd[it->first].begin(); it2 != agnd[it->first].end(); ++it2) {
				if (desde_hora < it2->first && it2->first < hasta_hora) {
					agnd[it->first].erase(it2);
				}
			}
		}		
	}
}


void main() {
	Agenda agn;
	const Fecha date(11,1,1997);
	const Hora time(12, 50);
	const Fecha date3(11, 1, 1997);
	const Hora time3(12, 57);
	const Fecha date2(11, 1, 1997);
	const Hora time2(12, 55);

	//const Fecha date4(13, 1, 1997);
	//const Hora time4(12, 36);
	//const Fecha date5(14, 1, 1997);
	//const Hora time5(13, 45);

	const Hora min(12, 00), max(12, 59);
	//const Fecha minF(10, 1, 1997), maxF(14, 1, 1997);
	agn.insertarEvento(date3, time3, "Things to do");
	agn.insertarEvento(date,time,"Things to do");
	agn.insertarEvento(date2, time2, "Things to do");

	//agn.insertarEvento(date4, time4, "Things to do");
	//agn.insertarEvento(date5, time5, "Things to do");

	//agn.elminarEventos(minF, min, maxF, max);
	agn.eventosDia(date, min, max);
	std::cout << agn.GetSize() << "\n";
	std::cout << agn.GetEvtSize() << "\n";
}