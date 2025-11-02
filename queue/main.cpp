#include "queue.h"

int main(int argc, char const *argv[]){
    Queue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);

    q1.print();

    Queue<int> q2(q1);
    return 0;
}