#include <iostream>
#include "queue.h"
#include "stack.h"

using namespace std;

int main()
{
    Stack q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Pop(nullptr);
    cout << q;

    return 0;
}
