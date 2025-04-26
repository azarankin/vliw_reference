#include <iostream>
#include <thread>

void wait_for_keypress() {
    std::cout << "Press any key..." << std::endl;
    getchar(); // מחכה לקלט → stall
    std::cout << "Key pressed!" << std::endl;
}

void compute_heavy() {
    for (int i = 0; i < 1e8; ++i); // פשוט חישוב כלשהו
    std::cout << "Computation done." << std::endl;
}

int main() {
    std::thread t1(wait_for_keypress);
    std::thread t2(compute_heavy);

    t1.join();
    t2.join();
}