#include "directory.hpp"

namespace fs = std::filesystem;

int main() {
	std::string dirPath = fs::current_path();

  // Directory object
  Directory currDir(dirPath);
  currDir.revert();
  return 0;
}
