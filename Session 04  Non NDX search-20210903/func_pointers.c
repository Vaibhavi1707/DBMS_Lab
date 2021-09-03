#include <stdio.h>

void f1(int x, int y) 
{
    printf("I am f1, %d\n", x * y);
}

void f2(int x, int y) 
{
    printf("I am f2, %d\n", x + y);
}
// Only functions satisfying this protoytpe 
// Can be passed
void f(void (*func)(int, int), int x, int y) 
{
    func(x, y);
}

int main() 
{
    f(f1, 5, 10);
    f(f2, 5, 10);
    return 1;
}