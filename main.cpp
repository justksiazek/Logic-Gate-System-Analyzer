#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "tuc.h"

int main(int ile, char * argumenty[])
{
    //sprawdzanie flag
    for (int i=0; i<ile; i++)
    {
        if (strcmp(argumenty[i],"-u")==0)
        {
            std::cout << "-u" << std::endl;
            if (i+1 == ile || strncmp(argumenty[i+1],"-*",1)==0)
            {
                std::cout << "blad" << std::endl;
                break;
            }
            else
                std::cout << "plik" << std::endl;
        }
        else if (strcmp(argumenty[i],"-i")==0)
        {
            std::cout << "-i" << std::endl;
            if (i+1 == ile || strncmp(argumenty[i+1],"-*",1)==0)
            {
                std::cout << "blad" << std::endl;
                break;
            }
            else
                std::cout << "plik" << std::endl;
        }
        else if (strcmp(argumenty[i],"-o")==0)
        {
            std::cout << "-o" << std::endl;
            if (i+1 == ile || strncmp(argumenty[i+1],"-*",1)==0)
            {
                std::cout << "blad" << std::endl;
                break;
            }
            else
                std::cout << "plik" << std::endl;
        }
    }
   
   //UWAGA WERSJA TESTOWA - NIE UŻYWA FLAG, TYLKO STAŁYCH PLIKÓW
    /*
    PLIKI
    - uklad.txt
    - stany.txt
    - wyniki.txt
    */
    
    bramka * pBramka = nullptr;
    droga * pDroga = nullptr;
    wynik * pWynik = nullptr;

    std::string linia; std::stringstream ss;
    int wejscie1, wejscie2, wyjscie;

    std::ifstream uklad;
    uklad.open("uklad.txt");
    if (uklad.good())
    {
        std::string br; int we1; int we2; int wy; logiczna typ;
        //odczyt węzłów in
        std::getline(uklad, linia);
        ss.str(linia);
        ss >> br >> we1 >> we2;
        std::cout << br << " " << we1 << " " << we2 << std::endl;
        wejscie1 = we1;
        wejscie2 = we2;
        dodajBramke(pBramka, IN, we1);
        dodajBramke(pBramka, IN, we2);
        ss.clear();
        //odczyt węzła out
        std::getline(uklad, linia);
        ss.str(linia);
        ss >> br >> wy;
        std::cout << br << " " << wy << std::endl;
        wyjscie = wy;
        ss.clear();
        //odczyt bramek
        while(std::getline(uklad, linia))
        {
            ss.str(linia);
            ss >> br >> we1 >> we2 >> wy;
            std::cout << br << " " << we1 << " " << we2 << " " << wy << std::endl;
            typ = rzutowanie(br);
            dodajBramke(pBramka, typ, wy);
            ss.clear();
        }
        //tworzenie dróg
        uklad.clear();
        uklad.seekg(15);
        while(std::getline(uklad, linia))
        {
            ss.str(linia);
            ss >> br >> we1 >> we2 >> wy;
            bramka * pWe1 = szukajWezla(pBramka, we1);
            bramka * pWe2 = szukajWezla(pBramka, we2);
            bramka * pWy = szukajWezla(pBramka, wy);
            dodajDroge (pDroga, pWe1, pWy);
            dodajDroge (pDroga, pWe2, pWy);
            std::cout << we1 << "-" << wy << std::endl;
            std::cout << we2 << "-" << wy << std::endl;
            ss.clear();
        }
    }
    uklad.close();

    std::cout << std::endl;    
    
    std::ifstream stany;
    stany.open("stany.txt");
    if (stany.good())
    {
        int we1, we2, stan1, stan2; char d;
        while(std::getline(stany, linia))
        {
            bramka * pEdit;
            ss.str(linia);
            ss >> we1 >> d >> stan1 >> we2 >> d >> stan2;
            std::cout << we1 << " " << stan1 << " " << we2 << " " << stan2 << std::endl;
            pEdit = szukajWezla(pBramka, we1);
            pEdit->wartosc = stan1;
            pEdit = szukajWezla(pBramka, we2);
            pEdit->wartosc = stan2;
            ss.clear();

            bramka * pStart = nullptr, * pLUB = nullptr, *pKbramka = nullptr;
            droga * pElement = nullptr, * pLUD = nullptr, * pKdroga = nullptr;
            int licznik = licz(pDroga);
            while(licznik != licz(pLUD))
            {
                usunBramke(pKbramka);
                usunDroge(pKdroga);
                kopiujBramki(pBramka, pKbramka, pLUB);
                kopiujDrogi(pDroga, pKdroga, pLUD);
                pStart = szukajBramki(pKbramka);
                pElement = szukajDrogi(pKdroga, pStart->wezel);
                if (!pElement)
                {
                    dodajBramke(pLUB, pStart->typ, pStart->wezel);
                    continue;
                }
                while (pElement->pStop->wartosc != 2)
                {
                    pElement = szukajDrogi(pElement->pNext, pStart->wezel);
                    if (!pElement)
                    {
                        dodajBramke(pLUB, pStart->typ, pStart->wezel);
                        break;
                    }
                }
                if (pElement->pStop->stan == 2)
                    szukajWezla(pBramka, pElement->pStop->wezel)->stan = pStart->wartosc;
                else
                    szukajWezla(pBramka, pElement->pStop->wezel)->wartosc = przetworzWartosc(pBramka, pStart->wartosc);
                
                std::cout << "bramka: " << pElement->pStop->wezel << " stan: " << pElement->pStop->stan<< " wartosc: "<<pElement->pStop->wartosc << std::endl;
                dodajDroge(pLUD, pElement->pStart, pElement->pStop);
            }
            usunBramke(pLUB);
            usunDroge(pLUD);
            usunBramke(pKbramka);
            usunDroge(pKdroga);
            dodajWynik(pWynik, szukajWezla(pBramka, wejscie1)->wartosc, szukajWezla(pBramka, wejscie2)->wartosc, szukajWezla(pBramka, wyjscie)->wartosc);
        }
    }
    stany.close();

    std::ofstream wyniki;
    wyniki.open("wyniki.txt");
    if (wyniki.good())
    {
       zapiszWyniki(pWynik, wyniki, wejscie1, wejscie2, wyjscie);
       std::cout << "koniec zapisu";
    }
    wyniki.close();

    usunWynik(pWynik);
    usunBramke(pBramka);
    usunDroge(pDroga);

    return 0;
}