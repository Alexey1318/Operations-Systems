#pragma once
#include <iostream>
struct Node {
	 int field;
	Node* nextItem;
};
class Stack
{
private:
	Node* head;
	int maxSize;
	int size;

public:
	/*Создание головы списка*/
	Stack(int n) {
		head = nullptr;
		maxSize = n*sizeof(int);
		size = 0;
	}
	/*Добавление элемента списка*/
	bool push(int value) {
		if (size < maxSize) {
			Node* n = new Node;
			n->field = value;
			n->nextItem = head;
			head = n;
			size += sizeof(value);
			return true;
		}
		else {
			return false;
		}
	}
	/*Извлечение элемента списка*/
	int pop() {
		int n = head->field;
		Node* c = head->nextItem;
		delete head;
		head = c;
		size -= sizeof(int);
		return n;
	}
	bool canPop() {
		if (head == NULL) {
			return false;
		}
		else {
			return true;
		}
	}
	/*Удаление списка*/
	~Stack() {
		while (head != nullptr) {
			Node* n = head->nextItem;
			delete head;
			head = n;
		}
	}
};