/* 
 * File:   unorderedSetTest.cpp
 * 
 */

#include <iostream>
#include "unorderedSetType.h"

using namespace std;

int main(){

	int retr;

	unorderedSetType set(100);

	// Show that insertAt() is working correctly

	cout << "Starting insertAt test..." << endl;

	for (int i = 0; i <= (set.maxListSize() / 2); i++){
		set.insertAt(i, (i * 2));
	}

	for (int i = 0; i <= (set.maxListSize() / 2); i++){
		set.retrieveAt(i, retr);
		cout << retr << endl;
	}

	set.insertAt(1, 2); //none of these work
	set.insertAt(10, 4);
	set.insertAt(89, 66);
	set.insertAt(100, 34);
	set.insertAt(54, 88);
	set.insertAt(76, 24);

	set.removeAt(1);
	set.insertAt(1, 3); //this one does because it is not a duplicate
	set.retrieveAt(1, retr);
	cout << "Since 3 was not a duplicate, I inserted it at index 1. See: " << retr << endl;

	// Show that insertAtEnd() is working correctly

	cout << "Starting insertAtEnd test..." << endl;

	set.insertEnd(101);
	set.insertEnd(34); //causes duplicate error

	set.retrieveAt(51, retr);
	cout << "The number 101 should be appended here: " << retr << endl;

	// Show that replaceAt() is working correctly

	set.replaceAt(51, 900);
	set.retrieveAt(51, retr);
	cout << "Replacement should be 900: " << retr << endl;
	set.replaceAt(51, 4); //fails because duplicate



	// Union Test

	cout << "Starting setUnion test..." << endl;

	unorderedSetType set2(100);
	set2.insertEnd(1);
	set2.insertEnd(2);
	set2.insertEnd(3);
	set2.insertEnd(4);

	unorderedSetType set3(100);
	set3.insertEnd(1);
	set3.insertEnd(2);
	set3.insertEnd(3);
	set3.insertEnd(4);
	set3.insertEnd(5);
	set3.insertEnd(9);
	set3.insertEnd(3);
	set3.insertEnd(20);

	unorderedSetType set4 = set2.setUnion(set3);

	set4.print();

	// Intersect Test

	cout << "Starting setIntersect test..." << endl;

	unorderedSetType set5(100);
	set5.insertEnd(1);
	set5.insertEnd(2);
	set5.insertEnd(3);
	set5.insertEnd(4);

	unorderedSetType set6(100);
	set6.insertEnd(1);
	set6.insertEnd(2);
	set6.insertEnd(3);
	set6.insertEnd(4);
	set6.insertEnd(5);
	set6.insertEnd(9);
	set6.insertEnd(20);

	unorderedSetType set7 = set5.setIntersect(set6);

	set7.print();

	system("pause");

	return 0;
}

