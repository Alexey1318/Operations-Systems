#include <iostream>
#include <windows.h>
#include <thread>
#include <process.h>
#include <conio.h>
#include "Stack.h"

using namespace std;

CRITICAL_SECTION critsect;

HANDLE Push, Pop;

bool IfEmpty(Stack* stack) {
	if (stack->canPop())
		return true;
	else
		return false;
}

void PopOutStack(Stack* stack) {
	cout << "PopOutStack" << endl;
	if (IfEmpty(stack))
		cout << stack->pop() << endl;
}

void PushInStack(Stack* stack, int val) {
	cout << "PushInStack" << endl;
	if (stack->push(val)) {}
	else {
		cout << "Stack is full" << endl;
	}
}

void PushFunction(void* ptr) {	
	Stack* st = (Stack*)ptr;
	int val = rand() % 100;
	EnterCriticalSection(&critsect);
	/*Вывод внутри критической секции нужен для отладки*/
	cout << "PushFunction(thread)" << endl;
	PushInStack(st, val);
	LeaveCriticalSection(&critsect);
	Sleep(1000);
	_endthread();
}

void PopFunction(void*ptr) {	
	Stack* st = (Stack*)ptr;
	EnterCriticalSection(&critsect);
	cout << "PopFunction(thread)" << endl;
	PopOutStack(st);
	LeaveCriticalSection(&critsect);
	Sleep(500);
	_endthread();
}

int main() {
	srand(time(NULL));
	int local_size = 6;
	Stack* stack = new Stack(local_size);
	InitializeCriticalSection(&critsect);

	for (int i = 0; i < 7; i++) {
		Push = (HANDLE)_beginthread(PushFunction, 1024, stack);
		Pop = (HANDLE)_beginthread(PopFunction, 1024, stack);
	}
	Sleep(5000);
	DeleteCriticalSection(&critsect);
	return 0;
}