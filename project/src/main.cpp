#include <cmath>
#include <cstdint>
#include <gsl/gsl>
#include <iostream>

int main(std::size_t argc, gsl::zstring* argv) {
	gsl::span<gsl::zstring> arguments(argv, argc);
	std::sort(arguments.begin(), arguments.end());

	gsl::not_null<gsl::zstring*> arguments_pointer_validated = argv;

	std::cout << "Hello World" << std::endl;
	std::uint32_t count = 0;
	std::size_t size = 12;
	std::float_t f = 0.0f;
	return 0;
}