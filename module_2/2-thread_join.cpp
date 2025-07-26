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

    t1.join();
    t2.join();
    t3.join();

    // join()   - waits for the thread to finish its execution
    return 0;
}