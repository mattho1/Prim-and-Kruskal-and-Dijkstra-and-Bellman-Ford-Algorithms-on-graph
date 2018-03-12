#ifndef KOPIEC_HH
#define KOPIEC_HH 

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include "Dane.hpp"

using namespace std;

struct Wezel{
	int wartosc;
	Krawedz krawedz; // przechowywana dana
	Wezel * lewySyn;
	Wezel * prawySyn;
	Wezel * rodzic;
};

class KolejkaPriorytetowa{
	private:
		
	Wezel* korzen;  
	int rozmiar;
	
	public:
	Wezel * min();
	Wezel * znajdzNastepnik(Wezel * p);
	KolejkaPriorytetowa();
	~KolejkaPriorytetowa();	
    void push(Krawedz wartosc);
    Krawedz pop();
};

#endif
