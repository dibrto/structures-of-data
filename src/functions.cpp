#include "functions.h"

void QueueUsage(){
    Queue<int> q1(100);
    
    q1.push(10);
    q1.push(20);
    q1.push(30);
    
    cout << q1.front() << endl;
    q1.pop();
    cout << q1.front() << endl;

    Queue<int> q2(q1);
    cout << q2.getSize() << endl;
    q2.print();

    Queue<int> q3;
    q1 = q1;
    q3 = q1;
    q1.pop();

    cout << q3.getSize() << endl;
    q3.print();
}

void DequeUsage(){
    Deque<int> d1;
    Deque<int> d2(d1);
    Deque<int> d3;
    d3 = d1;

    cout << "Deque one is: " << d1.empty() << endl;
    cout << "Deque one size is: " << d1.getSize() << endl;
}
