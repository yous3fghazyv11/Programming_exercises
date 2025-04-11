#include <cfloat>
#include <climits>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

#define H_RULE "============================================"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define NORMAL "\033[0m"

bool invalid_op(char op)
{
    if (op == '+' || op == '-' || op == '*' || op == '/') return false;
    return true;
}

int main()
{
	std::cout << "This is a simple calculator, please type two numbers and an operator below: " << std::endl;
	int num1 = 0;
	int num2 = 0;
	char op = ' ';
	while (std::cout << "> ") {
		std::cin >> num1 >> op >> num2;
		if (std::cin.fail()) {
			std::cerr << "wrrong input\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
		}
        if (invalid_op(op)) {
			std::cerr << "wrrong input\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (op) {
        case '+':
            std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
            break;
        default:
            std::cout << num1 << " / " << num2 << " = " << num1 / num2 << std::endl;
            break;
        }
	}
	return 0;
}
