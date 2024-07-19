#pragma once
#include "Yahtzee.h"
/**
* @brief Klasa odpowiadajaca za Menu tytulowe gry.
* @details Nie robi zbyt wiele oprocz rysowania Menu Tytulowego na ekranie i odpalania gry.
*/
class MainMenu : public YahtzeeGame
{
	std::string answer;/**< Zmienna przechowujaca odpowiedz gracza. */

public:
	/** Konstruktor. Ustawia zmienna answer na "".
	* @see answer
	*/
	MainMenu();
	/** Dekonstruktor. Nic ciekawego nie robi.
	*/
	~MainMenu();
	/** Funkcja wypisujaca Menu Tytulowe gry.
	* W zaleznosci od wyboru gracza wywoluje poszczegolna wersje gry.
	* @see YahtzeeGameStart
	* @see loadTheGame
	*/
	void DrawMenu();
	/** Funkcja wypisujaca na ekranie zasady gry w kosci.
	*/
	void ShowRules();
	/** Funkcja zwracajaca poszczegolny plik zapisu.
	* @param index Numer zapisanego pliku od 1 do 3.
	* @return Nazwa pliku zapisu
	*/
	std::string getChosenFile(std::string index);
};

