#ifndef GRAFM_HH
#define GRAFM_HH
  
#include "Dane.hpp" 
#include "KolejkaPriorytetowa.hpp"
#include <iostream>

using namespace std;
 
class GrafM{
	private:
		
	int** macierz;
	 
	int rozmiar;
	int poczatek;
	int koniec;	
	
	void laczenieZbiorow(int* zbiory, int nr1zbioru, int nr2zbioru);
	
	public:
	
	GrafM(Krawedz* dane, int pocz, int kon, int wielkosc, int lKrawedzi, bool skierowany);
	~GrafM();
	
    void wyswietl();
    Krawedz* algorytmKruskala();
    Krawedz* algorytmPrima();
    NajkrotszeSciezki* algorytmDijkstry();
    NajkrotszeSciezki* algorytmBellmanaForda();
    
};


#endif
