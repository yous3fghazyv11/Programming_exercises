#include <iostream>
#include <ostream>

int main()
{
    std::cout << "Please type a string below: " << std::endl << "> ";
    std::string temp_string;
    std::getline(std::cin, temp_string);
	for (char ch : temp_string) {
        if (ch == ' ') continue;
        std::cout << "letter \033[32m'" << ch << "'\033[0m:\033[32m " << static_cast<int>(ch) << "\033[0m" << std::endl;
    }
}
