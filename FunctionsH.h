#pragma once
#include <vector>
#include <string>
#include <istream>
#include <sstream>
/** Bubble Sort wykorzystany na potrzeby sumowania ilosci oczek na kosciach.
* @param arr Tablica z oczkami ktore wypadly na kosciach
* @param n Rozmiar tablicy "arr"
*/
void bubbleSort(int arr[], int n);
/** Funkcja porownujaca pary <string, int>.
* @param a Para pierwsza
* @param b Para druga
*/
bool comparePairs(const std::pair<std::string, int>& a, std::pair<std::string, int>& b);
