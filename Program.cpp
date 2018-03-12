#include "Program.hpp"



Program::~Program(){
	delete[] dane;
	delete grafMSkierowany;
	delete grafMNieskierowany;
	delete grafLSSkierowany;
	delete grafLSNieskierowany;
} 

// metoda menu odpowiada za obsluge interakcji z uzytkownikiem
// wczytuje z standardowego wejscia dane podane przez uzytkownika o paramterach grafu
// tworzy grafy i obsluguje testowanie algorytmow
// konczy dzialanie programu w przypadku niepoprawnych danych do generowania grafu
// lub w przypadku niepoprawnego otwarcia pliku z grafem albo w normalny sposob po podaniu odpowiedniej wartosci przez uzytkownika

 
void Program::menu(){
	
	int wybor,wyborCzynnosci,wyborPrezentacji;
	string nazwaPliku;
	int wielkoscGrafu;
	float gestoscGrafu;
	bool skierowany;
	Krawedz*tab;
	NajkrotszeSciezki* najkrotszeSciezki;
	
	cout << endl << "[1] test" << endl << "[2] prezentacja" << endl << "Wybor opcji: ";
	cin >> wyborPrezentacji;
	cout << endl; 
	
	if(wyborPrezentacji==1){
		cout << endl << "Podaj wielkosc grafu: " << endl;
		cin >> wielkoscGrafu;
		cout << endl << endl << "Podaj gestosc grafu: " << endl;
		cin >> gestoscGrafu;
		cout << endl << endl << "Podaj czy graf ma byc skierowny [0] czy nieskierowany [1]: " << endl;
		cin >> skierowany;
		if(!generator(wielkoscGrafu,gestoscGrafu,skierowany)){
			cout << endl << "Nie mozna wygenerowac grafu o podanych parametrach.";
			cout << " Upewnij sie czy dla podanej liczby krawedzi i gestosci mozna utworzyc spojny graf " << endl;
			exit( 0 );	
		}
		
		if(!pobierzDane("Dane")){
			cout << endl << "Plik z danymi nie zostal poprawnie otwarty. Sprawdz czy istnieje plik o podanej nazwie ";
			cout << "jezeli nie to uruchom ponownie i podaj poprawna nazwe pliku." << endl;
			exit( 0 );
		}
				
	}else{
		cout << endl << "Podaj nazwe pliku z danymi: " << endl;
		cin >> nazwaPliku;
		if(!pobierzDane(nazwaPliku)){
			cout << endl << "Plik z danymi nie zostal poprawnie otwarty. Sprawdz czy istnieje plik o podanej nazwie ";
			cout << "jezeli nie to uruchom ponownie i podaj poprawna nazwe pliku." << endl;
			exit( 0 );
		}
	} 
	
	
	grafMSkierowany = new GrafM(dane, poczatek, koniec, lWierzcholkow, lKrawedzi, true);
	grafMNieskierowany= new GrafM(dane, poczatek, koniec, lWierzcholkow, lKrawedzi, false);
	grafLSSkierowany = new GrafLS(dane, poczatek, koniec, lWierzcholkow, lKrawedzi, true);
	grafLSNieskierowany = new GrafLS(dane, poczatek, koniec, lWierzcholkow, lKrawedzi, false);
	
		do{
			cout << endl << "Wybierz problem jaki chcesz rozwiazac." << endl;
			cout << "[1] wyznaczenie minimalnego drzewa rozpinajacego" << endl << "[2] wyznaczenie najkrotszej sciezki w grafie" << endl << "[0]zakoncz"<< endl << "Wybor opcji: ";
			cin >> wybor;
			switch(wybor){ 
			case 0:
				break;
			case 1: //nieskierowany
				do{
				cout << endl <<"Wybierz co chcesz zrobic z grafem." << endl;
				cout << "[1] Wyswietl graf macierzowo" << endl << "[2] Wyswietl graf listowo" << endl << "[3] Algorytm Kruskala" << endl << "[4] Algorytm Prima" << endl << "[0]cofnij"<< endl << "Wybor opcji: ";
				cin >> wyborCzynnosci;
				
				switch(wyborCzynnosci){
				case 0:
					break;
				case 1:
					grafMNieskierowany->wyswietl();				
				    break;
				case 2: 
					grafLSNieskierowany->wyswietl();
				    break;
				case 3:
					tab=grafMNieskierowany->algorytmKruskala();
					wyswietlMST(tab);
					cout << endl << endl;
					tab=grafLSNieskierowany->algorytmKruskala(); 
					wyswietlMST(tab);
				    break;
				case 4:
					tab=grafMNieskierowany->algorytmPrima();
					wyswietlMST(tab);
					cout << endl << endl;
					tab=grafLSNieskierowany->algorytmPrima();
					wyswietlMST(tab); 
				    break;
				default:
				    cout<< endl << "Podano niepoprawna opcje zachowania dla grafu." << endl;
				    wyborCzynnosci=-1;
				    break; 
				}
				}while(wyborCzynnosci!=0);
				
			    break;
			case 2: //skierowany
				do{
				cout << endl << "Wybierz co chcesz zrobic z grafem." << endl;
				cout << "[1] Wyswietl graf macierzowo" << endl << "[2] Wyswietl graf listowo" << endl << "[3] Algorytm Dijkstry" << endl << "[4] Algorytm Bellmana-Forda" << endl << "[0]cofnij"<< endl << "Wybor opcji: ";
				cin >> wyborCzynnosci;
				
				switch(wyborCzynnosci){
				case 0:
					break;
				case 1:
					grafMSkierowany->wyswietl();				
				    break;
				case 2: 
					grafLSSkierowany->wyswietl();
				    break;
				case 3:
					najkrotszeSciezki=grafMSkierowany->algorytmDijkstry();
					wyswietlNajkrotszeSciezki(najkrotszeSciezki);
					cout << endl << endl;
					najkrotszeSciezki=grafLSSkierowany->algorytmDijkstry();
					wyswietlNajkrotszeSciezki(najkrotszeSciezki);
				    break;
				case 4:
					najkrotszeSciezki=grafMSkierowany->algorytmBellmanaForda();
					wyswietlNajkrotszeSciezki(najkrotszeSciezki);
					cout << endl << endl;
					najkrotszeSciezki=grafLSSkierowany->algorytmBellmanaForda();
					wyswietlNajkrotszeSciezki(najkrotszeSciezki);
				    break;
				default:
				    cout<< endl << "Podano niepoprawna opcje zachowania dla grafu." << endl;
				    wyborCzynnosci=-1;
				    break;
				}
				}while(wyborCzynnosci!=0);
				
			    break;
			default:
			    cout<< endl << "Podano niepoprawna opcje." << endl;
			    wybor=-1;
			    break;
			}
		}while(wybor!=0);
}

// metoda pobierz dane pobiera graf z pliku o nazwie podanej jako parametr
// zwraca true gdy pobieranie przebieglo pomyslnie i false gdy nie udalo sie otworzyc pliku

bool Program::pobierzDane(string nazwaPliku){
	ifstream plik;
	nazwaPliku = nazwaPliku + ".txt";
	plik.open( nazwaPliku );
	if( plik.good() )
	{
    	plik >> lKrawedzi >> lWierzcholkow >> poczatek >> koniec;
    	dane = new Krawedz[lKrawedzi];
    	for(int i=0;i<lKrawedzi;i++){
    		plik>> dane[i].wierzcholekPierwszy >> dane[i].wierzcholekDrugi >> dane[i].wartosc;
		}
	} else
	{	
		return false;
	} 	
	return true;
	plik.close();
}

// metoda wyswietl przyjmuje jako parametr tablice krawedzi tworzacych minimalne drzewo rozpinajace
// wykorzystywana do wyswietlania wynikow algorytmow Prima i Kruskala

void Program::wyswietlMST(Krawedz* tab){
	int suma = 0;
	for(int i = 0; i < (lWierzcholkow-1) ;i++){
		cout << endl << "(" << tab[i].wierzcholekPierwszy << ", " << tab[i].wierzcholekDrugi << ")  " << tab[i].wartosc;
		suma += tab[i].wartosc;
	}
	cout << endl << "MST = " << suma << endl;
}

// metoda wyswietl przyjmuje jako parametr wskaznik na obiekt najkrotsze sciezki
// wypisuje na standardowym wyjsciu najkrotsze sciezki dla kazdego wierzcholka i laczny koszt przejscia
// po najkrotszej sciezce. wypisuje rowniez wierzcholki po ktorych nalezy przejsc
// wykorzystywana do wyswietlania wynikow algorytmow Dijkstry i Bellmana-Forda

void Program::wyswietlNajkrotszeSciezki(NajkrotszeSciezki* najkrotszeSciezki){
	int licznik,pom;
	int* tabTMP;
	int* stos;
	//int suma=0; // do testow
	stos = new int[lWierzcholkow];
	if(najkrotszeSciezki->poprawne){
		for(int i = 0; i<lWierzcholkow; i++){
			cout << i << " | " << najkrotszeSciezki->kosztDojscia[i] << " | "; 
			//suma += najkrotszeSciezki->kosztDojscia[i];
			pom = i; 
			for(licznik = 0; najkrotszeSciezki->poprzednik[pom]!=-1; licznik++){
				stos[licznik] = pom;
				pom = najkrotszeSciezki->poprzednik[pom];
			}
			stos[licznik] = poczatek;
			
			while(licznik >= 0){
				cout << " " << stos[licznik--];
			}
			cout << endl;
		}
		//cout << endl << suma << endl;
	}else{
		cout << endl << "Nie mozna wyswietlic najkrotszych sciezek poniewaz wystepuje cykl ujemny" << endl;
	}
	
}


Program::Program(){
	srand( time( NULL ) );
} 

// metoda generator generuje graf i zapisuje go do pliku o nazwie Dane
// w zaleznosci od parametrow tworzy rozne rodzaje grafow
// wielkosc okresla liczbe wierzcholkow grafu i wyliczana jest z niej ilosc krawedzi
// zalezna od rodzaju generowanego grafu
// gestosc okresla jaki procent wszystkich mozliwych krawedzi zostanie wygenerowany
// rodzaj jest zmienna logiczna okreslajaca czy graf bedzie skierowany czy nie
// rodzaj: true nieskierowany false skierowany
//
// metoda zwraca true gdy stworzy graf
// metoda zwraca false gdy nie bedzie mozliwe stworzenie grafu o podanych parametrach 
// albo plik do zapisu nie zostanie poprawnie otwarty
//
// metoda generator moze stworzyc graf minimalnie wiekszy od najmniejszego jaki moglby byc stworzony
// dla zadanego rozmiaru. wynika to z sposobu generowania grafu tak zeby byl spojny i mozna bylo dojsc do kazdego wierzcholka

bool Program::generator(int wielkosc, float gestosc, bool rodzaj){ 
	Krawedz*tab;
	int liczbaWszystkichKrawedzi = 0,liczbaKrawedzi,poczatek,koniec;
	bool sprawdzenie;
	bool* docelowe;
	int rozmiar=wielkosc;
	
	if(gestosc>1){
		gestosc=1;
	}
	if(rodzaj){
		liczbaWszystkichKrawedzi = (wielkosc-1)*(wielkosc)/2;
	}else{
		liczbaWszystkichKrawedzi = (wielkosc-1)*(wielkosc);
	}
		
	liczbaKrawedzi = round(liczbaWszystkichKrawedzi*gestosc);
	
	fstream plik;
	plik.open("Dane.txt", ios::out);
	
	if(liczbaKrawedzi>0){
		
	poczatek=(rand()%wielkosc);
	koniec=(rand()%wielkosc);
		
	if(poczatek==koniec){
		do{
			sprawdzenie=true;
			koniec=(rand()%wielkosc);
			if(poczatek==koniec){
				sprawdzenie=false;
			}			
		}while(!sprawdzenie);
	}
	if(liczbaKrawedzi>=wielkosc+1){ /////
		if(plik.good()){
			plik << liczbaKrawedzi << " " << wielkosc << " " << poczatek << " " << koniec << endl;
			tab= new Krawedz[liczbaKrawedzi];
			docelowe= new bool[wielkosc];
			
			for(int i=0; i<wielkosc; i++){
				docelowe[i]=false;
			}
			for(int i=0; i<wielkosc; i++){
				if(i==(wielkosc-1)&&docelowe[wielkosc-1]==false){
					rozmiar++;
					tab[i].wartosc = (rand()%wielkosc)+1;
					tab[i].wierzcholekPierwszy = i;
					tab[i].wierzcholekDrugi = (rand()%(wielkosc-1));
					i++;
					tab[i].wartosc = (rand()%wielkosc)+1;
					tab[i].wierzcholekPierwszy = (rand()%(wielkosc-1));
					tab[i].wierzcholekDrugi = i-1;
				}else{
					do{
						sprawdzenie=false;
						tab[i].wartosc = (rand()%wielkosc)+1;
						tab[i].wierzcholekPierwszy = i;
						tab[i].wierzcholekDrugi = (rand()%wielkosc);
						if(tab[i].wierzcholekPierwszy==tab[i].wierzcholekDrugi){
							sprawdzenie=true;
						}else{
							if(docelowe[tab[i].wierzcholekDrugi]){
								sprawdzenie=true;
							}else{
								for(int n=0; n<i; n++){
									if((tab[i].wierzcholekPierwszy==tab[n].wierzcholekPierwszy && tab[i].wierzcholekDrugi==tab[n].wierzcholekDrugi)||
									   (tab[i].wierzcholekPierwszy==tab[n].wierzcholekDrugi && tab[i].wierzcholekDrugi==tab[n].wierzcholekPierwszy)){
										sprawdzenie = true;
										break;
									}
								}
							}
							//wylosowanie juz isteniejacej sciezki w dowolnym kierunku
						}			
					}while(sprawdzenie);
				}
					docelowe[tab[i].wierzcholekDrugi]=true;					
			}
			
			for(int i=0; i<wielkosc; i++){
				plik << tab[i].wierzcholekPierwszy << " " << tab[i].wierzcholekDrugi << " " << tab[i].wartosc << endl;	
			}
			 
			for(int i=rozmiar; i<liczbaKrawedzi; i++){
				tab[i].wartosc = (rand()%wielkosc)+1;
				do{
					sprawdzenie=true;
					tab[i].wierzcholekPierwszy = (rand()%wielkosc);
					tab[i].wierzcholekDrugi = (rand()%wielkosc);
					if(tab[i].wierzcholekPierwszy!=tab[i].wierzcholekDrugi){
						for(int n=0; n<i; n++){
							if(rodzaj){
								if((tab[i].wierzcholekPierwszy==tab[n].wierzcholekPierwszy && tab[i].wierzcholekDrugi==tab[n].wierzcholekDrugi)||
								(tab[i].wierzcholekPierwszy==tab[n].wierzcholekDrugi && tab[i].wierzcholekDrugi==tab[n].wierzcholekPierwszy)){
									sprawdzenie = false;
									break;
								}	
							}else{
								if(tab[i].wierzcholekPierwszy==tab[n].wierzcholekPierwszy && tab[i].wierzcholekDrugi==tab[n].wierzcholekDrugi){
									sprawdzenie = false;
									break;
								}		
							}	
						}
					}else{
						sprawdzenie = false;
					}		
				}while(!sprawdzenie);
				
				plik << tab[i].wierzcholekPierwszy << " " << tab[i].wierzcholekDrugi << " " << tab[i].wartosc << endl;
			}
			plik.close();
		}else{
			return false;
		}	
	}else{
		return false;
	}
	}else{
		if(wielkosc<=0){
			return false;
		}else{
			plik << 0 << " " << wielkosc << " " << wielkosc-1 << " " << wielkosc-1 << endl;
		}
	}
	return true;
}


