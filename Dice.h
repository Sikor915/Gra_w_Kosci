#pragma once
#include "Die.h"
#include <map>
#include <Windows.h>
#include "FunctionsH.h"
/**
* @brief Klasa opisujaca zestaw kosci gracza.
* @details Przerzuca kosci, sumuje wartosci.
*/
class dice : public die
{
	std::vector<die> heldDice; /**< Wektor z obiektami klasy "Die" czyli kosciami.*/

public:
	
	/** Funkcja przerzucajaca kosci gracza.
	* @param indexes Indeksy kosci do przerzutu
	* @param canReroll Zmienna boolowska pilnujaca czy gracz moze jeszcze przerzucac
	* @param rerollCounter Licznik przerzutow
	*/
	void Reroll(std::vector<int>& indexes, bool& canReroll, int& rerollCounter);
	/** Funkcja odpowiadajaca za uzyskanie od gracza indeksow kosci do przerzutu.
	* @param indexes Indeksy kosci do przerzutu
	* @param canReroll Zmienna boolowska pilnujaca czy gracz moze jeszcze przerzucac
	* @param rerollCounter Licznik przerzutow
	* @param answer Odpowiedz uzytkownika na pytanie co do przerzutu
	* @param currentPlayerDice Wskaznik na kosci gracza
	* @see Reroll
	*/
	void RollMenu(std::vector<int>& indexes, bool& canReroll, int& rerollCounter, std::string& answer, std::shared_ptr<dice>& currentPlayerDice);
	/** Funkcja rzucajaca kosciami poraz pierwszy.
	*/
	void Roll(); //dorobic cos z funkcja wirtualna moze? Tak zeby byl polimorfizm (To chyba jest to)
	/** Funkcja sumujaca oczka na kosciach.
	* @param square Numer pola do ktorego gracz chce wpisac rzut
	* @param rerollCTR Licznik przerzutow jakie gracz wykonal
	* @see bubbleSort
	*/
	int addValues(int& square, int& rerollCTR);	
	/** Funkcja wypisujaca wektor na ekranie
	*/
	void WriteVector();
	/** Getter wektora z kosciami.
	* @return Wektor z kosciami
	* @see heldDice
	*/
	std::vector<die>& GetDice();	
	/** Konstruktor. Wrzuca do wektora 5 kosci D6.
	*/
	dice();
	/** Destruktor. Nie za wiele robi ale sie stara i za to go cenimy.
	*/
	~dice();
};