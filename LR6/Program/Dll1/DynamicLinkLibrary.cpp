#include "pch.h"
#include "DynamicLinkLibrary.h"
int Func(int a, int b) {
    return a * b;
}


Foo::Foo(int _a) {
    this->a = _a;
}

Foo::~Foo() {}

int Foo::Get() {
    return a;
}

void Foo::Set(int _a) {
    this->a = _a;
}