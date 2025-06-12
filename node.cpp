#include "node.h"

node::node(int value)
{
	this->value = value;
	this->next = nullptr;
	this->prev = nullptr;
}