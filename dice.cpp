#include "Dice.h"



void dice::Reroll(std::vector<int>& indexes, bool& canReroll, int& rerollCounter)
{
	if (canReroll == true)
	{
		PlaySound(TEXT("diceThrowingSFX.wav"), NULL, SND_ASYNC);
		for (int i = 0; i < indexes.size(); i++) {
			int index{indexes[i] - 1};
			heldDice[index].Roll();
		}
		rerollCounter++;
		if (rerollCounter == 3)
		{
			canReroll = false;
		}
	}
}

void dice::RollMenu(std::vector<int>& indexes, bool& canReroll, int& rerollCounter, std::string& answer, std::shared_ptr<dice>& currentPlayerDice)
{
	while (canReroll and (answer == "Y" or answer == "T" or answer == "Yes" or answer == "Tak"))
	{
		answer.clear();
		std::cout << "Czy chcesz przerzucic swoje kosci(Y/N)?" << std::endl;
		std::cout << "Zostalo ci " << 3 - rerollCounter << " przerzutow." << std::endl;
		std::cin >> answer;
		if (answer == "Y" or answer == "Yes" or answer == "T" or answer == "Tak" or answer == "yes" or answer == "tak")
		{
			std::vector<int> diceIndexes;
			std::string stringOfIndexes;
			bool isNegative{ false };
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
		}
	}
}

void dice::Roll ()
{
	PlaySound(TEXT("diceThrowingSFX"), NULL, SND_ASYNC);
	for (int i = 0; i < this->heldDice.size(); i++)
	{
		heldDice[i].Roll();
		std::cout << "Na kosci nr " << i+1 << " wypadlo " << heldDice[i].GetNumber() << "!" << std::endl;
	}

}
int dice::addValues(int& square, int& rerollCTR)
{
	int score{};
	int tmp{};
	std::map<int, int> tmpMap; //tmpMap to mapa zliczaj¹ca ile razy pojawi³a siê koœæ z danym oczkiem
	int tmpArray[5]{}; //u¿ywane do posortowania koœci (wykorzystywane w drugiej po³owie karty)

	for (int i = 0; i < heldDice.size(); i++)
	{
		tmpArray[i] = heldDice[i].GetNumber();
		int tempIndex = heldDice[i].GetNumber();
		tmpMap[tempIndex]++;
	}
	bubbleSort(tmpArray, 5);
	switch (square)
	{
	case(1): 
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 1)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(2):
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 2)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(3):
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 3)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(4):
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 4)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(5):
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 5)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(6):
		for (int i = 0; i < heldDice.size(); i++)
		{
			if (heldDice[i].GetNumber() == 6)
			{
				score += heldDice[i].GetNumber();
			}
		}
		break;
	case(7):
		if (tmpMap[1] >= 3 || tmpMap[2] >= 3 || tmpMap[3] >= 3 || tmpMap[4] >= 3 || tmpMap[5] >= 3 || tmpMap[6] >= 3 )
		{
			for (int i = 0; i < heldDice.size(); i++)
			{
				score += heldDice[i].GetNumber();
			}
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(8):
		if (tmpMap[1] >= 4 || tmpMap[2] >= 4 || tmpMap[3] >= 4 || tmpMap[4] >= 4 || tmpMap[5] >= 4 || tmpMap[6] >= 4 )
		{
			for (int i = 0; i < heldDice.size(); i++)
			{
				score += heldDice[i].GetNumber();
			}
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(9):
		if ((((tmpArray[0] == tmpArray[1]) && (tmpArray[1] == tmpArray[2])) && // Three of a Kind
			(tmpArray[3] == tmpArray[4]) && // Two of a Kind
			(tmpArray[2] != tmpArray[3])) ||
			((tmpArray[0] == tmpArray[1]) && // Two of a Kind
				((tmpArray[2] == tmpArray[3]) && (tmpArray[3] == tmpArray[4])) && // Three of a Kind
				(tmpArray[1] != tmpArray[2])))
		{
			score = 25;
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(10):
		for (int j = 0; j < 4; j++)
		{
			int temp = 0;
			if (tmpArray[j] == tmpArray[j + 1])
			{
				temp = tmpArray[j];
				for (int k = j; k < 4; k++)
				{
					tmpArray[k] = tmpArray[k + 1];
				}
				tmpArray[4] = temp;
			}
		}
		if (((tmpArray[0] == 1) && (tmpArray[1] == 2) && (tmpArray[2] == 3) && (tmpArray[3] == 4)) ||
			((tmpArray[0] == 2) && (tmpArray[1] == 3) && (tmpArray[2] == 4) && (tmpArray[3] == 5)) ||
			((tmpArray[0] == 3) && (tmpArray[1] == 4) && (tmpArray[2] == 5) && (tmpArray[3] == 6)) ||
			((tmpArray[1] == 1) && (tmpArray[2] == 2) && (tmpArray[3] == 3) && (tmpArray[4] == 4)) ||
			((tmpArray[1] == 2) && (tmpArray[2] == 3) && (tmpArray[3] == 4) && (tmpArray[4] == 5)) ||
			((tmpArray[1] == 3) && (tmpArray[2] == 4) && (tmpArray[3] == 5) && (tmpArray[4] == 6)))
		{
			score = 30;
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(11):
		if (((tmpArray[0] == 1) &&
			(tmpArray[1] == 2) &&
			(tmpArray[2] == 3) &&
			(tmpArray[3] == 4) &&
			(tmpArray[4] == 5)) ||
			((tmpArray[0] == 2) &&
				(tmpArray[1] == 3) &&
				(tmpArray[2] == 4) &&
				(tmpArray[3] == 5) &&
				(tmpArray[4] == 6)))
		{
			score = 40;
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(12):
		if (tmpMap[1] == 5 || tmpMap[2] == 5 || tmpMap[3] == 5 || tmpMap[4] == 5 || tmpMap[5] == 5 || tmpMap[6] == 5)
		{
			score = 50;
			if (rerollCTR == 0)
			{
				score *= 2;
			}
		}
		break;
	case(13):
		for (int i = 0; i < heldDice.size(); i++)
		{
			score += heldDice[i].GetNumber();
		}
		break;
	default:
		std::cout << "Wrong choice." << std::endl;
		break;
	}
	return score;
}

void dice::WriteVector()
{
	for (int i = 0; i < this->heldDice.size(); i++)
	{
		std::cout << "Kosc nr " << i + 1 << ": " << this->heldDice[i].GetNumber() << std::endl;
	}
}

std::vector<die>& dice::GetDice()
{
	return heldDice;
}

dice::dice()
{
	
	for (int i = 0; i < 5; i++)
	{
		die oneDie;
		heldDice.push_back(oneDie);
	}
}

dice::~dice()
{
	
}

