#include <iostream>
#include "MyVector.h"
#include "MyList.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "MyDeque.h"
#include <iostream>
#include "vld.h"
using namespace std;

int main()
{
    MyDeque<int, 15> deque;
    for (int i = 0; i < 24; ++i) {
        deque.push_back(i);
        deque.push_front(i);
    }
    MyDeque<int, 15> deque2(deque);
    deque2[0] = 5000;
    for (int i = 0; i < deque2.size(); ++i) {
        cout << deque2[i] << endl;
    }

    return 0;

}

