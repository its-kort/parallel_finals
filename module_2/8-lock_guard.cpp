#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mtx;

void PrintID(int id) {
    lock_guard<mutex> guard(mtx); // Locks the mutex
    cout << "Thread: " << id << endl;
    // The mutex will be automatically released when the guard goes out of scope (e.g., function exits)
}
int main() {
    thread t1(PrintID, 1);
    thread t2(PrintID, 2);

    t1.join();
    t2.join();

    /* Lock Guard - an elegant way to manage mutexes and ensure that they
                    are properly locked and unlocked, preventing potential deadlocks and race conditions.
    */
   
    /* Output:
        Thread: 1
        Thread: 2
    */
    return 0;
}