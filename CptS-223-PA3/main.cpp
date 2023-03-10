<<<<<<< HEAD
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
=======
#include <map>
#include <string>
#include <chrono>
#include <cassert>
#include "ChainingHash.h"
#include "ProbingHash.h"
#include <iostream>
#include <fstream>

void testHash(Hash<int, int> *hash, std::ofstream &myfile)
{

    myfile << "current size: " << hash->size() << " bucket count: " << hash->bucket_count()
           << " load factor: " << hash->load_factor() << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        assert(hash->insert(std::make_pair(i, i)));
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[97] == 97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    hash->erase(97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[10000] == 10000);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    myfile << "current size: " << hash->size() << " bucket count: " << hash->bucket_count()
           << " load factor: " << hash->load_factor() << std::endl;
    hash->clear();
}

int main(int argc, char *argv[])
{
    std::ofstream myfile;
    myfile.open("output.txt");
    ChainingHash<int, int> cHash(101);
    ProbingHash<int, int> pHash(101);
    testHash(&cHash, myfile);
    testHash(&pHash, myfile);
    myfile.close();
>>>>>>> CptS-223-PA3/master
}