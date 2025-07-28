#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;

shared_mutex mtx;
int shared_data = 0;

void reader(int id) {
    shared_lock lock(mtx);
    cout << "[Reader " << id << "] reads shared_data: " << shared_data << endl;
}

void writer(int id) {
    unique_lock lock(mtx);
    ++shared_data;
    cout << "[Writer " << id << "] updates shared_data to: " << shared_data << endl;
}

int main() {
    // Create 5 reader threads
    thread readerT[5];
    for (int i = 0; i < 5; ++i) {
        readerT[i] = thread(reader, i + 1);
    }
    
    // Create 2 writer threads
    thread writerT[2];
    for (int i = 0; i < 2; ++i) {
        writerT[i] = thread(writer, i + 1);
    }

    // Join all threads
    for (int i = 0; i < 5; i++) {
        readerT[i].join();
    }
    
    for (int i = 0; i < 2; i++) {
        writerT[i].join();
    }

    return 0;

    /* A reader-writer lock (or shared mutex) can be locked in one of two ways. 
        • It can be locked in a shared read mode that allows multiple threads that only need to read
          simultaneously to lock it, or it can be locked in an exclusive write mode that limits access to
          only one thread at a time, allowing that thread to safely write to the shared resource.
        
        • Since only one thread can have the write lock at a time, all other threads wanting to read or
          write will have to wait until the lock becomes available again.
    */

    /* shared_mutex is a synchronization primitive that allows multiple threads to read from a
       shared resource simultaneously while ensuring exclusive access for writing. This can be
       particularly useful in scenarios where read operations are more frequent than write operations
    */

    /* Possible Output1 :
        [Writer 1] updates shared_data to: 1
        [Writer 2] updates shared_data to: 2
        [Reader 1] reads shared_data: 2
        [Reader 2] reads shared_data: 2
        [Reader 3] reads shared_data: 2
        [Reader 4] reads shared_data: 2
        [Reader 5] reads shared_data: 2
    */

    /* Possible Output 2: 
        [Writer 1] updates shared_data to: 1
        [Reader 1] reads shared_data: 1
        [Reader 2] reads shared_data: 1
        [Writer 2] updates shared_data to: 2
        [Reader 3] reads shared_data: 2
        [Reader 4] reads shared_data: 2
        [Reader 5] reads shared_data: 2
    */
}