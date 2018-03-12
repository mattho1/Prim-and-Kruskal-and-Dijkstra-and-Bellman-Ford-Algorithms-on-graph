#ifndef DANE_HH
#define DANE_HH 
  
#include <queue>
#include <conio.h>
#define brakKrawedzi 0 
#define nieskonczonosc 100000

// struktura Krawedz jest wykorzystywana do przechowywania krawedzi w kilku klasach
// wiercho³ek pierwszy jest po prostu jednym z wierzcho³ków w grafie nieskierowanym
// natomiast w grafie skierowanym jest on wierzcho³kiem z którego wychodzi krawêdŸ
// wierzcho³ek drgui jest natomiast wierzcho³kiem docelowym krawêdzi w grafie skierowanym
// wartosc okresla wartosc krawedzi pomiedzy dwoma wierzcho³kami

struct Krawedz{
	int wierzcholekPierwszy; 
	int wierzcholekDrugi;
	int wartosc;
};

// struktura NajkrotszeSciezki jest struktura pomocniczna do algorytmow 
// wyznaczajacych najkrotsze sciezki
// wskaznik kosztDojscia jest wykorzystywany do dynamicznego stworzenia tablicy
// przechowujacej wartosci kosztow dojscia od wierzcholka poczatkowego do okreslonego numerem indeksu tablicy
// wskaznik poprzednik jest wykorzystywany do dynamicznego stworzenia tablicy
// przechowuj¹cej poprzednik wierzcho³ka okreslonego numerem indeksu
// 
// konstruktor tworzy tablice wielkosci rozmiar i ustawia wszystkie pola tablicy kosztDojscia po za 
// oznacoznym indeksem poczatek na nieskonczonosc i wszystkie pola tablicy poprzednik na wartosc -1

struct NajkrotszeSciezki{
	int* kosztDojscia; 
	int* poprzednik;
	bool poprawne;
	NajkrotszeSciezki(int rozmiar, int poczatek){
		kosztDojscia = new int[rozmiar];
   		poprzednik = new int[rozmiar];
   		for(int i=0;i<rozmiar;i++){
   			kosztDojscia[i]=nieskonczonosc;
   			poprzednik[i]=-1;
		}
		kosztDojscia[poczatek]=0;
		poprawne=true;
	}
	~NajkrotszeSciezki(){
		delete []kosztDojscia;
		delete []poprzednik;
	}
};

#endif
