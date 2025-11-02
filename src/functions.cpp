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

    cout << "---- circle queue ----" << endl;
    Queue<int> q4(3);
    q4.push(1);
    q4.push(2);
    q4.push(3);

    q4.print();
    q4.pop();
    q4.push(4);
    q4.pop();
    q4.push(5);
    q4.pop();
    q4.push(6);
    q4.print();
}

void DequeUsage(){
    Deque<int> d1(3);
    Deque<int> d2(d1);
    Deque<int> d3;
    d3 = d1;

    cout << "---- circle deque ----" << endl;
    d1.insertBack(1);
    d1.insertBack(2);
    d1.insertBack(3);
    d1.print();
    d1.eraseFront();
    d1.insertBack(4);
    d1.eraseFront();
    d1.insertBack(5);
    d1.eraseFront();
    d1.insertBack(6);
    d1.print();
}
