#include "unorderedLinkedList.h"

int main(){

	unorderedLinkedList<int> list1 = unorderedLinkedList<int>();
	unorderedLinkedList<int> list2 = unorderedLinkedList<int>();
	int userNum = 0;
	int splitNum = 0;


	cout << "Enter numbers ending with -999 " << endl;
	while (userNum != -999){

		cin >> userNum;

		if (userNum != -999)
		list1.insertLast(userNum);
		

	}

	cout << "Enter the number at which to split list: ";
	cin >> splitNum;
	cout << endl;
	list1.divideAt(list2, splitNum);

	cout << "List one and List two after splitting at " << splitNum << endl;
	cout << "List one: ";
	list1.print();
	cout << endl;
	cout << "Length of list: " << list1.length() << endl;

	cout << "List two: ";
	list2.print();
	cout << endl;
	cout << "Length of list: " << list2.length() << endl;

	system("pause");

	list1.initializeList();
	list2.initializeList();



	return 0;
}