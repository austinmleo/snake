#include "linked_list.h"
#include "node.h"
#include <iostream>

linked_list::linked_list()
{
	head = nullptr;
	tail = nullptr;
	length = 0;
}

//Insert at head
void linked_list::insert(int value) {
	node* temp = new node(value);

	if (head == nullptr) {
		head = temp;
		tail = temp;
	}

	else {
		head->prev = temp;
		temp->next = head;
		head = temp;
	}

	length++;
}

//Remove from tail
void linked_list::remove() {
	if (head != nullptr) {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}

		length--;
	}
}

// Searches structure for value
bool linked_list::contains(int value) {
	node* temp = head;

	while (temp != nullptr) {
		if (temp->value == value) {
			return true;
		}

		temp = temp->next;
	}

	return false;
}

void linked_list::print() {
	node* temp = head;

	while (temp != nullptr) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}

	std::cout << "\n";
}
