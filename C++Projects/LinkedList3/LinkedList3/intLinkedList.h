#include "unorderedLinkedList.h"

class  intLinkedList : public  unorderedLinkedList<int>
{
public:
	void  splitEvensOddsList(intLinkedList  &evensList,
		intLinkedList  &oddsList);
	/* Function to rearrange the nodes of the linked list so
	*     that evensList consists of even integers and oddsList
	*     consists of odd integers.
	* Postcondition: evensList consists of even integers.
	*     oddsList consists of odd integers.
	*     The original list is empty.
	*/
};

void intLinkedList::splitEvensOddsList(intLinkedList  &evensList, intLinkedList  &oddsList){

	linkedListIterator<int> itr = this->begin();

	for (int i = 0; i < this->length(); i++){

		if (itr.current->info % 2 == 0){
			evensList.insertLast(itr.current->info);
			//this->deleteNode(itr.current->info);
		}

		else{
			oddsList.insertLast(itr.current->info);
			//this->deleteNode(itr.current->info);
		}

		++itr;

	}

}