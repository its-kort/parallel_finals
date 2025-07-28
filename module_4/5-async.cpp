#include <iostream>
#include <future>
#include <chrono>
using namespace std;

int sum(int x, int y) {
    // Count from 0 - 9
    for(int i = 0; i < 10; i++) {
        cout << "[Async]: " << i << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    return x + y; // adds x + y
}

int main() {
    cout << "Getting the sum . . ." << endl;
    future<int> result = async(sum, 2, 1);

    // Count from 0 - 9
    for(int i = 0; i < 10; i++) {
        cout << "[Main]: " << i << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    cout << "RESULT: " << result.get() << endl;

    return 0;

    /* The function template async runs the function f asynchronously (potentially in a separate thread which
    might be a part of a thread pool) and returns a std::future that will eventually hold the result of that function call.
    Which means no synchronization and runs independently.
    
    Syntax:
        To make functions asynchronous: 
            async(function_name, [arguments])
    
        When expencting an output:
            future<data_type> variable 
    */

    /* Output:
        Getting the sum . . .

        [Main]: 0
        [Async]: 0
        [Main]: 1
        [Async]: 1
        [Main]: 2
        [Async]: 2
        [Main]: 3
        [Async]: 3
        [Main]: 4
        [Async]: 4
        [Main]: 5
        [Async]: 5
        [Main]: 6
        [Async]: 6
        [Main]: 7
        [Async]: 7
        [Main]: 8
        [Async]: 8
        [Main]: 9
        [Async]: 9

        RESULT: 3 // async(sum, 2, 1); 2 + 1 = 3
    */
}