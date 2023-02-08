/*
ADVANTAGES/DISADVANTAGES LINKED LIST:
 - Linked lists make dynamic memory allocation much easier than arrays,
    as memory is allocated for data as it is added to the list.
    As a result, the only size limit to a linked list is the computer memory.
    Removing items from a linked list is simple, as the pointers to the next
    node are changed and any memory deallocated.
 - However, traversing linked lists is "expensive" for the time required to
    access the data. Nodes must be traversed in order, and it is not
    possible to "jump" to the middle of the list. Thus for very large datasets,
    it would be difficult to access later data.
    Items can also only be added to the front of the list without incurring a
    similar perforamce penalty by traversing the list, an O(n) operation.

ADVANTAGES/DISADVANTAGES ARRAY:
 - Arrays make it easy to access any data in the array in the same
    amount of time, as all of the data is in order. Increments to the memory
    address allow one to jump to any point in the array. Thus one can add new
    data to any point in the array, an O(1) operation.
 - New memory cannot quickly be allocated to allow new data into the array,
    if the initial array is not large enough to hold the data. A new, larger
    array would have to be created, and the original array memory copied
    to the new array. Simiarly, memory cannot be easily deallocated without
    shifting the data of the entire array to keep the memory continuous.
*/

#include <iostream>

#include "Wrapper.h"

int main() {
    // initialize randomness
    srand((unsigned)time(0));
	Wrapper app( "commands.csv",  "scores.csv" );
	app.run();

    return 0;
}