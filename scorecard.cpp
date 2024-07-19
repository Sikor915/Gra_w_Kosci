#include "Scorecard.h"


void scorecard::writeScore(int& index, dice& diceSet, int& rerollCTR)
{
	while (this->getIsWritten()[index-1] == true or index > this->wholeScorecardSize or index <= 0)
	{
		std::cout << "Nie mozesz tutaj wpisac rzutu!" << std::endl;
		std::cout << "Prosze podac inny indeks pola: " << std::endl;
		std::cin >> index;
	}
	if (isWritten[index - 1] == false)
	{
		int value = diceSet.addValues(index, rerollCTR);
		scores[index - 1] = value;
		isWritten[index - 1] = true;
	}
}

void scorecard::setSet(std::shared_ptr<dice>& otherSet)
{
	yourDice = otherSet;
}

bool scorecard::isFull()
{
	bool full{ true };
	for (int i = 0; i < wholeScorecardSize; i++)
	{
		if (isWritten[i] == false)
		{
			full = false;
		}
	}
	
	return full;
}

void scorecard::writePlayersScorecard(std::string& playerName)
{
	std::cout << "O to karta gracza " << playerName << ": " << std::endl;
	std::cout << "---------------" << std::endl;
	for (int i = 0; i < this->wholeScorecardSize; i++)
	{
		static std::string isWrittenString{};
		if (i < 6)
		{
			if (this->isWritten[i] == false)
			{
				isWrittenString = "Nie";
			}
			else
			{
				isWrittenString = "Tak";
			}
			std::cout << "Kategoria " << i + 1 << " (suma wyrzuconych " << i + 1 << "): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;

		}
		else if (i >= 6 and i < this->wholeScorecardSize)
		{
			if (this->isWritten[i] == false)
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
				std::cout << "---------------" << std::endl;
				std::cout << "Kategoria " << i + 1 << " (3 jednakowe kosci - suma wszystkich oczek): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(7):
				std::cout << "Kategoria " << i + 1 << " (4 jednakowe kosci - suma wszystkich oczek): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(8):
				std::cout << "Kategoria " << i + 1 << " (Full - 3 jednakowe kosci + 2 jednakowe kosci - 25pkt): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(9):
				std::cout << "Kategoria " << i + 1 << " (Maly strit - sekwencja 4 kolejnych oczek - 30pkt): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(10):
				std::cout << "Kategoria " << i + 1 << " (Duzy strit - sekwencja 5 kolejnych oczek - 40pkt): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(11):
				std::cout << "Kategoria " << i + 1 << " (General (Yahtzee) - 5 jednakowych rzutow - 50pkt): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(12):
				std::cout << "Kategoria " << i + 1 << " (Szansa - suma wszystkich oczek): " << this->getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			default:
				break;
			}
		}
	}
	
	std::cout << "---------------" << std::endl;
}

std::shared_ptr<dice> scorecard::getSet()
{
	return yourDice;
}

int* scorecard::getScorecard()
{
	return scores;
}

bool* scorecard::getIsWritten()
{
	return isWritten;
}

int scorecard::getScore()
{
	int score{ 0 };
	for (int i = 0; i < wholeScorecardSize; i++)
	{
		score += scores[i];
	}
	return score;
}
scorecard::scorecard()
{
	yourDice = std::make_shared<dice>();
}

scorecard::scorecard(scorecard& otherScorecard)
{
	for (int i = 0; i < wholeScorecardSize; i++)
	{
		this->isWritten[i] = otherScorecard.getIsWritten()[i];
		this->scores[i] = otherScorecard.getScorecard()[i];
	}
	this->yourDice = std::make_shared<dice>(*otherScorecard.yourDice.get());
}
scorecard::~scorecard()
{
}

std::ostream& operator<<(std::ostream& os, scorecard& tmp)
{
	os << "O to twoja karta: " << std::endl;
	os << "---------------" << std::endl;
	for (int i = 0; i < tmp.wholeScorecardSize; i++)
	{
		static std::string isWrittenString{};
		if (i < 6)
		{
			if (tmp.isWritten[i] == false)
			{
				isWrittenString = "Nie";
			}
			else
			{
				isWrittenString = "Tak";
			}
			os << "Kategoria " << i + 1 << " (suma wyrzuconych " << i + 1 << "): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;

		}
		else if (i >=6 and i < tmp.wholeScorecardSize)
		{
			if (tmp.isWritten[i] == false)
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
				os << "---------------" << std::endl;
				os << "Kategoria " << i + 1 << " (3 jednakowe kosci - suma wszystkich oczek): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(7):
				os << "Kategoria " << i + 1 << " (4 jednakowe kosci - suma wszystkich oczek): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(8):
				os << "Kategoria " << i + 1 << " (Full - 3 jednakowe kosci + 2 jednakowe kosci - 25pkt): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(9):
				os << "Kategoria " << i + 1 << " (Maly strit - sekwencja 4 kolejnych oczek - 30pkt): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(10):
				os << "Kategoria " << i + 1 << " (Duzy strit - sekwencja 5 kolejnych oczek - 40pkt): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(11):
				os << "Kategoria " << i + 1 << " (General (Yahtzee) - 5 jednakowych rzutow - 50pkt): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			case(12):
				os << "Kategoria " << i + 1 << " (Szansa - suma wszystkich oczek): " << tmp.getScorecard()[i] << "pkt" << " --- " << "Czy zostalo tu cos juz wpisane? - " << isWrittenString << std::endl;
				break;
			default:
				break;
			}
		}
	}
	os << "Pamietaj ze jezeli rzucisz cos z reki (tzn. bez przerzucania) to dostajesz podwojne punkty do danej kategorii (tylko dla 2 polowy karty)!" << std::endl;
	
	os << "---------------" << std::endl;

	return os;
}
