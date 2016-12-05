#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
class Fecha {
private:
	int day;
	int month;
public:
	Fecha(int d, int m);
	friend inline bool operator< (const Fecha& fch, const Fecha& fch2);
	friend inline bool operator==(const Fecha& fch, const Fecha& fch2);
	friend class Agenda;

};

inline bool operator==(const Fecha& fch, const Fecha& fch2) {
	if (fch.month == fch2.month && fch.day == fch2.day) { return true; }
	else return false;
}

inline bool operator< (const Fecha& fch, const Fecha& fch2) {
	if (fch.month < fch2.month) { return true; }
	else if (fch.month == fch2.month) { if (fch.day < fch2.day) return true; else return false;	}
	
	else return false;
}


Fecha::Fecha(int d, int m){
	day = d;
	month = m;
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
	else if (hr.hour == hr2.hour) { if (hr.minutes < hr2.minutes) return true; else return false; }
	else return false;
}

inline bool operator== (const Hora& hr, const Hora& hr2) {
	if (hr.hour == hr2.hour &&  hr.minutes == hr2.minutes) { return true; }
	else return false;
}



class Agenda {
private:
	std::map <const Fecha, std::map <const Hora, const std::string>> agnd;
public:
	Agenda();
	void insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion);
	std::list<std::pair<Hora, std::string>>eventosDia(const Fecha &fecha);
	std::list<std::pair<Hora, std::string>>eventosDia(const Fecha& fecha, const Hora& desde, const Hora& hasta);
	void elminarEventos(const Fecha &desde_fecha, const Hora& desde_hora, const Fecha& hasta_fecha, const Hora& hasta_hora);
	int GetSize() {	return int(agnd.size()); }
};

Agenda::Agenda(){}

//Insertar eventos en la agenda
void Agenda::insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion) {
	agnd[fecha].insert(std::pair<const Hora&, const std::string&>(hora, descripcion));
}

//Eventos dia segun fecha
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

//Eventos dia segun fecha e intervalo
std::list<std::pair<Hora, std::string>> Agenda::eventosDia(const Fecha& fecha, const Hora& desde, const Hora& hasta) {
	std::list <std::pair<Hora, std::string>> lst;
	for (auto it = agnd[fecha].begin(); it != agnd[fecha].end(); ++it) {
		if ((desde < it->first || it->first == desde) && (it->first < hasta || it->first == hasta)) {
			lst.push_back(std::pair<Hora, std::string>(it->first, it->second));
		}
	}
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		std::cout << it->first.hour << ':' << it->first.minutes << " -> " << it->second << "\n";
	}
	return lst;
}

//Eliminar Eventos
void Agenda::elminarEventos(const Fecha &desde_fecha, const Hora& desde_hora, const Fecha& hasta_fecha, const Hora& hasta_hora) {
	std::list<Hora> tmp;
	for (auto it = agnd.begin(); it != agnd.end(); ++it) {
		if (desde_fecha < it->first && it->first < hasta_fecha) {
			for (auto it2 = agnd[it->first].begin(); it2 != agnd[it->first].end(); ++it2) {
				if (desde_hora < it2->first && it2->first < hasta_hora) {
					std::cout << "There's an element\n";
					tmp.push_back(it2->first);
				}
			}
		}		
	}	

	for (auto it = agnd.begin(); it != agnd.end(); ++it) {
		for (auto itL = tmp.begin(); itL != tmp.end(); itL++) {;
		agnd[it->first].erase(*itL);
		}
	}

}


void main() {
	Agenda agn;
	const Fecha date(11,1);
	const Hora time(12, 50);

	const Fecha date3(11, 1);
	const Hora time3(12, 57);

	const Fecha date2(11, 1);
	const Hora time2(12, 55);

	const Fecha date4(30, 11);
	const Hora time4(15, 45);

	const Fecha date5(20, 3);
	const Hora time5(13, 45);

	const Hora min(12, 00), max(12, 57);
	const Fecha minF(10, 1), maxF(14, 1);

	agn.insertarEvento(date3, time3, "Things to do");
	agn.insertarEvento(date, time, "Things to do");
	agn.insertarEvento(date2, time2, "Things to do");
	agn.insertarEvento(date4, time4, "Pls work");
	agn.insertarEvento(date5, time5, "Shit happens");
	agn.eventosDia(date3);
	agn.elminarEventos(minF, min, maxF, max);
	agn.eventosDia(date3);
	std::cout << agn.GetSize() << "\n";
}