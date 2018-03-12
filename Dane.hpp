#ifndef DANE_HH
#define DANE_HH 
  
#include <queue>
#include <conio.h>
#define brakKrawedzi 0 
#define nieskonczonosc 100000

// struktura Krawedz jest wykorzystywana do przechowywania krawedzi w kilku klasach
// wiercho�ek pierwszy jest po prostu jednym z wierzcho�k�w w grafie nieskierowanym
// natomiast w grafie skierowanym jest on wierzcho�kiem z kt�rego wychodzi kraw�d�
// wierzcho�ek drgui jest natomiast wierzcho�kiem docelowym kraw�dzi w grafie skierowanym
// wartosc okresla wartosc krawedzi pomiedzy dwoma wierzcho�kami

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
// przechowuj�cej poprzednik wierzcho�ka okreslonego numerem indeksu
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
