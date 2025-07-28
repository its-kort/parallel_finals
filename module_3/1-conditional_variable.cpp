#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv;
atomic<bool> ready = false;

void Waiting_Thread() {
    unique_lock<mutex> lock(mtx);

    while (ready == false) {
        cout << "[Waiting Thread] Locking..." << endl;
        cv.wait(lock); // Wait until 'ready' is true
    }
        
    cout << "[Waiting Thread] Signal received!" << endl;
}

void Signaling_Thread() {
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work

    cout << "[Signaling Thread] Sending signal..." << endl;
    ready = true;
    cv.notify_one(); // Notify the waiting thread
}

int main() {
    thread t1(Waiting_Thread);
    thread t2(Signaling_Thread);

    t1.join();
    t2.join();
    return 0;

    /* Summary of what it does:
        step 1: locks Waiting_Thread on unique_lock<mutex> lock(mtx)
        step 2: unlocks Waiting_Thread on cv.wait(lock)
        step 3: sleeps Waiting_Thread after unlocking it (allowing other threads to use any shared data, in this case, the ready atomic variable) 
                and waits for it to be woken up by cv.notify_one()
        step 4: wakes up on cv.notify_one(), then locks Waiting_Thread afterward    
    */

    /* Output:
        [Waiting Thread] Locking...
        [Signaling Thread] Sending signal...
        [Waiting Thread] Signal received!
    */
}