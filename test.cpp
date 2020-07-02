#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <map>

namespace fs = std::filesystem;

int main() {
	std::map<std::string, bool> dirManager;
	std::cout << dirManager["hi"] << std::endl;
	return 0;
}
