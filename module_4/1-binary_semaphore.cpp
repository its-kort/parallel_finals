#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std;

binary_semaphore bsp(0);

void doingSomething() {
    bsp.acquire(); // if bsp is 1, set bsp to 0, lock
    cout << "[Thread] Signal received." << endl;

    this_thread::sleep_for(chrono::seconds(3));

    cout << "[Thread] Signal sent." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    bsp.release();  // if bsp is 0, set bsp to 1, unlock
}

int main() {
    thread t1(doingSomething);

    cout << "[Main] Signal sent." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    bsp.release(); // if bsp is 0, set bsp to 1, unlock
    
    this_thread::sleep_for(chrono::seconds(3));

    bsp.acquire(); // if bsp is 1, set bsp to 0, lock
    cout << "[Main] Signal received." << endl;

    t1.join();
    
    return 0;

    /* Binary semaphore - This is also known as mutex lock. It can have only two values – 0 and 1. 
       It is just a counting semaphore initialized to 1. This means only 1 thread can access the semaphore.
       It is used to implement the solution of critical section problems with multiple processes.
    */

    /* Output:
        [Main] Signal sent.
        [Thread] Signal received.
        [Thread] Signal sent.
        [Main] Signal received.
    */
}