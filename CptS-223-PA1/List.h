#pragma once

#include <iostream>

// linked List node template
template <typename T>
struct node {
    T data;
    node *next;

	// constructor to initialize next to nullptr
	// data should be assigned later by user
	node() { next = nullptr; }

	// destructor, important for freeing all List memory
	~node() { delete next; }
};

template <class T>
class List {
public:
	List();
	~List();

	bool isEmpty();
	void clearList();
	node<T>* getHead();
	void setHead(node<T>* head);
	int getLength();
	node<T>* getNodeAtPosition(int n);

	bool insertAtFront(T& data);
	bool removeNode(node<T>* match);

private:
	node<T>* pHead;
};

/*************************************************************
 * Function: List ()                                         *
 * Description: default constructor for List class           *
 *************************************************************/
template <class T>
List<T>::List() {
	pHead = nullptr;
}

/*************************************************************
 * Function: ~List ()                                        *
 * Description: destructor for List class                    *
 *************************************************************/
template <class T>
List<T>::~List() {
	delete pHead;
}

/*************************************************************
 * Function: isEmpty ()                                      *
 * Description: determines whether list is empty             *
 *************************************************************/
template <class T>
bool List<T>::isEmpty() {
	return (pHead == nullptr);
}

/*************************************************************
 * Function: clearList ()                                    *
 * Description: deletes all nodes in list and resets pHead   *
 *		to NULL                                              *
 *************************************************************/
template <class T>
void List<T>::clearList() {
	if (!isEmpty()) {
		delete pHead;
		pHead = nullptr;
	}
}

/*************************************************************
 * Function: getHead ()                                      *
 * Description: get head pointer of list                     *
 *************************************************************/
template <class T>
node<T>* List<T>::getHead() {
	return pHead;
}

/*************************************************************
 * Function: setHead ()                                      *
 * Description: sets the head pointer of list to new node    *
 *        within the range provided                          *
 *************************************************************/
template <class T>
void List<T>::setHead(node<T>* head) {
	pHead = head;
}

/*************************************************************
 * Function: getLength ()                                    *
 * Description: calculates the length of the list            *
 *************************************************************/
template <class T>
int List<T>::getLength() {
	int count = 0;
	node<T>* pCurrent = this->getHead();

	// iterate over array and count nodes
	while (pCurrent != nullptr) {
		pCurrent = pCurrent->next;
		count++;
	}

	return count;
}

/*************************************************************
 * Function: getNodeAtPosition ()                            *
 * Description: returns pointer to the node at specified     *
 *        position n                                         *
 * Preconditions: n <= (list length - 1)                     *
 *************************************************************/
template <class T>
node<T>* List<T>::getNodeAtPosition(int n) {
	if (n <= this->getLength() - 1) {
		node<T>* pCurrent = pHead;
		for (int i = 0; i < n; i++) {
			pCurrent = pCurrent->next;
		}

		return pCurrent;
	}
	else {
		return nullptr;
	}
}

/*************************************************************
 * Function: insertAtFront ()                                *
 * Description: inserts new data at front of List            *
 * Postconditions: returns true if allocated successfully,   *
 *		false otherwise                                      *
 *************************************************************/
template <class T>
bool List<T>::insertAtFront(T& data) {
	node<T>* pNew = new node<T>;
	pNew->data = data;

	// check memory successfully allocated
	if (pNew != 0) {
		if (isEmpty()) {
			pHead = pNew;
		}
		else {
			pNew->next = pHead;
			pHead = pNew;
		}

		return true;
	}

	return false;
}

/*************************************************************
 * Function: removeNode ()                                   *
 * Description: removes matching node from the list,         *
 * 			returns removal success                          *
 * Preconditions: node<T>* match is in list                  *
 *************************************************************/
template <class T>
bool List<T>::removeNode(node<T>* match) {
	node<T>* pCurrent = this->getHead();
	// check whether head matches
	if (pCurrent->data == match->data) {
		// list remains intact by keeping a head node
		this->setHead(pCurrent->next);
		// free memory
		delete pCurrent;
		return true;
	}
	else {
		node<T>* pPrev = pCurrent;
		pCurrent = pCurrent->next;

		// iterate over list to search for matching node
		while (pCurrent != nullptr) {
			if (pCurrent->data == match->data) {
				// reconnect list to avoid match
				pPrev->next = pCurrent->next;
				// free memory
				delete pCurrent;
				return true;
			}
			pPrev = pCurrent;
			pCurrent = pCurrent->next;
		}
	}

	// node was not removed
	return false;
}