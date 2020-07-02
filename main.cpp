#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "cleanup-tools.hpp"
namespace fs = std::filesystem;

int main() {
	std::array<char, 128> buffer;
	std::string result;
	std::string dirPath = fs::current_path();
	std::string cmd = "fswatch -0 " + dirPath;
	std::cout << cmd << std::endl;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(),
				"r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (true) {
		// if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			// // result += buffer.data();
			// std::cout << buffer.data() << std::endl;
		// }
		std::cout << pipe.get() << std::endl;
	}
	return 0;
}
