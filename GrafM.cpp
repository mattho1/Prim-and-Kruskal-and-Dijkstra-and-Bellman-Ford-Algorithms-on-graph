#include "GrafM.hpp" 

//typedef std::priority_queue < Krawedz, std::vector < Krawedz >, PorownajKrawedzie > KolejkaPriorytetowa;
 

GrafM::~GrafM(){
	for(int i=0; i<rozmiar; i++){
		delete []macierz[i];
	}
	delete []macierz;
}

// konstruktor grafu w postaci macierzowej 
// wczytuje dane do grafu z tablicy dane przechowujacej krawedzie 
// argument skierowany okresla jako true graf skierowany i false nieskierowany
// dla grafu nieskierowanego uzupelnia graf symetrycznie wzgledem glownej przekatnej macierzy

GrafM::GrafM(Krawedz* dane, int pocz, int kon, int wielkosc, int lKrawedzi, bool skierowany){
	poczatek=pocz;
	koniec = kon;
	rozmiar = wielkosc;
	macierz = new int *[wielkosc];
	for(int i=0;i<rozmiar;i++){
		macierz[i]= new int[rozmiar];
	}
	for(int i=0;i<rozmiar;i++){
		for(int n=0;n<rozmiar;n++){
			macierz[i][n]=brakKrawedzi;
		}	
	}
	if(skierowany){
		for(int i=0;i<lKrawedzi;i++){
			macierz[dane[i].wierzcholekPierwszy][dane[i].wierzcholekDrugi]=dane[i].wartosc;
		}
	}else{ 
		for(int i=0;i<lKrawedzi;i++){
			if(macierz[dane[i].wierzcholekPierwszy][dane[i].wierzcholekDrugi]==brakKrawedzi){
				macierz[dane[i].wierzcholekPierwszy][dane[i].wierzcholekDrugi]=dane[i].wartosc;
				macierz[dane[i].wierzcholekDrugi][dane[i].wierzcholekPierwszy]=dane[i].wartosc;
			}
		}
	}
}

// metoda wyswietla graf w postaci macierzy
// dla kazdego wierzcholka wyswietla wierzcholki z nim polaczone 
// numer wiersz okresla w grafie skierowanym numer wierzcholka 
// z ktorego wychodzi krawedz a numer kolumny okresla numer wierzcholka docelowego
// najlepiej wyswietla wyniki maksymalnie 3 syfrowe 
	 
void GrafM::wyswietl(){ 
	for(int i=0;i<rozmiar;i++){
		for(int n=0;n<rozmiar;n++){
			if((macierz[i][n]/100)!=0){
				cout << macierz[i][n];
			}else if((macierz[i][n]/10)!=0){
				cout << " " << macierz[i][n];
			}else{
				cout << " " << " " << macierz[i][n];
			}
			if(n!=(rozmiar-1)){
				cout << " ";
			}
		}
		cout << endl;
	}
}

// metoda laczy zbiory 
// w tablicy reprezentujacej wszystkie wierzcholki zamienia przynaleznosc do zbioru 2 na przynaleznosc do zbioru 1


void GrafM::laczenieZbiorow(int* zbiory, int nr1zbioru, int nr2zbioru){
	for(int i=0; i<rozmiar; i++){
		if(zbiory[i]==nr2zbioru){
			zbiory[i]=nr1zbioru;
		}
	}
}

// metoda algorytmKruskala wylicza minimalne drzewo rozpinajace wed≥ug algorytmu Kruskala
// metoda zwraca tablice krawÍdzi bÍdaca minimalnym drzewem rozpinajacym

Krawedz* GrafM::algorytmKruskala(){
    KolejkaPriorytetowa kolejkaPriorytetowa;
   	Krawedz* tab;
   	Krawedz pom, sprawdzana;
   	int* zbioryRozlaczne;
   	int licznik=0; 
   	tab = new Krawedz[rozmiar-1];
   	zbioryRozlaczne = new int[rozmiar];
   	for(int i=0; i<rozmiar; i++){
   		zbioryRozlaczne[i]=i;
   		for(int n=i; n<rozmiar; n++){
   			if(macierz[i][n]!=brakKrawedzi){
				pom.wartosc = macierz[i][n];
				pom.wierzcholekDrugi = i;
				pom.wierzcholekPierwszy = n;
				kolejkaPriorytetowa.push(pom);
			}
		}
	}
	
	while(licznik<(rozmiar-1)){
		while(true){
//			sprawdzana=kolejkaPriorytetowa.top();
//			kolejkaPriorytetowa.pop();
			sprawdzana=kolejkaPriorytetowa.pop();
			if(zbioryRozlaczne[sprawdzana.wierzcholekPierwszy]!=zbioryRozlaczne[sprawdzana.wierzcholekDrugi]){
				laczenieZbiorow(zbioryRozlaczne, zbioryRozlaczne[sprawdzana.wierzcholekPierwszy], zbioryRozlaczne[sprawdzana.wierzcholekDrugi]);
				tab[licznik]=sprawdzana;
				licznik++;	
				break;
			}	
		}
	
	}   
   	
   	return tab;
} 

// metoda algorytmPrima wylicza minimalne drzewo rozpinajace wed≥ug algorytmu prima
// metoda zwraca tablice krawÍdzi bÍdaca minimalnym drzewem rozpinajacym
// algorytm wykorzystuje klase kolejka priorytetowa

Krawedz* GrafM::algorytmPrima(){
    KolejkaPriorytetowa kolejkaPriorytetowa;
    bool * lNalezy,sprawdzenie;
    int licznik = 0,rozpatrywany,test;
	Krawedz* tab;
	Krawedz sprawdzana;
	Krawedz pom;
	tab = new Krawedz[rozmiar-1];
	lNalezy = new bool[rozmiar];
	
	for(int i=0; i<rozmiar;i++){
		lNalezy[i]=false;
	}
	rozpatrywany=poczatek;
	while(licznik < (rozmiar-1)){
		lNalezy[rozpatrywany]=true;
		for(int i=0; i<rozmiar;i++){
			if(macierz[rozpatrywany][i]!=brakKrawedzi){
				if(!lNalezy[i]){ // bo krawÍdzie wierzcho≥kÛw odwiedzonych sa juø dodane wczeúniej
					pom.wartosc = macierz[rozpatrywany][i];
					pom.wierzcholekDrugi = i;
					pom.wierzcholekPierwszy = rozpatrywany;
					kolejkaPriorytetowa.push(pom);
				}
			}
		}
		sprawdzenie=true;
		while(sprawdzenie){
			sprawdzana=kolejkaPriorytetowa.pop();
			if(!lNalezy[sprawdzana.wierzcholekDrugi]){
				lNalezy[sprawdzana.wierzcholekDrugi]=true;
				tab[licznik]=sprawdzana;
				rozpatrywany=sprawdzana.wierzcholekDrugi;
				licznik++;
				sprawdzenie=false;		
			} 
		} 	
	}
	
	return tab;	
}

// metoda algorytmDijkstry wylicza najkrotsze sciezki w grafie dla kazdego wierzcholka
// od wierzcholka poczatkowego wed≥ug algorytmu Dijkstry
// metoda zwraca wskaünik na obiekt typu NajkrotszeSciezki
// zawiera on dwie tablice reprezentujace najkrotsze sciezki w grafie
// pierwsza tablica okresla wartosc najkrotszej sciezki
// druga tablica okresla poprzedniki kazdego wierzcholka na podstawie ktorych 
// mozna odtworzyc najkrotsza sciezke dla kazdego wierzcholka
    
NajkrotszeSciezki* GrafM::algorytmDijkstry(){
    NajkrotszeSciezki* najkrotszeSciezki;
	najkrotszeSciezki= new NajkrotszeSciezki(rozmiar,poczatek);
    bool* podzialWierzcholkow;
    int aktualny, min;
   	podzialWierzcholkow = new bool[rozmiar];  // false oznacza ze jeszcze nie rozpatrzony, true juz odwiedzony
   	for(int i=0;i<rozmiar;i++){
   		podzialWierzcholkow[i]=false;		
    }
    aktualny=poczatek;
    for(int i=0; i<rozmiar; i++){
    	podzialWierzcholkow[aktualny]=true;
    	for(int n=0; n<rozmiar; n++){
    		if(macierz[aktualny][n]!=brakKrawedzi){
    			if(najkrotszeSciezki->kosztDojscia[n]>najkrotszeSciezki->kosztDojscia[aktualny]+macierz[aktualny][n]){
    				najkrotszeSciezki->kosztDojscia[n]=najkrotszeSciezki->kosztDojscia[aktualny]+macierz[aktualny][n];
    				najkrotszeSciezki->poprzednik[n]=aktualny;
				}
			}
		}
		min = nieskonczonosc;
		for(int m=0; m<rozmiar; m++){
			if(!podzialWierzcholkow[m]){
				if(min>najkrotszeSciezki->kosztDojscia[m]){
					min=najkrotszeSciezki->kosztDojscia[m];
					aktualny=m;
				}
			}	
		}
	}			
	return najkrotszeSciezki;		
}

// metoda algorytmBellmanaForda wylicza najkrotsze sciezki w grafie dla kazdego wierzcholka
// od wierzcholka poczatkowego wed≥ug algorytmu Bellmana-Forda
// metoda zwraca wskaünik na obiekt typu NajkrotszeSciezki
// zawiera on dwie tablice reprezentujace najkrotsze sciezki w grafie
// pierwsza tablica okresla wartosc najkrotszej sciezki
// druga tablica okresla poprzedniki kazdego wierzcholka na podstawie ktorych 
// mozna odtworzyc najkrotsza sciezke dla kazdego wierzcholka
//
// algorytm jest odporny na ujemne krawedzie
// wykrywa ujemne cykle

NajkrotszeSciezki* GrafM::algorytmBellmanaForda(){
    NajkrotszeSciezki* najkrotszeSciezki;
	najkrotszeSciezki= new NajkrotszeSciezki(rozmiar,poczatek);
	bool wyznaczone;
	for(int i = 0; i < rozmiar-1; i++){
		wyznaczone=true;
		for( int n = 0; n < rozmiar; n++){
			for( int m = 0; m < rozmiar; m++){
				if(macierz[n][m]!=brakKrawedzi){
					if(najkrotszeSciezki->kosztDojscia[m] > najkrotszeSciezki->kosztDojscia[n] + macierz[n][m]){
						najkrotszeSciezki->kosztDojscia[m] = najkrotszeSciezki->kosztDojscia[n] + macierz[n][m];
						najkrotszeSciezki->poprzednik[m] = n;
						wyznaczone = false;	
					}
				}
			}
		}
		if(wyznaczone){
			return najkrotszeSciezki;
		}
	}
	for( int n = 0; n < rozmiar; n++){
		for( int m = 0; m < rozmiar; m++){
			if(macierz[n][m]!=brakKrawedzi){
				if(najkrotszeSciezki->kosztDojscia[m] > najkrotszeSciezki->kosztDojscia[n] + macierz[n][m]){
					najkrotszeSciezki->poprawne = false;
					return najkrotszeSciezki;	
				}
			}
		}
	}
			
	return najkrotszeSciezki;	
}



