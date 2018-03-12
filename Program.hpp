#ifndef PROGRAM_HH
#define PROGRAM_HH
 
#include "GrafM.hpp"
#include "GrafLS.hpp"
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <ctime>
#include <random> 
#include <string>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <iomanip>

using namespace std;


class Program{  
	private:
	
	Krawedz* dane; // dane pobrane z pliku
	GrafM* grafMSkierowany;
	GrafM* grafMNieskierowany;
	GrafLS* grafLSSkierowany; 
	GrafLS* grafLSNieskierowany;
	int poczatek, koniec;
	int lKrawedzi, lWierzcholkow;

	
	public:
	
	Program();
	~Program();
	
	void menu();
	bool pobierzDane(string nazwaPliku);
	void wyswietlMST(Krawedz* tab);
	void wyswietlNajkrotszeSciezki(NajkrotszeSciezki* najkrotszeSciezki);
	bool generator(int wielkosc, float gestosc, bool rodzaj);
};

#endif
