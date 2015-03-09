/* 
 * File:   unorderedArrayListType.h
 * Author: Owner
 *
 * Created on July 13, 2014, 12:21 PM
 */

#ifndef UNORDEREDARRAYLISTTYPE_H
#define	UNORDEREDARRAYLISTTYPE_H

#include "arrayListType/arrayListType.h"

class unorderedArrayListType : public arrayListType {
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
    
    int seqSearch(int searchItem) const;
    // Function to search the list for searchItem. Note that this is an 
    // abstract function.
    //Postcondition: If the item is found, returns the location in the array 
    // where the item is found; otherwise, returns -1.
    
    void remove(int removeItem);
    // Function to remove an item from the list
    // Postcondition: If the item is found in the list, it is removed and the
    //   length of the list is decreased by 1; if the item is not in the list
    //   an appropriate message is displayed.
    
    void removeAll(int removeItem);
    // Function to remove all occurrences of an item from the list
    // Postcondition: If the item is found in the the list, all occurrences are
    //    removed and the length of the list is decreased accordingly. If the
    //    item is not in the list an appropriate message is displayed.
    
    unorderedArrayListType(int size = 100);
    //Constructor.
};

#endif	/* UNORDEREDARRAYLISTTYPE_H */

