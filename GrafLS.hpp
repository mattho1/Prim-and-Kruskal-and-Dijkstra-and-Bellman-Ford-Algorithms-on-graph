#ifndef GRAFLS_HH
#define GRAFLS_HH 
 
#include "Dane.hpp"
#include "KolejkaPriorytetowa.hpp"
#include <iostream> 


using namespace std;

struct Dane{
	int nrWierzcholka;
	int wartosc; 
	Dane * next;
};

class GrafLS{
	private:
		
	Dane** listaSasiedztwa;
	
	int rozmiar;
	int poczatek;
	int koniec;	
	
	void laczenieZbiorow(int* zbiory, int nr1zbioru, int nr2zbioru);
	
	public:
	
	GrafLS(Krawedz* dane, int pocz, int kon, int wielkosc, int lKrawedzi, bool skierowany);
	~GrafLS();
	
    void wyswietl();
    Krawedz* algorytmPrima();
    Krawedz* algorytmKruskala();
    NajkrotszeSciezki* algorytmDijkstry();
    NajkrotszeSciezki* algorytmBellmanaForda();
    
};

#endif
