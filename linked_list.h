#pragma once

struct node;

struct linked_list
{
	node *head, *tail;
	int length;

	linked_list();
	~linked_list();
	void insert(int value);
	void remove();
	bool contains(int value);
	void print();
};