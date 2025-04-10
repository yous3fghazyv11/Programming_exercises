#include <iostream>
#include <limits>
#include <vector>

#define H_RULE "============================================"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define NORMAL "\033[0m"

void guess(int& lower, int& upper, char answer)
{
    std::cout << lower << " " << upper << std::endl;
    if (upper - lower == 2) {
        std::cout << "Your number is: " << GREEN << (upper + lower) / 2 << NORMAL << std::endl;
        exit(0);
    }
    if (answer == 'y') {
        lower = (lower + upper) / 2;
    }
    if (answer == 'n') {
        upper = (lower + upper) / 2;
    }
    if (upper - lower < 2) {
        std::cerr << RED << "That's not a number" << NORMAL << std::endl;
        exit(0);
    }
    std::cout << lower << " " << upper << std::endl;
}
bool bad_answer(char answer)
{
    if (answer == 'y') return false;
    if (answer == 'n') return false;
    return true;
}
int main()
{
    /********************************/
	std::cout << "this simple number guessing game" << std::endl;
	std::cout << "think of a number between 0 and 100 and i will try to guess it" << std::endl;
	std::cout << "please think of the number in your head then press enter to contine..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << H_RULE << std::endl;
    /********************************/
    int upper = 100;
    int lower = 0;
    char answer = ' ';
    bool guessing = true;
    /********************************/
    while (guessing) {
        std::cout << "is your number " << GREEN << (lower + upper) / 2 << NORMAL << "?[y/n] ";
        std::cin >> answer;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.eof() || answer == 'y') {
            std::cout << "\nexit.." << std::endl;
            break;
        }
        if (bad_answer(answer)) {
            std::cerr << RED << "invalid input provided" << NORMAL << std::endl;
            continue;
        } 
        std::cout << "is your number bigger than " << GREEN << (lower + upper) / 2 << NORMAL << "?[y/n] ";
        std::cin >> answer;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.eof()) {
            std::cout << "\nexit.." << std::endl;
            break;
        }
        if (bad_answer(answer)) {
            std::cerr << RED << "invalid input provided" << NORMAL << std::endl;
            continue;
        } 
        guess(lower, upper, answer);
    /********************************/
    }
	return 0;
}
