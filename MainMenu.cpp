#include "MainMenu.h"

MainMenu::MainMenu()
{
	answer = "";
}

MainMenu::~MainMenu()
{

}

void MainMenu::DrawMenu()
{
	std::cout << "--------------------YAHTZEE GAME--------------------" << std::endl;
	std::cout << "    Witam w znanej na calym swiecie gry w kosci!    " << std::endl;
	std::cout << "     Czy jestescie gotow na gre pelna przygood?     " << std::endl;
	std::cout << "1. Nowa Gra" << std::endl;
	std::cout << "2. Wczytaj Gre" << std::endl;
	std::cout << "3. Nie, prosze wypusc mnie :(" << std::endl;
	std::cin >> answer;
	while (answer != "1" and answer != "2" and answer != "3")
	{
		std::cout << "                Zapytam jeszcze raz.                " << std::endl;
		std::cout << "     Czy jestescie gotow na gre pelna przygood?     " << std::endl;
		std::cout << "1. Nowa Gra" << std::endl;
		std::cout << "2. Wczytaj Gre" << std::endl;
		std::cout << "3. NIE, prosze wylacz aplikacje" << std::endl;
		std::cin >> answer;
	}
	if (answer == "3")
	{
		system("CLS");
		std::cout << "No to co ty tutaj jeszcze robisz?" << std::endl;
	}
	else
	{
		if (answer == "1")
		{
			ShowRules();
			YahtzeeGameStart();
		}
		else if (answer == "2")
		{
			std::string chosenFile;
			std::cout << "Prosze podac numer pliku zapisu: \n";
			std::cout << "1. Save1" << std::endl << "2. Save2" << std::endl << "3. Save3" << std::endl;
			std::cin >> chosenFile;
			chosenFile = getChosenFile(chosenFile);
			if (chosenFile != "ERROR")
			{
				system("CLS");
				loadTheGame(chosenFile);
			}
			std::cout << "Program dokona autodestrukcji" << std::endl;
		}
		else
		{
			std::cout << "Nie powinno cie tu byc" << std::endl;
		}
	}
}

void MainMenu::ShowRules()
{
	std::cout << "\nO to sa zasady grania w kosci: " << std::endl;
	std::cout << "1. Kazdy gracz posiada swoja wlasna karte z wynikami z 13 polami." << std::endl;
	std::cout << "2. W swojej turze gracz wykonuje rzut 5 kosciami D6 i moze wykonac kilka akcji: " << std::endl;
	std::cout << "	2.1 Przerzucic wybrane kosci, wpisac rzut do karty wynikow lub zobaczyc karte innego gracza" << std::endl;
	std::cout << "	2.2 Dodatkowo moze on zapisac aktualny stan gry lub ja zakonczyc przedwczesnie." << std::endl;
	std::cout << "3. Gra konczy sie kiedy kazdy gracz zapisze wszystkie pola w karcie." << std::endl;
	std::cout << "4. Na koniec gry program pokaze wyniki i zapisze je do pliku tekstowego." << std::endl;
	std::cout << "Capiche?\n" << std::endl;
}

std::string MainMenu::getChosenFile(std::string index)
{
	if (index == "1" or index == "Save1")
	{
		return "Save1.txt";
	}
	else if (index == "2" or index == "Save2")
	{
		return "Save2.txt";
	}
	else if (index == "3" or index == "Save3")
	{
		return "Save3.txt";
	}
	else
	{
		std::cout << "Podano niepoprawny indeks!" << std::endl;
		return "ERROR";
	}
}
