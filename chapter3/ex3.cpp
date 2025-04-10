#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<double> temps;
	for (double temp; std::cin >> temp;)
		temps.push_back(temp);
	double sum = 0;
	for (double x : temps)
		sum += x;
    std::cout << "Average temperature: " << sum / temps.size() << '\n';
    std::ranges::sort(temps);
    if (temps.size() % 2 == 1)
        std::cout << "Median temperature: " << temps[temps.size() / 2] << '\n';
    else {
        double first_mid_item = temps[(temps.size() / 2) - 1];
        double second_mid_item = temps[temps.size() / 2];
        double median = (first_mid_item + second_mid_item) / 2;
        std::cout << "Median temperature: " << median << '\n';
    }
}
