/* 
 * File:   unorderedSetType.cpp
 *
 */

#include <iostream>
#include "unorderedSetType.h"

using namespace std;

void unorderedSetType::insertAt(int location, int insertItem){

	bool isDuplicate = false;

	for (int i = 0; i < this->listSize(); i++){


		if (this->isItemAtEqual(i, insertItem)){

			isDuplicate = true;

		}

	}

	if (!isDuplicate){

		unorderedArrayListType::insertAt(location, insertItem);
	}
	else{
		cout << "A set cannot contain duplicate items." << endl;
	}

}


void unorderedSetType::insertEnd(int insertItem){

	bool isDuplicate = false;

	for (int i = 0; i < this->listSize(); i++){


		if (this->isItemAtEqual(i, insertItem)){

			isDuplicate = true;

		}

	}

	if (!isDuplicate){

		unorderedArrayListType::insertEnd(insertItem);
	}
	else{
		cout << "A set cannot contain duplicate items." << endl;
	}

}


void unorderedSetType::replaceAt(int location, int repItem){

	bool isDuplicate = false;

	for (int i = 0; i < this->listSize(); i++){


		if (this->isItemAtEqual(i, repItem)){

			isDuplicate = true;

		}

	}

	if (!isDuplicate){

		unorderedArrayListType::replaceAt(location, repItem);
	}
	else{
		cout << "A set cannot contain duplicate items." << endl;
	}

}


unorderedSetType unorderedSetType::setUnion(unorderedSetType set){

	int mergeTemp;

	for (int i = 0; i < set.listSize(); i++){ //for all the items in the set

		this->retrieveAt(i, mergeTemp); //set mergeTemp equal to each

		if (!this->isItemAtEqual(i, mergeTemp)){ //if mergeTemp is NOT equal, append mergeTemp to the end of passed set.

			set.insertEnd(mergeTemp);

		}

	}

	return set;
}


unorderedSetType unorderedSetType::setIntersect(unorderedSetType set){

	int mergeTemp;
	int mergeTemp2;
	unorderedSetType setTemp;


	for (int i = 0; i < set.listSize(); i++){

		set.retrieveAt(i, mergeTemp);

		for (int j = 0; j < this->listSize(); j++){

			this->retrieveAt(j, mergeTemp2);

			if (mergeTemp == mergeTemp2)
				setTemp.insertEnd(mergeTemp);

		}
	}


	return setTemp;
}


unorderedSetType::unorderedSetType(int size){

}


