#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "tuc.h"

void dodajBramke (bramka * & pHead, logiczna gate, int num)
{
    pHead = new bramka {num, 2, 2, gate, pHead};
}
void dodajDroge (droga * & pHead, bramka * pBegin, bramka * pEnd)
{
    pHead = new droga {pBegin, pEnd, pHead};
}
void dodajWynik (wynik * & pHead, int value1, int value2, int result)
{
    pHead = new wynik {value1, value2, result, pHead};
}
void wyswietlBramki (bramka * & pGate)
{
    if (pGate)
    {
        std::cout << pGate->wezel << " ";
        wyswietlBramki(pGate->pNext);
    }
}
void wyswietlDrogi (droga * & pRoad)
{
    if (pRoad)
    {
        std::cout << pRoad->pStart->wezel << "-" << pRoad->pStop->wezel << std::endl;
        wyswietlDrogi (pRoad->pNext);
    }
}
void zapiszWyniki (wynik * & pHead, std::ostream & wyniki, int w1, int w2, int wy)
{
    char d = ':', s = ' '; std::string i = "IN: ", o = "OUT: ";
    while (pHead)
    {
        wyniki << i << w1 << d << pHead->wejscie1 << s << w2 << d << pHead->wejscie2 << s << o << wy << d << pHead->wyjscie << std::endl;
        pHead = pHead->pNext;
    }
}
void usunBramke (bramka * & pHead)
{
    while (pHead)
    {
        bramka * pNastepny = pHead->pNext;
        delete pHead;
        pHead = pNastepny;
    }
}
void usunDroge (droga * & pHead)
{
    while (pHead)
    {
        droga * pNastepny = pHead->pNext;
        delete pHead;
        pHead = pNastepny;
    }
}
void usunWynik (wynik * & pHead)
{
    while (pHead)
    {
        wynik * pNastepny = pHead->pNext;
        delete pHead;
        pHead = pNastepny;
    }
}
int przetworzWartosc(bramka * & pHead, int num)
{
    switch (pHead->typ)
    {
        case NAND:
                    if (pHead->stan == 1 && pHead->stan == num)
                        return 0;
                    else
                        return 1;
                    break;
        case AND:
                    if (pHead->stan == 1 && pHead->stan == num)
                        return 1;
                    else
                        return 0;
                    break;
        case NOR: 
                    if (pHead->stan == 0 && pHead->stan == num)
                        return 1;
                    else
                        return 0;
                    break;
        case OR:
                    if (pHead->stan == 0 && pHead->stan == num)
                        return 0;
                    else
                        return 1;
                    break;
        case XOR:
                    if (pHead->stan != num)
                        return 1;
                    else
                        return 0;
                    break;
        case XNOR:
                    if (pHead->stan == num)
                        return 1;
                    else
                        return 0;
                    break;
    }
}

logiczna rzutowanie(std::string read)
{
    if (read == "NOR")
        return NOR;
    else if (read == "NAND")
        return NAND;
    else if (read == "AND")
        return AND;
    else if (read == "OR")
        return OR;
    else if (read == "NEG")
        return NEG;
    else if (read == "XOR")
        return XOR;
    else
        return XNOR;
}

bramka * szukajWezla(bramka * & pBramka, int node)
{
    if (pBramka->wezel == node)
        return pBramka;
    szukajWezla(pBramka->pNext, node);
}

droga * szukajDrogi(droga * & pDroga, int node)
{
    std::cout << pDroga->pStart->wezel << "-" << pDroga->pStop->wezel << " " << node << std::endl;
    if (pDroga->pStart->wezel == node)
        return pDroga;
    if (pDroga->pNext == nullptr && pDroga->pStart->wezel != node)
        return nullptr;
        
    szukajDrogi(pDroga->pNext, node);
}
void kopiujDrogi(droga * & pDroga, droga * & pKopia, droga * & pUsed)
{
    droga * p = pDroga;
    while (p)
    {
        droga * t = pUsed;
        bool powt = false;
        while (t)
        {
            if (p->pStart->wezel == t->pStart->wezel && p->pStop->wezel == t->pStop->wezel)
            {
                powt = true;
                break;
            }
            t = t->pNext;
        }
        if (powt == false)
        {
            pKopia = new droga {p->pStart, p->pStop, pKopia};
        }
        p=p->pNext;
    }
}
void kopiujBramki(bramka * & pBramka, bramka * & pKopia, bramka * & pUsed)
{
    bramka * p = pBramka;
    while (p)
    {
        bramka * t = pUsed;
        bool powt = false;
        while (t)
        {
            if (p->wezel == t->wezel)
            {
                powt = true;
                break;
            }
            t = t->pNext;
        }
        if (powt == false)
        {
            pKopia = new bramka {p->wezel, p->stan, p->wartosc, p->typ, pKopia};
        }
        p=p->pNext;
    }
}
bramka * szukajBramki(bramka * & pGate)
{
    if (pGate->wartosc != 2)
        return pGate;
    szukajBramki(pGate->pNext);

}
/*
void usunElementD(droga * & pElement, droga * & pDroga)
{
    std::cout << pElement <<std::endl;
    if (pElement->pPrev)
        pElement->pPrev->pNext = pElement->pNext;
    if (pElement->pNext)
    {
        if(!pElement->pPrev)
        {
            pDroga = pElement->pNext;
            pDroga->pPrev = nullptr;
        }
        else
            pElement->pNext->pPrev = pElement->pPrev;
    }
    if (!pElement->pPrev && !pElement->pNext)
        usunDroge(pDroga);
    else
        delete pElement;
        
}
void usunElementB(bramka * & pElement, bramka * & pBramka)
{   
    std::cout << pElement <<std::endl;
    if (pElement->pPrev)
        pElement->pPrev->pNext = pElement->pNext;
    if (pElement->pNext)
    {
        if (!pElement->pPrev)
        {
            pBramka = pElement->pNext;
            pBramka->pPrev = nullptr;
        }
        else
            pElement->pNext->pPrev = pElement->pPrev;
    }
    if (!pElement->pPrev && !pElement->pNext)
        usunBramke(pBramka);       
    else
        delete pElement;
}
*/
int licz (droga * & pRoad)
{
    int i = 0;
    droga * p = pRoad;
    while (p)
    {
        i++;
        p = p->pNext;
    }
    return i;
}