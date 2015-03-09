#include "unorderedLinkedList.h"
#include <random>

int main(){

	unorderedLinkedList<int> list1 = unorderedLinkedList<int>();
	unorderedLinkedList<int> list2 = unorderedLinkedList<int>();
	int rndNum = 0;

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(1, 100);

	rndNum = distribution(generator);

	for (int i = 1; i <= rndNum; i++){ //fill with random number
		list1.insertLast(i);
	}

	list1.divideMid(list2);

	cout << "Printing list one: " << endl;
	list1.print();
	cout << endl;

	cout << "Printing list two: " << endl;
	list2.print();
	cout << endl;

	system("pause");

	list1.initializeList();
	list2.initializeList();



	return 0;
}