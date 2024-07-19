#include "Yahtzee.h"

std::map<std::string, std::shared_ptr<scorecard>>& YahtzeeGame::getScorecards()
{
	return scorecardHolder;
}

std::shared_ptr<scorecard> YahtzeeGame::getScorecard(std::string& name)
{
	return scorecardHolder[name];
}

int YahtzeeGame::getPlayerCount()
{
	return players.size();
}

void YahtzeeGame::getPlayersScorecard()
{
	std::cout << "Aktualni gracze: " << std::endl;
	for (int i = 0; i < players.size(); i++)
	{
		std::cout << i + 1 << ". " << players[i] << std::endl;
	}
	int playersIndex{};
	std::string playersName{};
	std::cout << "Ktorego gracza karte chcialbys obejrzec?" << std::endl;
	std::cin >> playersName;
	if (!playersName.empty() && playersName.find_first_not_of("0123456789") != std::string::npos)
	{
		if (scorecardHolder.count(playersName) == 0)
		{
			std::cout << "Taki gracz nie istnieje" << std::endl;
		}
		else
		{
			scorecardHolder[playersName].get()->writePlayersScorecard(playersName);
		}
	}
	else
	{
		if (std::stoi(playersName) > players.size())
		{
			std::cout << "Taki gracz nie istnieje" << std::endl;
		}
		else
		{
			playersName = players.at(std::stoi(playersName) - 1);
			if (scorecardHolder.count(playersName) == 0)
			{
				std::cout << "Taki gracz nie istnieje" << std::endl;
			}
			else
			{
				scorecardHolder[playersName].get()->writePlayersScorecard(playersName);
			}
		}
		
	}
}

void YahtzeeGame::YahtzeeGameStart()
{
	std::string numberOfPlayers{};
	std::cout << "Prosze o podane liczby graczy" << std::endl;
	std::cin >> numberOfPlayers;
	while (numberOfPlayers.find_first_not_of("0123456789") != std::string::npos or std::stoi(numberOfPlayers) <= 0)
	{
		std::cout << "Ilosc graczy musi byc dodatnia liczba calkowita" << std::endl;
		std::cout << "Prosze o podane DODATNIEJ liczby graczy" << std::endl;
		std::cin >> numberOfPlayers;
	}

	for (int i = 0; i < std::stoi(numberOfPlayers); ++i)
	{
		std::shared_ptr<scorecard> blank = std::make_shared<scorecard>();
		std::string playerName{};
		std::cout << "Prosze podac imie " << i + 1 << " gracza." << std::endl;
		std::cin >> playerName;
		scorecardHolder.try_emplace(playerName, blank);
		players.push_back(playerName);
	}
	system("CLS");

	int currentPlayer{ 0 };
	int round{ 0 };
	while (!isGameDone())
	{
		if (currentPlayer == 0)
		{
			round++;
		}
		std::string index{};
		std::shared_ptr<scorecard> currentPlayerScorecard = scorecardHolder[players[currentPlayer]];
		std::shared_ptr<dice> currentPlayerDice = currentPlayerScorecard->getSet();

		std::cout << "Runda " << round << std::endl;
		std::cout << "Gracz " << currentPlayer+1 << ": " << players[currentPlayer] << std::endl << std::endl;
		std::cout << *currentPlayerScorecard;
		std::cout << "Rzuczanie koscmi..." << std::endl;
		currentPlayerDice->Roll();
		int rerollCounter = YahtzeeMenu(currentPlayerScorecard, currentPlayerDice, currentPlayer, round);
		std::cout << *currentPlayerScorecard;
		std::cout << "----------Jezeli twoje rzuty nie pasuja do zadnego pola na karcie wynikow, prosze wpisac nr pola do ktorego wpisac 0 punktow----------" << std::endl;
		std::cout << "Do ktorego pola chcesz wpisac twoj rzut?" << std::endl;
		std::cin >> index;
		while (index.find_first_not_of("0123456789") != std::string::npos or std::stoi(index) <= 0)
		{
			std::cout << "To co wpisales nie jest liczba naturalna. Prosze podac liczbe naturalna!" << std::endl;
			std::cin >> index;
		}
		int indexInt = std::stoi(index);
		currentPlayerScorecard->writeScore(indexInt, *currentPlayerDice, rerollCounter);
		currentPlayer = (currentPlayer + 1) % players.size();
		system("CLS");
	}

	YahtzeeGameEnd();
}

void YahtzeeGame::YahtzeeGameStart(int roundFromFile, std::string currentPlayerS)
{
	auto it = std::find(players.begin(), players.end(), currentPlayerS);
	int currentPlayer{ static_cast<int>(std::distance(players.begin(), it))}, round{roundFromFile}, blocker{0};

	while (!isGameDone())
	{
		if (currentPlayer == 0 and blocker != 0)
		{
			round++;
		}
		std::string index{};
		std::shared_ptr<scorecard> currentPlayerScorecard = scorecardHolder[players[currentPlayer]];
		std::shared_ptr<dice> currentPlayerDice = currentPlayerScorecard->getSet();

		std::cout << "Runda " << round << std::endl;
		std::cout << "Gracz " << currentPlayer + 1 << ": " << players[currentPlayer] << std::endl << std::endl;
		std::cout << *currentPlayerScorecard;
		if (blocker != 0)
		{
			std::cout << "Rzuczanie koscmi..." << std::endl;
			currentPlayerDice->Roll();
		}
		else
		{
			std::cout << "O to twoj zestaw kosci:" << std::endl;
			currentPlayerDice.get()->WriteVector();
		}
		int rerollCounter = YahtzeeMenu(currentPlayerScorecard, currentPlayerDice, currentPlayer, round);
		if (rerollCounter == 5)
		{
			break;
		}
		std::cout << *currentPlayerScorecard;
		std::cout << "----------Jezeli twoje rzuty nie pasuja do zadnego pola na karcie wynikow, prosze wpisac nr pola do ktorego wpisac 0 punktow----------" << std::endl;
		std::cout << "Do ktorego pola chcesz wpisac twoj rzut?" << std::endl;
		std::cin >> index;
		while (index.find_first_not_of("0123456789") != std::string::npos or std::stoi(index) <= 0)
		{
			std::cout << "To co wpisales nie jest liczba naturalna. Prosze podac liczbe naturalna!" << std::endl;
			std::cin >> index;
		}
		int indexInt = std::stoi(index);
		currentPlayerScorecard->writeScore(indexInt, *currentPlayerDice, rerollCounter);
		currentPlayer = (currentPlayer + 1) % players.size();
		if (blocker == 0)
		{
			blocker++;
		}
		system("CLS");
	}

	YahtzeeGameEnd();
}

int YahtzeeGame::YahtzeeMenu(std::shared_ptr<scorecard>& currentPlayerScorecard, std::shared_ptr<dice>& currentPlayerDice, int currentPlayer, int crrRound)
{
	bool isDone{ false };
	std::string action{};
	
	while (!isDone)
	{
		std::cout << "Co chcesz zrobic?" << std::endl;
		std::cout << "1. Przerzucic kosci" << std::endl;
		std::cout << "2. Zobaczyc karte innego gracza" << std::endl;
		std::cout << "3. Wpisac rzut do karty wynikow" << std::endl;
		std::cout << "4. Zapisac aktualny stan gry" << std::endl;
		std::cout << "5. Przedwczesnie zakonczyc gre" << std::endl;
		std::cin >> action;
		if (action == "1")
		{
			std::string answer{ "Y" };
			bool canReroll{ true }, isNegative{ false };
			int rerollCounter{ 0 };
			std::cout << "Zostalo ci " << 3 - rerollCounter << " przerzutow." << std::endl;
			std::vector<int> diceIndexes;
			std::string stringOfIndexes;
			std::cout << "Prosze podac indeksy kosci do przerzutu: " << std::endl;
			std::cin.ignore();
			std::getline(std::cin, stringOfIndexes);
			for (const char& a : stringOfIndexes)
			{
				if (a == '1' or a == '2' or a == '3' or a == '4' or a == '5')
				{
					int index = a - '0';
					if (!isNegative)
					{
						diceIndexes.push_back(index);
					}
					isNegative = false;
				}
				else if (a == '-')
				{
					isNegative = true;
				}
				else
				{
					isNegative = false;
				}
			}
			currentPlayerDice->Reroll(diceIndexes, canReroll, rerollCounter);
			std::cout << "Po przerzuceniu twoja aktualna reka wyglada nastepujaco: " << std::endl;
			currentPlayerDice.get()->WriteVector();

			currentPlayerDice.get()->RollMenu(diceIndexes, canReroll, rerollCounter, answer, currentPlayerDice);

			isDone = true;
			return rerollCounter;
		}
		else if (action == "2")
		{
			getPlayersScorecard();
			currentPlayerDice.get()->WriteVector();
		}
		else if (action == "3")
		{
			isDone = true;
			return 0;
		}
		else if (action == "4")
		{
			std::string saveAnswer{};
			std::cout << "Prosze podac do ktorego pliku zapisac stan gry:" << std::endl;
			std::cout << "1. Save1" << std::endl << "2. Save2" << std::endl << "3. Save3" << std::endl;
			std::cin >> saveAnswer;
			while (saveAnswer != "1" and saveAnswer != "2" and saveAnswer != "3")
			{
				std::cout << "Podano zly indeks pliku!" << std::endl;
				std::cout << "Prosze podac do ktorego pliku zapisac stan gry:" << std::endl;
				std::cout << "1. Save1" << std::endl << "2. Save2" << std::endl << "3. Save3" << std::endl;
				std::cin >> saveAnswer;
			}
			writeScorecardToFile(saveAnswer, currentPlayer, currentPlayerDice, crrRound);
		}
		else if (action == "5")
		{
			for (const auto& a : players)
			{
				for (int i = 0; i < 13; i++)
				{
					scorecardHolder[a].get()->getIsWritten()[i] = true;
				}
			}
			isDone = true;
			return 5;
		}
		else
		{
			std::cout << "Prosze podac poprawna akcje w menu" << std::endl;
		}
	}
}

bool YahtzeeGame::isGameDone()
{
	for (const auto& player : players)
	{
		if (!scorecardHolder[player].get()->isFull())
		{
			return false;
		}
	}
	return true;
}

void YahtzeeGame::YahtzeeGameEnd()
{
	system("CLS");
	std::vector<std::pair<std::string, int>> playerScorePairs;
	for (const auto& a : scorecardHolder)
	{
		int pScore = a.second.get()->getScore();
		playerScorePairs.push_back(std::make_pair(a.first, pScore));
	}
	std::sort(playerScorePairs.begin(), playerScorePairs.end(), comparePairs);

	PlaySound(TEXT("FanfareSFX.wav"), NULL, SND_ASYNC);
	Sleep(2000);
	std::cout << "----- Wyniki -----" << std::endl;
	for (const auto& pair : playerScorePairs) {
		std::cout << "Gracz: " << pair.first << ": " << pair.second << "pkt." << std::endl;
	}
	Sleep(4000);
	
	writeScorecardToFile();
	
}




void YahtzeeGame::writeScorecardToFile()
{
	std::ofstream txtFile("Wyniki.txt", std::ofstream::out);
	if (txtFile.is_open())
	{
		std::vector<std::pair<std::string, int>> playerScorePairs;
		for (const auto& a : scorecardHolder)
		{
			int pScore = a.second.get()->getScore();
			playerScorePairs.push_back(std::make_pair(a.first, pScore));
		}
		std::sort(playerScorePairs.begin(), playerScorePairs.end(), comparePairs);
		txtFile << "----- Wyniki -----" << std::endl;
		for (const auto& pair : playerScorePairs) {
			txtFile << "Gracz: " << pair.first << ": " << pair.second << "pkt." << std::endl;
		}
		txtFile << "----- Karty graczy -----" << std::endl;

		for (auto& playerName : players)
		{
			txtFile << "O to karta gracza " << playerName << ": " << std::endl;
			std::cout << "---------------" << std::endl;
			for (int i = 0; i < 13; i++)
			{
				static std::string isWrittenString{};
				if (i < 6)
				{
					if (this->getScorecard(playerName).get()->getIsWritten()[i] == false)
					{
						isWrittenString = "Nie";
					}
					else
					{
						isWrittenString = "Tak";
					}
					txtFile << "Kategoria " << i + 1 << " (suma wyrzuconych " << i + 1 << "): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;

				}
				else if (i >= 6 and i < 13)
				{
					if (this->getScorecard(playerName).get()->getIsWritten()[i] == false)
					{
						isWrittenString = "Nie";
					}
					else
					{
						isWrittenString = "Tak";
					}
					switch (i)
					{
					case(6):
						txtFile << "---------------" << std::endl;
						txtFile << "Kategoria " << i + 1 << " (3 jednakowe kosci - suma wszystkich oczek): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(7):
						txtFile << "Kategoria " << i + 1 << " (4 jednakowe kosci - suma wszystkich oczek): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(8):
						txtFile << "Kategoria " << i + 1 << " (Full - 3 jednakowe kosci + 2 jednakowe kosci - 25pkt): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(9):
						txtFile << "Kategoria " << i + 1 << " (Maly strit - sekwencja 4 kolejnych oczek - 30pkt): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(10):
						txtFile << "Kategoria " << i + 1 << " (Duzy strit - sekwencja 5 kolejnych oczek - 40pkt): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(11):
						txtFile << "Kategoria " << i + 1 << " (General (Yahtzee) - 5 jednakowych rzutow - 50pkt): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					case(12):
						txtFile << "Kategoria " << i + 1 << " (Szansa - suma wszystkich oczek): " << this->getScorecard(playerName).get()->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
						break;
					default:
						break;
					}
				}
			}

			txtFile << "---------------" << std::endl;
			txtFile << "Suma punktow: " << this->getScorecard(playerName).get()->getScore() << std::endl;
			txtFile << "---------------" << std::endl;
			txtFile << "---------------" << std::endl;
		}
		std::cout << "Udalo sie zapisac wyniki oraz karty graczy do pliku zewnetrznego" << std::endl;
		txtFile.close();
	}
	else
	{
		std::cout << "Nie udalo sie zapisac wynikow do pliku zewnetrznego" << std::endl;
	}
}

void YahtzeeGame::writeScorecardToFile(std::string& saveIndex, int currentPlayer, std::shared_ptr<dice> currentPlayerDice, int crrRound)
{
	int index = std::stoi(saveIndex);
	switch (index)
	{
	case(1):
	{
		std::ofstream txtFile("Save1.txt", std::ofstream::out | std::ofstream::trunc);
		if (txtFile.is_open())
		{
			txtFile << crrRound << " ";
			txtFile << players[currentPlayer] << std::endl;
			for (int i = 0; i < currentPlayerDice.get()->GetDice().size(); i++)
			{
				txtFile << currentPlayerDice.get()->GetDice()[i].GetNumber() << " ";
			}
			txtFile << std::endl;

			for (auto& playerName : players)
			{
				txtFile << playerName << " ";
				for (int i = 0; i < 13; i++)
				{
					txtFile << this->getScorecard(playerName).get()->getScorecard()[i] << " " << this->getScorecard(playerName).get()->getIsWritten()[i] << " ";
				}
				txtFile << std::endl;
			}
			std::cout << "Udalo sie zapisac wyniki oraz karty graczy do pliku zewnetrznego" << std::endl;
			txtFile.close();
		}
		else
		{
			std::cout << "Nie udalo sie zapisac wynikow do pliku zewnetrznego" << std::endl;
		}
		break;
	}
	case(2):
	{
		std::ofstream txtFile("Save2.txt", std::ofstream::out | std::ofstream::trunc);
		if (txtFile.is_open())
		{
			txtFile << crrRound << " ";
			txtFile << players[currentPlayer] << std::endl;
			for (int i = 0; i < currentPlayerDice.get()->GetDice().size(); i++)
			{
				txtFile << currentPlayerDice.get()->GetDice()[i].GetNumber() << " ";
			}
			txtFile << std::endl;

			for (auto& playerName : players)
			{
				txtFile << playerName << " ";
				for (int i = 0; i < 13; i++)
				{
					txtFile << this->getScorecard(playerName).get()->getScorecard()[i] << " " << this->getScorecard(playerName).get()->getIsWritten()[i] << " ";
				}
				txtFile << std::endl;
			}
			std::cout << "Udalo sie zapisac wyniki oraz karty graczy do pliku zewnetrznego" << std::endl;
			txtFile.close();
		}
		else
		{
			std::cout << "Nie udalo sie zapisac wynikow do pliku zewnetrznego" << std::endl;
		}
		break;
	}
	case(3):
	{
		std::ofstream txtFile("Save3.txt", std::ofstream::out | std::ofstream::trunc);
		if (txtFile.is_open())
		{
			txtFile << crrRound << " ";
			txtFile << players[currentPlayer] << std::endl;
			for (int i = 0; i < currentPlayerDice.get()->GetDice().size(); i++)
			{
				txtFile << currentPlayerDice.get()->GetDice()[i].GetNumber() << " ";
			}
			txtFile << std::endl;

			for (auto& playerName : players)
			{
				txtFile << playerName << " ";
				for (int i = 0; i < 13; i++)
				{
					txtFile << this->getScorecard(playerName).get()->getScorecard()[i] << " " << this->getScorecard(playerName).get()->getIsWritten()[i] << " ";
				}
				txtFile << std::endl;
			}
			std::cout << "Udalo sie zapisac wyniki oraz karty graczy do pliku zewnetrznego" << std::endl;
			txtFile.close();
		}
		else
		{
			std::cout << "Nie udalo sie zapisac wynikow do pliku zewnetrznego" << std::endl;
		}
		break;
	}
	default:
		std::cout << "You shouldn't be here" << std::endl;
		break;
	}

}

void YahtzeeGame::loadTheGame(std::string& filename)
{
	std::ifstream inputFile(filename);
	if (inputFile.is_open()) 
	{
		std::string line, currentPlayer, numberString;
		std::getline(inputFile, line);
		std::stringstream os1(line);
		int round{}, numberOnDie{};
		os1 >> round >> currentPlayer;
		std::shared_ptr<dice> playersDice = std::make_shared<dice>();
		std::getline(inputFile, line);
		std::stringstream os2(line);

		for (int i = 0; i < 5; i++)
		{	
			os2 >> numberOnDie;
			playersDice.get()->GetDice()[i].set(numberOnDie);
		}

		while (std::getline(inputFile, line)) 
		{
			std::stringstream ss(line);
			std::string playerName;
			int score;
			bool written{ false };
			ss >> playerName;
			players.push_back(playerName);

			std::shared_ptr<scorecard> playerScorecard = std::make_shared<scorecard>();

			for (int i = 0; i < 13; i++)
			{
				ss >> score >> written;
				playerScorecard.get()->getScorecard()[i] = score;
				playerScorecard.get()->getIsWritten()[i] = written;
			}
			scorecardHolder[playerName] = playerScorecard;
		}
		scorecardHolder[currentPlayer].get()->setSet(playersDice);
		inputFile.close();
		YahtzeeGameStart(round, currentPlayer);
	}
	else 
	{
		std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
	}
}
YahtzeeGame::YahtzeeGame()
{

}

YahtzeeGame::~YahtzeeGame()
{
	std::cout << "Yahtzee game has ended" << std::endl;
}
