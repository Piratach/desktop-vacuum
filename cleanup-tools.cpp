#include "cleanup-tools.hpp"

void move(std::string oldName, std::string targetDir, std::ofstream& txtFile) {
	// targetDir taken from extension
	std::string newName = targetDir + "/" + oldName;
	// check with a tag to avoid computation
	if (std::filesystem::exists(targetDir)) {
		std::rename(oldName.c_str(), newName.c_str());
	} else {
		std::filesystem::create_directory(targetDir);
		std::rename(oldName.c_str(), newName.c_str());
		// set tag to true
	}
	writeChanges(txtFile, targetDir, oldName, newName);
}

void autoMove(std::string oldName, std::string targetDir) {
	// targetDir taken from extension
	std::string newName = targetDir + "/" + oldName;
	// check with a tag to avoid computation
	if (std::filesystem::exists(targetDir)) {
		std::rename(oldName.c_str(), newName.c_str());
	} else {
		std::filesystem::create_directory(targetDir);
		std::rename(oldName.c_str(), newName.c_str());
		// set tag to true
	}
}

std::map<std::string, DefaultString> initMap(std::string mapFile) {
	std::map<std::string, DefaultString> groupings;
	std::ifstream infile;
	infile.open(mapFile);
	std::string key, val;
	while (infile >> key >> val) {
		groupings[key] = DefaultString(val);
	}
	return groupings;
}
