#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    const int limitNum = 100;
    int targetNum = std::rand() % limitNum;
    int inputNum = 0;
    int tries = 0;
    std::array<int, limitNum> numArray = { 0 };
    bool repeat = false;
    std::cout << "Guess the number between 0 and 99.\n";

    do {
        repeat = false;
        std::cout << "Enter your number: \n";
        std::cin >> inputNum;

        for (int i = 0; i < tries; i++) {
            if (numArray[i] == inputNum) {
                repeat = true;
                break;
            }
        }
        if (repeat) {
            std::cout << "You tried this number already\n ";

            continue;
        }
        numArray[tries] = inputNum;
        tries++;

        if (inputNum == targetNum) {
            std::cout << "You guessed the number! it was: " << targetNum << std::endl;
            std::cout << "You tried" << tries << " times.\n";
            return 0;
        }
        if (inputNum > targetNum) {
            std::cout << "Target number is smaller\n";
        } else {
            std::cout << "Target number is greater \n";
        }

    } while (inputNum != targetNum);
}
