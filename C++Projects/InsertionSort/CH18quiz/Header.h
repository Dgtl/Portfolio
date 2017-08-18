#include <cstdlib>
#include <iostream>
using namespace std;

void print_array(int array[], int size) {
	cout << "buble sort steps: ";
	int j;
	for (j = 0; j<size; j++)
		cout << " " << array[j];
	cout << endl;
}//end of print_array

void bubble_sort(int arr[], int size) {
	bool not_sorted = true;
	int j = 1, tmp;

	while (not_sorted)  {
		not_sorted = false;
		j++;
		for (int i = 0; i < size - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				not_sorted = true;

			}//end of if
			print_array(arr, 8);
		}//end of for loop
	}//end of while loop
}//end of bubble_sort

