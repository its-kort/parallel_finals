#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mtx;

void attemptLock(int threadID) {
    if (mtx.try_lock()) {
        // This part of code will only run if mtx is unlocked
        cout << "Thread " << threadID << " acquired the lock." << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
        mtx.unlock();
    } else {
        cout << "Thread " << threadID << " could not acquire the lock." << endl;
        // This part of code will only run if mtx is already locked, which avoids locking the thread twice and 
        // does not wait for the thread to be unlocked
    }
}

int main() {
    thread t1(attemptLock, 1);
    thread t2(attemptLock, 2);
    
    t1.join();
    t2.join();
    
    /* Try lock (or try enter) is a non-blocking version of the lock or acquire method. 
       It returns immediately and one of two things will happen:
          – If the mutex you're trying to lock is available, it will get locked, and the method with return TRUE.
          – Otherwise, if the mutex is already possessed by another thread, the try lock method will immediately return FALSE.
    */

    /* Output:
        Thread 1 acquired the lock.
        Thread 2 could not acquire the lock.
    */

    return 0;
}