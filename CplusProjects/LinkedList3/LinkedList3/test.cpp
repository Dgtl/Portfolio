#include "intLinkedList.h"

int main(){

	intLinkedList list1 = intLinkedList();
	intLinkedList list2 = intLinkedList();
	intLinkedList list3 = intLinkedList();
	int userNum = 0;
	int splitNum = 0;


	cout << "Enter numbers ending with -999 " << endl;
	while (userNum != -999){

		cin >> userNum;

		if (userNum != -999)
		list1.insertLast(userNum);
		

	}

	cout << "list: ";
	list1.print();
	cout << endl;

	list1.splitEvensOddsList(list2, list3);

	cout << "evensList: ";
	list2.print();
	cout << endl;

	cout << "oddsList: ";
	list3.print();
	cout << endl;

	system("pause");



	return 0;
}