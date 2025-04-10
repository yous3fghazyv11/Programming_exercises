#include <iostream>
#include <vector>

int main()
{
    std::vector<char> chars;
    std::cout << "Please type a string below:" << std::endl << "> ";
	for (char temp; std::cin >> temp;)
        chars.push_back(temp);
    int temp = 0;
    for (char ch : chars) {
        temp = ch;
        std::cout << "First letter: " << ch << " = " << temp << std::endl;
    }
    return 0;
}
