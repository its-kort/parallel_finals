#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

recursive_mutex rmtx;

void recursiveFunction(int count) {
    if (count < 1) return;
    rmtx.lock();
    cout << "Lock acquired, count: " << count << endl;
    
    // Recursive call
    recursiveFunction(count - 1);
    
    cout << "Unlocking, count: " << count << endl;
    rmtx.unlock();
}
int main() {
    thread t1(recursiveFunction, 3);
    
    t1.join();
    return 0;

    /* Reentrant Lock (aka Recursive Mutex or Recursive Lock) us a particular type of mutex that can be locked multiple times by the same
       process or thread. Internally, the reentrant mutex keeps track of how many times it's been locked by the owning thread, 
       and it has to be unlocked an equal number of times before another thread can lock it.
    */

    /* Output:
        Lock acquired, count: 3
        Lock acquired, count: 2
        Lock acquired, count: 1
        Unlocking, count: 1
        Unlocking, count: 2
        Unlocking, count: 3
    */
}