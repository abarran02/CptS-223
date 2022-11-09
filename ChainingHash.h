/*
 *  Separate chaining table
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm> // std::find

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    int totalBuckets, elements = 0;
    vector<list<pair<K,V>>> table;

public:
    ChainingHash(int n = 11) {
        totalBuckets = findNextPrime(n);
        table.clear();
        table.resize(totalBuckets);
    }

    ~ChainingHash() {
        this->clear();
    }

    // return number of elements
    int size() {
        return elements;
    }

    V operator[](const K& key) {
        // hash the key
        int keyHash = hash(key);
        // get corresponding bucket
        list<pair<K,V>> bucket = table.at(keyHash);
        // iterate over bucket to find matching key/value pair
        for (pair<K,V> p : bucket) {
            if (p.first == key) {
                // return matching value
                return p.second;
            }
        }

        // otherwise not found, throw out of range
        throw std::range_error("Key not found in hash table");
    }

    // add new key/value pair to list
    bool insert(const std::pair<K, V>& pair) {
        // get hash for key
        int keyHash = hash(pair.first);
        table.at(keyHash).push_back(pair);
        elements++;

        // may need to rehash if too many buckets in use
        if (load_factor() > LOAD_TOLERANCE) {
            rehash();
        }

        return true;
    }

    // returns whether the table is empty
    bool empty() {
        return elements == 0;
    }

    // clear all content
    void clear() {
        // iterate over each bucket and clear list
        for (int i = 0 ; i < totalBuckets; i++) {
            table[i].clear();
        }

        elements = 0;
    }

    // remove key/value pair from list based on key
    void erase(const K& key) {
        // hash the key
        int keyHash = hash(key);
        // check if key exists in the list
        bool removed = false;
        for (pair<K,V> p : table[keyHash]) {
            // key found, then remove pair from list
            if (p.first == key) {
                table[keyHash].remove(p);
                elements--;
                removed = true;
                break;
            }
        }
    }

    int bucket_count() {
        return totalBuckets;
    }

    float load_factor() {
        return (float)elements / totalBuckets;
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return key % totalBuckets;       
    }

    void rehash() {
        // new hash table of double capacity
        ChainingHash<K,V> newTable(totalBuckets * 2);

        // each list in table vector
        for (auto l : table) {
            // each pair in bucket
            for (auto p : l) {
                // insert to new hash table
                newTable.insert(p);
            }
        }

        // set new hash table to old memory
        table = newTable.table;
        totalBuckets = newTable.bucket_count();
    }
};

#endif //__CHAINING_HASH_H
