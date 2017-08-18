/* 
 * File:   unorderedSetType.h
 *
 */

#ifndef UNORDEREDSETTYPE_H
#define	UNORDEREDSETTYPE_H

#include "unorderedArrayListType.h"

class unorderedSetType : public unorderedArrayListType{
public:

	void insertAt(int location, int insertItem);
	// Function to insert an item at a particular location
	// Postcondition: The item has been added to the list and the length has
	//    been increased by 1.

	void insertEnd(int insertItem);
	// Function to insert an item at the end of the list
	// Postcondition: The item has been added at the end of the list and the 
	//    length has been increased by 1.

	void replaceAt(int location, int repItem);
	// Function to replace an item in the list.
	// Postcondition: repItem overrwrites the item at the specified location
	//     in the list. The length of the list is unchanged.

	unorderedSetType setUnion(unorderedSetType set);
	//returns a new set containing members of caller and parameter

	unorderedSetType setIntersect(unorderedSetType set);
	//returns a new set containing only members parameter and caller share.

	unorderedSetType(int size = 100);
	//constructor



};

#endif	/* UNORDEREDSETTYPE_H */

