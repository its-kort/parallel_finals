#include <iostream>
#include <thread> // Required header directive for threads

using namespace std;

int main() {
    cout << "[MAIN] Hello World!" << endl;
    cout << "[MAIN] Thread ID: " << this_thread::get_id() << endl; // Outputs the thread ID being used

    return 0;
}