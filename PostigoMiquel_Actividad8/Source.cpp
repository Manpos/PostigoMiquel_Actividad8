#include <stdio.h>
#include <iostream>
#include <map>

class Fecha {
private:
	int day;
	int month;
	int year;

public:
	Fecha(int d, int m, int y);
};

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
	std::map < Fecha, std::map < Hora, std::string> > agnd;
	std::map <Hora, std::string> evt;
public:
	void insertarEvento(const Fecha &fecha, const Hora &hora, const std::string &descripcion);

};

void Agenda::insertarEvento(const Fecha &fecha, const Hora &hora, const std::string &descripcion) {
	evt.emplace(descripcion, hora);
	agnd.emplace(evt, fecha);
}

void main() {

}