#pragma once
#include "Dice.h"
/**
* @brief Klasa zajmujaca sie karta wynikow gracza.
* @details Zapisuje wynik rzutu, sumuje punkty i wypisuje karte na ekranie.
*/
class scorecard
{
	
	const static int wholeScorecardSize = 13; /**< Wielkosc karty wynikow. */
	int scores[wholeScorecardSize]{ 0 }; /**< Tablica z wynikami gracza. */
	bool isWritten[wholeScorecardSize]{ false }; /**< Tablica z informacja czy cos zostalo wpisane w dana komorke w karcie.*/
	std::shared_ptr<dice> yourDice; /**< Wskaznik na zestaw kosci gracza. */

public:

	/** Funkcja wpisujaca do podanej komorki wynik rzutu.
	* @param index Indeks pola do wpisania
	* @param diceSet Zestaw rzuconych kosci
	* @param rerollCTR Ilosc przerzutow jakie gracz wykonal podczas tury
	* @see addValues
	* @see scores
	*/
	void writeScore(int& index, dice& diceSet, int& rerollCTR);
	
	/** Funkcja ustawiajaca wskaznik na podany zestaw kosci.
	* @param otherSet Wskaznik na inne kosci
	*/
	void setSet(std::shared_ptr<dice>& otherSet);
	/** Funkcja sprawdzajaca czy karty sa pelne.
	* Sprawdza czy wszystkie pola w tablicy isWritten sa ustawione na true.
	* @return True albo false. Zazwyczaj false
	* @see isWritten
	*/
	bool isFull();
	/** Funkcja wypisujaca karte podanego gracza.
	* @param playerName Imie gracza
	*/
	void writePlayersScorecard(std::string& playerName);
	/** Metoda zwracajaca wskaznik na kosci gracza.
	* @return Wskaznik na kosci
	*/
	std::shared_ptr<dice> getSet();
	/** Funkcja zwracajaca tablice wynikow.
	* @return Tablica scores
	* @see scores
	*/
	int* getScorecard();
	/** Funkcja zwracajaca tablice z info co do zapisania karty wynikow.
	* @return Tablica isWritten
	* @see isWritten
	*/
	bool* getIsWritten();
	/** Funkcja zwracajaca sume punktow.
	* @return Zsumowane punkty z karty wynikow
	*/
	int getScore();
	/** Konstruktor. Ustawia wskaznik na nowe kosci.
	*/
	scorecard();
	/** Konstruktor kopiujacy. Ustawia wszystkie dane na takie same jak w podanej karcie.
	* @param otherScorecard Inna karta wynikow
	*/
	scorecard(scorecard& otherScorecard);
	/** Destruktor. Nie za wiele robi.
	*/
	~scorecard();
	/** Operator wypisywania.
	* Wypisuje ladnie wygladajaca i opisana karte wynikow aktualnego gracza.
	* @param os Zwykly ostream
	* @param tmp Karta wynikow gracza
	* @return Ostream os
	*/
	friend std::ostream& operator<<(std::ostream& os, scorecard& tmp);
};
