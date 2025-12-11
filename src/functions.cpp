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

    cout << "---- tests ----" << endl;
    d2.insertFront(30);
    d2.insertFront(20);
    d2.insertFront(10);
    d2.print(); // 10 20 30

    d2.eraseBack();
    d2.insertFront(0);
    d2.print(); // 0 10 20

    d2.eraseFront();
    d2.insertBack(25);
    d2.print(); // 10 20 25

    d2.insertBack(35); // should print "Deque is full"

    d2.eraseFront();
    d2.insertBack(30);
    d2.print(); // 20 25 30

    d3 = d2;
    d3.print(); // 20 25 30
    d3.eraseFront();
    d3.print(); // 25 30
    d2.print(); // 20 25 30

}

void StackUsage(){
    Stack<int> s1(3);
    s1.push(30);
    s1.push(20);
    s1.push(10);

    cout << s1.top() << endl; // 10
    s1.print(); // 30 20 10

    s1.pop();
    s1.push(5);
    s1.print(); // 30 20 5

    s1.push(0); // stack is full
}

void ListUsage(){
    NodeList<int> list;
    list.insertFront(5);
    list.insertFront(10);

    cout << list.size();
}
