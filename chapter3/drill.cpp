/*
 * one very important trick in this program is that we need to differentiate
 * between the input the user provided and the input converted to the user preferred unit
 * for that we use two kind of variables, output_values and input_values
 * for example if input value is 10m, and the preferred unit is cm
 * the output value would be 100. Some functions like get_input and print input will only deal with input values.
 * while others like compare will deal with output values
 */

#include <math.h>

#include <ios>
#include <iostream>
#include <limits>
#include <vector>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define NORMAL "\033[0m"

/*
 * returns the sum of a list
 */
double sum(std::vector<double> list)
{
	double result = 0;
	for (double item : list) {
		result += item;
	}
	return result;
}

/*
 * converts value from a unit to another
 */
double convert(std::string to_unit, std::string from_unit, double value)
{
	double value_in_meters = 0;
	constexpr double CM_M = 0.01;
	constexpr double IN_M = 0.0254;
	constexpr double FT_M = 0.3048;

	if (from_unit == "m")
		value_in_meters = value;
	else if (from_unit == "cm")
		value_in_meters = value * CM_M;
	else if (from_unit == "ft")
		value_in_meters = value * FT_M;
	else if (from_unit == "in")
		value_in_meters = value * IN_M;

	if (to_unit == "m")
		return value_in_meters;
	else if (to_unit == "cm")
		return value_in_meters / CM_M;
	else if (to_unit == "ft")
		return value_in_meters / FT_M;
	else if (to_unit == "in")
		return value_in_meters / IN_M;
	else
		return 0;
}
/*
 * in case of bad input, this function clears the input stream
 */
void clear_input_stream()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
/*
 * checks if a unit is valid
 */
bool legal_unit(std::string unit)
{
	std::vector<std::string> legal_units = {"m", "ft", "in", "cm"};
	for (std::string x : legal_units) {
		if (unit == x) return true;
	}
	return false;
}
/*
 * prints help message
 */
void help()
{
	std::cout << GREEN << "===================================" << NORMAL << std::endl;
	std::cout << "This is a unit convertor program, provide the prompet with a number followed by a unit." << std::endl;
	std::cout << "Choose a unit to convert all input to and then print out the summation of all of them." << std::endl;
	std::cout << "Examples: 12in, 2cm, 14m, 15ft" << std::endl;
	std::cout << "Legal units: m, cm, ft, in " << std::endl;
	;
	std::cout << GREEN << "===================================" << NORMAL;
	std::cout << std::endl;
}
/*
 * prints input in original units and values
 */
void print_inputs(std::vector<double> input_values, std::vector<std::string> input_units)
{
	std::cout << std::endl
		  << std::endl
		  << "values entered: " << GREEN << '[';
	for (std::size_t i = 0; i < input_values.size(); i++) {
		std::cout << input_values[i] << input_units[i];
		if (i != input_units.size() - 1) std::cout << ", ";
	}
	std::cout << ']' << NORMAL << std::endl;
}
/*
 * checks if an item is repeated in a list
 */
bool repeated(std::vector<double> list, double item)
{
	int count = 0;
	for (double x : list) {
		if (x == item) count++;
	}
	if (count >= 2) return true;
	return false;
}
/*
 * compares a value to a list of values to check if it's the smallest or the biggest
 */
void compare(std::vector<double> list_of_values, double value)
{
	double biggest = std::numeric_limits<double>::min();
	double smallest = std::numeric_limits<double>::max();
	for (double value : list_of_values) {
		if (value > biggest) biggest = value;
		if (value < smallest) smallest = value;
	}
	if (repeated(list_of_values, value)) return;
	if (value == biggest)
		std::cout << "This is the biggest value so far!" << std::endl;
	else if (value == smallest)
		std::cout << "This is the smallest value so far!" << std::endl;
}
/*
 * gets input, both unit and value
 * this function only deals with input units
 */
void get_input(std::vector<double>& input_values, double& current_value, bool& getting_input,
	       std::vector<std::string>& input_units, std::string& current_unit)
{
	std::cout << GREEN << "===================================" << NORMAL;
	while (std::cout << "\n> ") {
		std::cin >> current_value;
		if (std::cin.eof()) {
			std::cout << "\nExiting..." << std::endl;
			getting_input = false;
			break;
		}
		if (std::cin.fail()) {
			std::cin.clear();
			char ch;
			std::cin >> ch;
			if (ch == 'h' || ch == 'H') {
				help();
				clear_input_stream();
				continue;
			} else {
				std::cerr << RED << "input operation failed, please provide a valid input!" << NORMAL << std::endl;
				clear_input_stream();
				continue;
			}
		}
		std::cin >> current_unit;
		if (!legal_unit(current_unit) || std::cin.peek() != '\n') {
			std::cerr << RED << "input operation failed, please provide a valid input!" << NORMAL << std::endl;
			clear_input_stream();
			continue;
		}
		input_values.push_back(current_value);
		input_units.push_back(current_unit);
		return;
	}
}
/*
 * gets the user preferred unit
 */
std::string get_user_unit()
{
	std::cout << GREEN << "===================================" << NORMAL;
	std::string user_unit;
	while (std::cout << "\n> ") {
		std::cin >> user_unit;
		if (std::cin.eof()) {
			std::cout << "\nExiting..." << std::endl;
			exit(0);
		}
		if (std::cin.fail() || !legal_unit(user_unit) || std::cin.peek() != '\n') {
			if (user_unit == "h") {
				help();
				continue;
			}
			std::cerr << RED << "input operation failed, please provide a valid input!" << NORMAL << std::endl;
			clear_input_stream();
			continue;
		}
		return user_unit;
	}
	return " ";
}
int main()
{
	double current_value = 0;	       // for input value
	std::vector<double> output_values;     // for values converted to user preferred unit
	std::vector<double> input_values;      // for values kept in original units;
	std::string current_unit;	       // for current input unit
	std::vector<std::string> input_units;  // a vector of all original units

	std::cout << std::endl << "Please type your preferred unit below (ctrl + D to exit, 'h' for help)" << std::endl;
	std::cout << "Options: m, cm, ft, in" << std::endl;
	std::cout << "All input will be converted to the preferred unit after the program ends:" << std::endl;
	std::string user_unit = get_user_unit();
	std::cout << "All input will be converted to " << user_unit << std::endl;

	std::cout << std::endl << "Please type a number below" << std::endl;
	bool getting_input = true;
	while (getting_input) {	 // main loop
		get_input(input_values, current_value, getting_input, input_units, current_unit);
		if (getting_input) {
			output_values.push_back(convert(user_unit, current_unit, current_value));
			if (input_values.size() > 1)
				compare(output_values, convert(user_unit, current_unit, current_value));
			else
				std::cout << "this is the biggest and smallest so far" << std::endl;
		}
	}
	print_inputs(input_values, input_units);

	std::cout << "values in " << user_unit << ": " << GREEN << '[';
	for (std::size_t i = 0; i < output_values.size(); i++) {
		std::cout << output_values[i] << user_unit;
		if (i != output_values.size() - 1) std::cout << ", ";
	}
	std::cout << ']' << NORMAL << std::endl;
	std::cout << "Sum of entered values in " << user_unit << " is: " << sum(output_values) << std::endl;
}
