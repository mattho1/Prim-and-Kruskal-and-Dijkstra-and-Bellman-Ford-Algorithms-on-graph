#include "KolejkaPriorytetowa.hpp"


KolejkaPriorytetowa::KolejkaPriorytetowa(){
	korzen=NULL;
	rozmiar=0;
}

KolejkaPriorytetowa::~KolejkaPriorytetowa(){
	Krawedz log;
	do{
		log=pop();
	}while(rozmiar!=0);
}

// metoda wyszukaj sluzy do wyszukiwania elementu
// metoda wyszukuje element struktury, ktorego wartosc jest rowna wartosci argumentu wejsciowego
// metoda zwraca wskaznik na znaleziony wezel
// uwaga: gdy jest wiecej elementow o takiej samej wartosci metoda zwroci najblizszy korzeniowi 

//Wezel* KolejkaPriorytetowa::wyszukaj(int wartosc){ 
//	Wezel* tmp;
//	tmp=korzen;
//	while(tmp!=NULL){
//		if(tmp->wartosc==wartosc){
//			return tmp;
//		}else{
//			if(tmp->wartosc<wartosc){
//				tmp=tmp->prawySyn;
//			}else{
//				tmp=tmp->lewySyn;
//			}	
//		}
//	}	
//	return tmp;
//}

void  KolejkaPriorytetowa::push(Krawedz krawedz){
	if(rozmiar==0){
		Wezel* nowy;
		nowy=new Wezel();
		nowy->krawedz=krawedz;
		nowy->wartosc=krawedz.wartosc;
		nowy->lewySyn=NULL;
		nowy->prawySyn=NULL;
		nowy->rodzic=NULL;
		korzen=nowy;
		rozmiar++;
	}else{
		Wezel* tmp,* nowy;
		nowy=new Wezel();
		tmp=korzen;
		do{
			if(tmp->wartosc>=krawedz.wartosc){
				if(tmp->prawySyn==NULL){
					nowy->wartosc=krawedz.wartosc;
					nowy->krawedz=krawedz;
					nowy->rodzic=tmp;
					tmp->prawySyn=nowy;
					nowy->prawySyn=NULL;
					nowy->lewySyn=NULL;
					rozmiar++;
					break;
				}else{
					tmp=tmp->prawySyn;
				}
			}else{
				if(tmp->lewySyn==NULL){
					nowy->wartosc=krawedz.wartosc;
					nowy->krawedz=krawedz;
					nowy->rodzic=tmp;
					tmp->lewySyn=nowy;
					nowy->prawySyn=NULL;
					nowy->lewySyn=NULL;
					rozmiar++;
					break;
				}else{
					tmp=tmp->lewySyn;
				}
			}
		}while(tmp!=NULL); //zawsze ma byc true
	}
}

// metoda znajduje nastepnik elementu podanego jako argument
// metoda zwraca wskaznik na znaleziony element

Wezel * KolejkaPriorytetowa::znajdzNastepnik(Wezel * szukany){
  Wezel * tmp;
  if(szukany!=NULL){
    if(szukany->lewySyn!=NULL){
    	tmp=szukany->lewySyn;
    	if(tmp!=NULL){
    		while(tmp->prawySyn!=NULL){
    			tmp = tmp->prawySyn;
			} 
		}
  		return tmp;	
	}else{
      tmp = szukany->rodzic;
      while((tmp!=NULL) && (szukany == tmp->lewySyn)){
        szukany = tmp;
        tmp = tmp->rodzic;
      }
      return tmp;
    }
  }
  return szukany;
}

Wezel*  KolejkaPriorytetowa::min(){
	Wezel* tmp=korzen;
	while(tmp!=NULL){
		if(tmp->prawySyn!=NULL){
			tmp=tmp->prawySyn;
		}else{
			return tmp;
		}
	}
	return tmp;
}

// metoda sluzy do usuwania wezla z drzewa
// metoda zwraca wartosc logiczna
// true - gdy usunie wezel
// false - gdy nie usunie lub drzewo jest puste

Krawedz  KolejkaPriorytetowa::pop(){
	Wezel* tmp;
	Wezel*znalezionyElement=min();
	Krawedz zwracana;
	zwracana = znalezionyElement->krawedz;
		
		if(rozmiar==1){
			rozmiar--;
			delete korzen;
			return zwracana;
		}else{
			if(znalezionyElement->prawySyn==NULL&&znalezionyElement->lewySyn==NULL){
					if(znalezionyElement->wartosc>znalezionyElement->rodzic->wartosc){ 
						znalezionyElement->rodzic->lewySyn=NULL;
						delete znalezionyElement;
					}else{
						znalezionyElement->rodzic->prawySyn =NULL;
						delete znalezionyElement;
					}
				rozmiar--;
				return zwracana;	
			}else{
				if(znalezionyElement->prawySyn!=NULL&&znalezionyElement->lewySyn!=NULL){
					tmp=znajdzNastepnik(znalezionyElement);
					if(znalezionyElement->lewySyn!=tmp&&znalezionyElement->prawySyn!=tmp){
						if(tmp->lewySyn!=NULL){
							tmp->lewySyn->rodzic=tmp->rodzic;
							if(tmp->rodzic->lewySyn==tmp){
								tmp->rodzic->lewySyn=tmp->lewySyn;
							}else{
								tmp->rodzic->prawySyn=tmp->lewySyn;
							}	
						}else{
								if(tmp->rodzic->lewySyn==tmp){
									tmp->rodzic->lewySyn=NULL;
								}else{
									tmp->rodzic->prawySyn=NULL;
								}
								
						}
					}			
					if(znalezionyElement!=korzen){
						if(znalezionyElement->rodzic->lewySyn==znalezionyElement){
							znalezionyElement->rodzic->lewySyn=tmp;
							tmp->rodzic=znalezionyElement->rodzic;
						}else{
							znalezionyElement->rodzic->prawySyn=tmp;
							tmp->rodzic=znalezionyElement->rodzic;	
						}	
					}else{
						tmp->rodzic=NULL;
						korzen=tmp;
					}
					
					if(znalezionyElement->prawySyn!=tmp){
						tmp->prawySyn=znalezionyElement->prawySyn;
						znalezionyElement->prawySyn->rodzic=tmp;
					}
					if(znalezionyElement->lewySyn!=tmp){
						tmp->lewySyn=znalezionyElement->lewySyn;
						znalezionyElement->lewySyn->rodzic=tmp;
					}
					delete znalezionyElement;
					rozmiar--;	
					return zwracana;
				}else{
					if(znalezionyElement!=korzen){
					if(znalezionyElement->wartosc>=znalezionyElement->rodzic->wartosc){
						if(znalezionyElement->lewySyn==NULL){
							znalezionyElement->rodzic->prawySyn=znalezionyElement->prawySyn;
							znalezionyElement->prawySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}else{
							znalezionyElement->rodzic->prawySyn=znalezionyElement->lewySyn;
							znalezionyElement->lewySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}	
					}else{
						if(znalezionyElement->lewySyn==NULL){
							znalezionyElement->rodzic->lewySyn=znalezionyElement->prawySyn;
							znalezionyElement->prawySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}else{
							znalezionyElement->rodzic->prawySyn=znalezionyElement->lewySyn;
							znalezionyElement->lewySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}
					}	
					}else{
						if(znalezionyElement->prawySyn!=NULL){
							tmp=znalezionyElement->prawySyn;
							delete korzen;
							tmp->rodzic=NULL;
							korzen=tmp;
						}else{
							tmp=znalezionyElement->lewySyn;
							delete korzen;
							tmp->rodzic=NULL;
							korzen=tmp;
						}
					}
				}
				rozmiar--; 
				return zwracana; 
			}  
		}  

	return zwracana;
}

