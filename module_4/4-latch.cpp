#include <latch>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

latch start_game(3);
latch end_game(3);

void character_select(string username, string character_name, int time_taken) {
    cout << "[" << username << "]" << " Selected: " << character_name << endl;
    cout << "Loading . . ." << endl;

    this_thread::sleep_for(chrono::seconds(time_taken));
    cout << "[" << username << "]" << " Connected. " << endl;

    start_game.arrive_and_wait(); // waits until all threads have arrived at this point of the code before proceeding, start_game is used and cant be used again
    cout << "[" << username << "]" << " In Game. " << endl;


    srand(time(NULL));
    int alive_time = rand() % 5 + time_taken;
    cout << "[" << username << "]" << " Played for. " << alive_time << " seconds." << endl;

    this_thread::sleep_for(chrono::seconds(alive_time));
    cout << "[" << username << "]" << " Eliminated." << endl;
    end_game.arrive_and_wait(); // waits until all threads have arrived at this point of the code before exiting the function, end_game is used and cant be used again
}

int main() {
    cout << "Character Selection Phase. . ." << endl;

    thread player1(character_select, "Aquaman", "Jeff the Land Shark", 5);
    thread player2(character_select, "Batman", "The Punisher", 1);
    thread player3(character_select, "Superman", "Groot", 4);

    this_thread::sleep_for(chrono::seconds(20));

    cout << "Match over." << endl;

    player1.join();
    player2.join();
    player3.join();

    return 0;

    /* The latch class is a downward counter type which can be used to synchronize threads.
       The value of the counter is initialized on creation. Threads may block on the latch until the counter is decremented to zero. 
       There is no possibility to increase or reset the counter, which makes the latch a single-use barrier.

       Syntax: latch variable(number_of_threads)
    */

    /* Output:
        Character Selection Phase. . .

        [Aquaman] Selected: Jeff the Land Shark
        Loading . . .

        [Batman] Selected: The Punisher
        Loading . . .

        [Superman] Selected: Groot
        Loading . . .

        [Batman] Connected.
        [Aquaman] Connected.
        [Superman] Connected.

        [Aquaman] In Game.
        [Batman] In Game.
        [Superman] In Game.

        [Batman] Played for. 3 seconds.
        [Aquaman] Played for. 7 seconds.
        [Superman] Played for. 8 seconds.

        [Batman] Eliminated.
        [Aquaman] Eliminated.
        [Superman] Eliminated.

        Match over.
    */
}