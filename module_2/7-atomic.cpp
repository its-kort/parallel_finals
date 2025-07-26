#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

atomic<int> counter = 0;
// atomic - ensures safe access to shared data in multi-threaded programs without using locks
//        - however, race condition is still possible unlike mutex

void increment() {
    for (int i = 1; i <= 10; i++) {
        ++counter;
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);
    
    t1.join();
    t2.join();

    cout << "[MAIN] Total Counter: " << counter << endl;
    return 0;
}