#include "FunctionsH.h"

void bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);

				swapped = true;
			}
		}

		// IF no two elements were swapped
		// by inner loop, then break
		if (swapped == false)
			break;
	}
}
bool comparePairs(const std::pair<std::string, int>& a, std::pair<std::string, int>& b) {
	return a.second > b.second;
}