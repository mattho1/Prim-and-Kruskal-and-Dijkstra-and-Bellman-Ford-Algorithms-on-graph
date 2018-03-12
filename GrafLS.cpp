#include "GrafLS.hpp" 

//typedef std::priority_queue < Krawedz, std::vector < Krawedz >, PorownajKrawedzie > KolejkaPriorytetowa;
 
GrafLS::~GrafLS(){
	Dane*tmp,*tmp2;  
	for(int i=0; i<rozmiar; i++){
		while(listaSasiedztwa[i]!=NULL){
			tmp=listaSasiedztwa[i];
			listaSasiedztwa[i]=listaSasiedztwa[i]->next;
			delete tmp;
		}	
	}
	delete []listaSasiedztwa;
}
  
// konstruktor obiektu Graf w postaci listy sπsiedztwa
// uzupelnia graf danymi otrzymanymi w tablicy dane
// w zaleznosci od tego czy graf jest skierowany czy nie tworzy rozne grafy
// w grafie nie skierowanym zapisuje krawedz do dwoch wierzcholkow
// argument skierowany true oznacza skierowany false oznacza nie skierowany
  
GrafLS::GrafLS(Krawedz* dane, int pocz, int kon, int wielkosc, int lKrawedzi, bool skierowany){
	Dane *tmp,*tmp2,*tmp3,*tmp4;
	bool sprawdzenie;
	poczatek=pocz;
	koniec = kon;
	rozmiar = wielkosc;
	listaSasiedztwa = new Dane*[rozmiar];
	for(int i=0; i<rozmiar;i++){
		listaSasiedztwa[i]=NULL;
	}
	if(skierowany){
		for(int i=0;i<lKrawedzi;i++){
			tmp=new Dane();
			tmp->next=NULL;
			tmp->nrWierzcholka=dane[i].wierzcholekDrugi;
			tmp->wartosc=dane[i].wartosc;
			tmp2=listaSasiedztwa[dane[i].wierzcholekPierwszy];
			if(tmp2!=NULL){
				while(tmp2->next!=NULL){
					tmp2=tmp2->next;
				}
				tmp2->next=tmp;
			}else{
				listaSasiedztwa[dane[i].wierzcholekPierwszy]=tmp;
			}
		}
	}else{
		for(int i=0;i<lKrawedzi;i++){
			
			tmp=new Dane();
			tmp->next=NULL;
			tmp->nrWierzcholka=dane[i].wierzcholekDrugi;
			tmp->wartosc=dane[i].wartosc; 
			
			tmp4=new Dane();
			tmp4->next=NULL;
			tmp4->nrWierzcholka=dane[i].wierzcholekPierwszy;
			tmp4->wartosc=dane[i].wartosc;
			
			tmp2=listaSasiedztwa[dane[i].wierzcholekPierwszy];
			tmp3=listaSasiedztwa[dane[i].wierzcholekDrugi];
			
			sprawdzenie=true;
			
			while(tmp3!=NULL){
				if(tmp3->nrWierzcholka==dane[i].wierzcholekPierwszy){
					sprawdzenie=false;
					break;
				}
				tmp3=tmp3->next;
			}
			tmp3=listaSasiedztwa[dane[i].wierzcholekDrugi];
			if(sprawdzenie){
				if(tmp2!=NULL){
					while(tmp2->next!=NULL){
						if(tmp2->nrWierzcholka==dane[i].wierzcholekDrugi){
							break;
						}
						tmp2=tmp2->next;
					}
					tmp2->next=tmp;
				}else{ 
					listaSasiedztwa[dane[i].wierzcholekPierwszy]=tmp;
				}
				if(tmp3!=NULL){
					while(tmp3->next!=NULL){
						if(tmp3->nrWierzcholka==dane[i].wierzcholekPierwszy){
							break;
						}
						tmp3=tmp3->next;
					}
					tmp3->next=tmp4;
				}else{ 
					listaSasiedztwa[dane[i].wierzcholekDrugi]=tmp4;
				}
			}
		}
	}
}

// metoda wyswietla graf w postaci listy sasiedztwa
// dla kazdego wierzcholka wyswietla wierzcholki z nim polaczone
// najlepiej wyswietla wyniki maksymalnie 3 syfrowe 

void GrafLS::wyswietl(){
	Dane *tmp;
	for(int i=0;i<rozmiar;i++){
		cout << "ListaSasiedztwa[" << i << "] = ";
		tmp = listaSasiedztwa[i];
		while(tmp!=NULL){
			cout << tmp->nrWierzcholka << " ";
			tmp=tmp->next;
		}
		cout << endl;
	}
}

// metoda algorytmPrima wylicza minimalne drzewo rozpinajace wed≥ug algorytmu prima
// metoda zwraca tablice krawÍdzi bÍdaca minimalnym drzewem rozpinajacym
// algorytm wykorzystuje klase kolejka priorytetowa

Krawedz* GrafLS::algorytmPrima(){
    KolejkaPriorytetowa kolejkaPriorytetowa;
    bool * lNalezy,sprawdzenie;
    int licznik = 0,rozpatrywany,test;
	Krawedz* tab;
	Krawedz sprawdzana;
	Krawedz pom;
	Dane* tmp;
	tab = new Krawedz[rozmiar-1];
	lNalezy = new bool[rozmiar];
	
	for(int i=0; i<rozmiar;i++){
		lNalezy[i]=false;
	}
	rozpatrywany=poczatek;
	
	while(licznik < (rozmiar-1)){
		lNalezy[rozpatrywany]=true;
		tmp=listaSasiedztwa[rozpatrywany];
		
		while(tmp!=NULL){
			if(!lNalezy[tmp->nrWierzcholka]){
				pom.wartosc = tmp->wartosc;
				pom.wierzcholekDrugi = tmp->nrWierzcholka;
				pom.wierzcholekPierwszy = rozpatrywany;
				kolejkaPriorytetowa.push(pom);
			}
			tmp=tmp->next;
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

// metoda laczy zbiory 
// w tablicy reprezentujacej wszystkie wierzcholki zamienia przynaleznosc do zbioru 2 na przynaleznosc do zbioru 1

void GrafLS::laczenieZbiorow(int* zbiory, int nr1zbioru, int nr2zbioru){
	for(int i=0; i<rozmiar; i++){
		if(zbiory[i]==nr2zbioru){
			zbiory[i]=nr1zbioru;
		}
	}
}

// metoda algorytmKruskala wylicza minimalne drzewo rozpinajace wed≥ug algorytmu Kruskala
// metoda zwraca tablice krawÍdzi bÍdaca minimalnym drzewem rozpinajacym

Krawedz* GrafLS::algorytmKruskala(){
   	KolejkaPriorytetowa kolejkaPriorytetowa;
   	Krawedz* tab;
	Dane * tmp;
   	Krawedz pom, sprawdzana;
   	int* zbioryRozlaczne;
   	int licznik=0;
   	tab = new Krawedz[rozmiar-1];
   	zbioryRozlaczne = new int[rozmiar];
   	for(int i=0; i<rozmiar; i++){
   		zbioryRozlaczne[i]=i;
   		tmp = listaSasiedztwa[i];
   		while(tmp!=NULL){
   			if(i>tmp->nrWierzcholka){ // bo krawÍdzie ktÛrych wierzcho≥ek docelowy jest wiÍksze od tego ktÛry rozpatrujemy sa juø dodane wczeúniej
   				pom.wartosc = tmp->wartosc;
				pom.wierzcholekDrugi = tmp->nrWierzcholka;
				pom.wierzcholekPierwszy = i;
				kolejkaPriorytetowa.push(pom);
			}
			tmp=tmp->next;
		}
	}
	while(licznik<(rozmiar-1)){
		while(true){
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
 
// metoda algorytmDijkstry wylicza najkrotsze sciezki w grafie dla kazdego wierzcholka
// od wierzcholka poczatkowego wed≥ug algorytmu Dijkstry
// metoda zwraca wskaünik na obiekt typu NajkrotszeSciezki
// zawiera on dwie tablice reprezentujace najkrotsze sciezki w grafie
// pierwsza tablica okresla wartosc najkrotszej sciezki
// druga tablica okresla poprzedniki kazdego wierzcholka na podstawie ktorych 
// mozna odtworzyc najkrotsza sciezke dla kazdego wierzcholka
  
NajkrotszeSciezki* GrafLS::algorytmDijkstry(){
    NajkrotszeSciezki* najkrotszeSciezki;
	najkrotszeSciezki = new NajkrotszeSciezki(rozmiar,poczatek);
    bool* podzialWierzcholkow;
    Dane* tmp;
    int aktualny, min;
   	podzialWierzcholkow = new bool[rozmiar];  // false oznacza ze jeszcze nei rozpatrzony, true juz odwiedzony
   	for(int i=0;i<rozmiar;i++){
   		podzialWierzcholkow[i]=false;		
    }
    aktualny=poczatek;
    for(int i=0; i<rozmiar; i++){
    	podzialWierzcholkow[aktualny]=true;
				
		tmp=listaSasiedztwa[aktualny];
		while(tmp!=NULL){
			if(najkrotszeSciezki->kosztDojscia[tmp->nrWierzcholka]>najkrotszeSciezki->kosztDojscia[aktualny]+tmp->wartosc){
    				najkrotszeSciezki->kosztDojscia[tmp->nrWierzcholka]=najkrotszeSciezki->kosztDojscia[aktualny]+tmp->wartosc;
    				najkrotszeSciezki->poprzednik[tmp->nrWierzcholka]=aktualny;
			}
			tmp=tmp->next;
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

NajkrotszeSciezki* GrafLS::algorytmBellmanaForda(){
    NajkrotszeSciezki* najkrotszeSciezki;
	najkrotszeSciezki= new NajkrotszeSciezki(rozmiar,poczatek);
	Dane* tmp;
	bool wyznaczone;
	for(int i = 0; i < rozmiar-1; i++){
		wyznaczone=true;
		for( int n = 0; n < rozmiar; n++){
			tmp = listaSasiedztwa[n];
			while(tmp != NULL){
				if(najkrotszeSciezki->kosztDojscia[tmp->nrWierzcholka] > najkrotszeSciezki->kosztDojscia[n] + tmp->wartosc){
					najkrotszeSciezki->kosztDojscia[tmp->nrWierzcholka] = najkrotszeSciezki->kosztDojscia[n] + tmp->wartosc;
					najkrotszeSciezki->poprzednik[tmp->nrWierzcholka] = n;
					wyznaczone = false;	
				}
				tmp = tmp->next;
			}
		}
		if(wyznaczone){
			return najkrotszeSciezki;
		}
	}
	
	for( int n = 0; n < rozmiar; n++){
		tmp = listaSasiedztwa[n];
		while(tmp != NULL){
			if(najkrotszeSciezki->kosztDojscia[tmp->nrWierzcholka] > najkrotszeSciezki->kosztDojscia[n] + tmp->wartosc){
				najkrotszeSciezki->poprawne = false;
				return najkrotszeSciezki;
			}
			tmp = tmp->next;
		}
	}
			
	return najkrotszeSciezki;		
}
