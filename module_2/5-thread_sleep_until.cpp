#include <iostream>
#include <thread>

using namespace std;

void Function1() {
    for(int i = 1; i <= 5; i++) {
        cout << "[FUNCTION 1] Hello: " << i << endl;
        this_thread::sleep_until(chrono::system_clock::now() + 2s );
    }
}

void Function2() {
    for(int i = 1; i <= 5; i++) {
        cout << "[FUNCTION 2] Hello: " << i << endl;
        this_thread::sleep_until(chrono::system_clock::now() + 2s );
    }
}

int main() {
    thread t1(Function1);
    thread t2(Function2);

    cout << "[MAIN] Hello World!" << endl;

    t1.join();
    t2.join();

    /* sleep_until - puts thread to "sleep" (waits) a certain amount of time before resuming
                   - sleeps until a specific point in time is reached. 
                   - in this example, it pauses the thread until 2 seconds from now.
                   - sleep thread, then run
    */
    return 0;
}