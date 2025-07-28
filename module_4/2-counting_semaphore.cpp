#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std;

// Counting semaphore initialized to 2: only 2 threads can enter at the same time
counting_semaphore<3> csp(2);

void accessResource(int id) {
    cout << "[Thread " << id << "] Waiting to access resource..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work

    csp.acquire(); // Decrease the count. If 0, wait until another thread releases.

    cout << "[Thread " << id << "] Access granted!" << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work

    cout << "[Thread " << id << "] Releasing resource." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work
    csp.release(); // Increase the count back
}

int main() {
    thread t1(accessResource, 1);
    thread t2(accessResource, 2);
    thread t3(accessResource, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;

    /* Counting Semaphore - Its value can range over an unrestricted domain. It is
    used to control access to a resource that has multiple instances. Meaning,
    multiple threads can access the semaphore unlike binary semaphore.

    Syntax: counting_semaphore<x> variable_name(y)
    x - max number of threads that can access the semaphore
    y - the number of threads that are allowed to access the semaphore
    */

    /* Output:
        [Thread 1] Waiting to access resource...
        [Thread 1] Access granted!

        [Thread 2] Waiting to access resource...
        [Thread 2] Access granted!

        [Thread 3] Waiting to access resource...
        [Thread 1] Releasing resource.
        [Thread 3] Access granted!

        [Thread 2] Releasing resource.
        [Thread 3] Releasing resource.
    */
}
