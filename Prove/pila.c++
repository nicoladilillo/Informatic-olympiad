#include <stack>
#include <iostream>

int main() {
    std::stack <int> pila;
    int n=6;

    pila.push(n);
    std::cout << pila.top() ;

    return 0;
}
