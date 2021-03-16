#ifndef TUC_H
#define TUC_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

enum logiczna {NOR, NAND, AND, OR, NEG, XOR, XNOR, IN};

struct droga;

struct bramka {
    int wezel;
    int stan;
    int wartosc;
    logiczna typ;
    bramka * pNext;
};

struct droga {
    bramka * pStart;
    bramka * pStop;
    droga * pNext;
};

struct wynik {
    int wejscie1;
    int wejscie2;
    int wyjscie;
    wynik * pNext;
};

/** Funkcja dodaje nową bramkę do listy bramek
 * @param pHead wskaźnik na początek listy
 * @param gate typ bramki
 * @param num numer węzła w grafie tworzącym mapę bramek
 **/
void dodajBramke (bramka * & pHead, logiczna gate, int num);
/** Funkcja dodaje nowe połączenie do listy połączeń
 * @param pHead wskaźnik na początek listy
 * @param pBegin bramka wychodząca
 * @param pEnd bramka zakańczająca
 **/
void dodajDroge (droga * & pHead, bramka * pBegin, bramka * pEnd);
/** Funkcja dodaje nowy wynik do listy
 * @param pHead wskaźnik na początek listy
 * @param value1 wartość na pierwszym wejściu
 * @param value2 wartość na drugim wejściu
 * @param result wartośc na wyjściu
 **/
void dodajWynik (wynik * & pHead, int value1, int value2, int result);
/** Funkcja wyświetla litę bramek
 * @param pGate wskaźnik na pierwszy element listy
 **/
void wyswietlBramki (bramka * & pGate);
/** Funkcja wyświetla litę  dróg
 * @param pRoad wskaźnik na pierwszy element listy
 **/
void wyswietlDrogi (droga * & pRoad);
/** Funkcja zapisuje do pliku listę wyników
 * @param pHead wskaźnik na listę wyników
 * @param wyniki strumień wyjścia do pliku
 **/
void zapiszWyniki (wynik * & pHead, std::ostream & wyniki, int w1, int w2, int wy);
/** Funkcja usuwa listę bramek
 * @param pHead wskaźnik na początek listy
 **/
void usunBramke (bramka * & pHead);
/** Funkcja usuwa listę połączeń
 * @param pHead wskaźnik na początek listy
 **/
void usunDroge (droga * & pHead);
/** Funkcja usuwa listę wyników
 * @param pHead wskaźnik na początek listy wyników
 **/
void usunWynik (wynik * & pHead);
/** Funkcja przetwarza wartości przekazane do bramki, adekwatnie do typu bramki
 * @param pGate przekazywana bramka
 * @param num wartość na drugim wejściu
 * @return wartość na wyjściu bramki
 **/
int przetworzWartosc(bramka * & pGate, int num);
/** Funkcja rzutuje wartości odczytane z pliku na wartości enum
 * @param read odczytana wartość
 * @return wartość typu enum
 **/
logiczna rzutowanie(std::string read);
/** Funkcja szuka bramki, o odpowiednim numerze węzła
 * @param pBramka początek listy bramek
 * @param node numer węzła poszukiwanej bramki
 * @return adres szukanej bramki
 **/
bramka * szukajWezla(bramka * & pGate, int node);
/** Funkcja szuka bramki, o ustalonej wartości (innej niź 2)
 * @param pBramka początek listy bramek
 * @return adres szukanej bramki
 **/
bramka * szukajBramki(bramka * & pGate);
/** Funkcja szuka drogi, zaczynającej się w odpowiednim węźle i usuwa tę drogę z listy
 * @param pBramka początek listy dróg
 * @param node numer węzła bramki startowej
 * @return adres bramki końcowej
 **/
droga * szukajDrogi(droga * & pDroga, int node);
/** Funkcja kopiuje listę bramek
 * @param pDroga wskaźnik na początek listy dróg
 * @param pKopia wskaźnik na początek kopii listy dróg
 **/
void kopiujDrogi(droga * & pDroga, droga * & pKopia, droga * & pUsed);
void usunElementD(droga * & pElement, droga * & pDroga);
void kopiujBramki(bramka * & pBramka, bramka * & pKopia, bramka * & pUsed);
void usunElementB(bramka * & pElement, bramka * & pBramka);
int licz (droga * & pRoad);



#endif