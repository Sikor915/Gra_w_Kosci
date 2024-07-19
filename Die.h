#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <memory>
/** 
* @brief Klasa bedaca pojedyncza koscia do gry.
* @details Typ kosci: D6.
*/
class die
{
	int number; /**< Zmienna przechowujaca ilosc oczek ktore wypadly.*/

public:
	/** Wirtualna funkcja do losowania ilosci oczek.
	*/
	virtual void Roll();
	/** Funkcja ustawiajaca numer oczek na podany.
	* @param numberOnDie Podana liczba oczek
	*/
	void set(int& numberOnDie);
	/** Funkcja zwracajaca numer na kosci.
	* @return Liczba oczek na kosci
	*/
	int GetNumber();
	/** Konstruktor. Ustawia numer na 1.
	* @see number
	*/
	die();
	/** Destruktor. Nie za wiele robi ale i tak go kochamy.
	*/
	~die();
};


