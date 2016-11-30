#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

class Fecha {
private:
	int day;
	int month;
	int year;
public:
	Fecha(int d, int m, int y);
	bool operator() (const Fecha& fch, const Fecha& fch2)
	{
		if (fch.year < fch2.year) {
			if (fch.month < fch2.month) {
				if (fch.day < fch2.day) {
					return true;
				}
			}
		}
		else return false;
	}
	//bool operator < (const Fecha &fch);
	//bool operator == (const Fecha &fch);

};

//inline bool operator< (const Fecha& fch, const Fecha& fch2) {
//	if (fch.year < fch2.year) { 
//		if (fch.month < fch2.month) { 
//			if (fch.day < fch2.day) { 
//				return true; 
//			}
//		} 
//	}
//	else return false;
//}

//bool Fecha::operator==(const Fecha &fch) {
//	if ((*this).year == fch.year) {
//		if ((*this).month == fch.month) {
//			if ((*this).day == fch.day) {
//				return true;
//			}
//		}
//	}
//	else return false;
//}

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
};

Hora::Hora(int h, int m) {
	hour = h;
	minutes = m;
}



class Agenda {
private:
	std::map <const Hora, const std::string> evt;
	std::map <const Fecha, std::map <const Hora, const std::string>> agnd;
public:
	Agenda();
	void insertarEvento(const Fecha &fecha, const Hora &hora, const std::string& descripcion);
	int GetSize() {	return agnd.size();	}
};

Agenda::Agenda(){}

void Agenda::insertarEvento(const Fecha& fecha, const Hora& hora, const std::string& descripcion) {
	evt.emplace(hora,descripcion);
	agnd.emplace(fecha, evt);

}

void main() {
	//Agenda agn;
	const Fecha date(1,11,1997);
	const Hora time(12, 50);
	//agn.insertarEvento(date,time,"Things to do");
	//std::cout << agn.GetSize();
}