#include <iostream>
#include <mutex> // Required directive for mutex
#include <thread>

using namespace std;

mutex mtx;
void PrintID(int id) {
    mtx.lock(); // Blocks the calling thread until it successfully locks the mutex.
    cout << "Thread: " << id << endl;
    mtx.unlock(); //  Releases the mutex, allowing other threads to acquire it.
}

int main() {
    thread t1(PrintID, 1);
    thread t2(PrintID, 2);
    thread t3(PrintID, 3);

    t1.join();
    t2.join();
    t3.join();   

    /* Output:
        Thread: 1
        Thread: 2
        Thread: 3
    */  
    return 0;
}