#include <iostream>
#include <thread>

using namespace std;

void Function1() {
    for(int i = 1; i <= 5; i++) {
        cout << "[FUNCTION 1] Hello: " << i << endl;
        this_thread::sleep_for(2s);
    }
}

void Function2() {
    for(int i = 1; i <= 5; i++) {
        cout << "[FUNCTION 2] Hello: " << i << endl;
        this_thread::sleep_for(1s);
    }
}

int main() {
    thread t1(Function1);
    thread t2(Function2);

    cout << "[MAIN] Hello World!" << endl;

    t1.join();
    t2.join();

    /* sleep_for - puts thread to "sleep" (waits) a certain amount of time before resuming
                 - sleeps for a specific amount of time from now.
                 - in this example, pauses the thread for 2 seconds from now.
                 - run thread, then sleep
    */
    return 0;
}