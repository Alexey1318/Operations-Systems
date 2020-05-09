const auto fork = 1;
#include <iostream>
#include <Windows.h>
#include <list>
using namespace std;

//const int length = 5;		
list<int>forks;		// для учета вилок

HANDLE philosopher;

DWORD WINAPI Ph(PVOID pParam) {
	int ind = (int)pParam;

	// ждем, когда освободятся вилки
	WaitForSingleObject(philosopher, INFINITE);

	// забрали 2 вилки со стола
	cout << ind << "-st philosopher take left fork" << endl;
	forks.pop_back();
	cout << ind << "-st philosopher take right fork" << endl;
	forks.pop_back();
	Sleep(200);

	// задержка - ждем пока философ доест свою порцию
	cout << ind << "-st philosopher eats" << endl;

	// время, за которое свою порцию съедает один философ
	// учитывай при показе!!!
	Sleep(500);
	//Sleep(500 * ind);

	// кладем 2 вилки на стол
	cout << ind << "-st philosopher put left fork" << endl;
	forks.push_back(fork);
	cout << ind << "-st philosopher put right fork" << endl;
	forks.push_back(fork);

	// разрешаем другим брать вилки
	ReleaseSemaphore(philosopher, 1, NULL);

	// закрываем поток
	ExitThread(NULL);
}

int main() {
	int length = 0;

	// ввод к-ва философов; для отладки
	while (length != -1) {
		cin >> length;
		philosopher = CreateSemaphore(NULL, length / 2, length / 2, NULL);

		// выкладываем вилки на стол
		for (int i = 0; i < length; i++) {
			forks.push_back(fork);
		}

		// запускаем философов в столовую
		for (int i = 0; i < length; i++) {
			CreateThread(NULL, 0, Ph, (void*)i, 0, NULL);
		}

		// задержка
		getchar();
	}
	return 0;
}