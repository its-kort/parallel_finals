#include <iostream>
#include <thread>

using namespace std;

void Function1() {
    cout << "[FUNCTION 1] Hello World!" << endl;
}

void Function2() {
    cout << "[FUNCTION 2] Hello!" << endl;
}

class Object{
    public:
    void ObjectFunction() {
        cout << "[OBJECT FUNCTION] Hello..." << endl;
    }
};

int main() {
    thread t1(Function1);
    thread t2(Function2);

    Object obj;
    thread t3(&Object::ObjectFunction, &obj);

    cout << "[MAIN] Hello World!" << endl;

    t1.detach();
    t2.detach();
    t3.detach();

    cout << "[MAIN] Program end." << endl; 
    // detach() - permits the thread to execute independently from the thread handle
    return 0;
}