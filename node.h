#pragma once
struct node
{
	node(int value);

	int value;
	node *next, *prev;
};

