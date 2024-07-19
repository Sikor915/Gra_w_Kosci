#pragma once
#include "Scorecard.h"
#include <stdlib.h>
#include <fstream>
/**
* @brief Klasa ktora jest calym kontrolerem gry w kosci.
* @details Zajmuje sie ona wszystkim: Pilnuje gry, czynow graczy, wynikow itp.
* Zdecydowanie najwieksza i najbardziej rozbudowana klasa w programie
*/
class YahtzeeGame
{
	std::map<std::string, std::shared_ptr<scorecard>> scorecardHolder; /**< Mapa z wskaznikami na karty graczy. */
	std::vector<std::string> players; /**< Wektor z imionami graczy. */

public:
	/** Funkcja zwracajaca mape.
	* @see scorecardHolder
	* @return Mapa z wskaznikami
	*/
	std::map<std::string, std::shared_ptr<scorecard>>& getScorecards();
	/** Funkcja zwracajaca wskaznik na karte podanego gracza.
	* @param name Imie gracza
	* @return Wskaznik na karte tego gracza
	* @see scorecardHolder
	*/
	std::shared_ptr<scorecard> getScorecard(std::string& name);
	/** Funkcja zwracajaca ilosc graczy.
	* @return Liczba grajacych osob
	*/
	int getPlayerCount();
	/** Funkcja zajmujaca sie wypisywaniem karty podanego gracza.
	*/
	void getPlayersScorecard();
	/** Funkcja startujaca gre.
	* Startuje kompletnie nowa gra z wybrana iloscia osob.
	*/
	void YahtzeeGameStart();
	/** Przeciazona funkcja startujaca gre.
	* Przyjmuje parametry zwiazane z zapisana wczesniej gra.
	* @param roundFromFile Aktualna runda zczytana z pliku zapisu
	* @param currentPlayerS Imie aktualnego gracza (tego ktory zapisal)
	* @see loadTheGame
	*/
	void YahtzeeGameStart(int roundFromFile, std::string currentPlayerS);
	/** Metoda przedstawiajaca dozwolone czynnosci podczas rozgrywki.
	* Gracz podczas swojej tury moze przerzucic wybrane kosci 3 razy, podejrzec karte innego gracza, zapisac stan rozgrywki, badz zakonczyc ja wczesniej.
	* @param currentPlayerScorecard Karta aktualnego gracza
	* @param currentPlayerDice Zestaw kosci aktualnego gracza
	* @param currentPlayer Indeks aktualnego gracza
	* @param crrRound Numer rundy
	* @return Liczba przerzutow jaka gracz wykonal
	*/
	int YahtzeeMenu(std::shared_ptr<scorecard>& currentPlayerScorecard, std::shared_ptr<dice>& currentPlayerDice, int currentPlayer, int crrRound);
	/** Funkcja sprawdzajaca czy gre nalezy zakonczyc.
	* Sprawdza czy wszystkie pola w kartach graczy zostaly zapisane.
	* @return True albo false. W wiekszosci przypadkow False
	*/
	bool isGameDone();
	/** Funkcja zajmujaca sie zakonczeniem gry.
	* Zpisuje i sortuje wyniki, wypisuje je z fanfarami i zapisuje je do pliku txt.
	* @see writeScorecardToFile
	* @see comparePairs		
	*/
	void YahtzeeGameEnd();
	/** Funkcja wpisujaca karty graczy i wyniki do pliku txt.
	* @see YahtzeeGameEnd
	*/
	void writeScorecardToFile();
	/** Przeciazona funkcja ktora zapisuje stan gry.
	* Zapisuje runde, aktualnego gracza i dane kart wynikow graczy.
	* @param saveIndex Indeks do ktorego pliku zapisac stan gry
	* @param currentPlayer Indeks aktualnego gracza
	* @param currentPlayerDice Zestaw kosci aktualnego gracza
	* @param crrRound Aktualna runda
	* @see YahtzeeMenu
	*/
	void writeScorecardToFile(std::string& saveIndex, int currentPlayer , std::shared_ptr<dice> currentPlayerDice, int crrRound);
	/** Funkcja wczytujaca zapisany stan gry.
	* @param filename Nazwa pliku z ktorego wczytujemy stan gry
	*/
	void loadTheGame(std::string& filename);
	/** Konstruktor. Tyle.
	*/
	YahtzeeGame();
	/** Dekonstruktor. Mowi ze gra sie zakonczyla.
	*/
	~YahtzeeGame();
};
