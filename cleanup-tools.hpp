#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <map>

struct DefaultString
{
	DefaultString() : value("others") {}
	DefaultString(std::string s) : value(s) {}
	std::string value;
};

// getting extension while ignoring trailing whitespace
inline std::string extension(std::string s) {
	int len = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (std::isspace(s[i])) continue;
		else if (s[i] == '.') {
			return s.substr(i, len+1);
		}
		len++;
	}
	return "";
}

inline void writeChanges(std::ofstream& txtFile,
		const std::string &targetDir, const std::string &oldName,
		const std::string &newName) {
	txtFile << targetDir << '\n'; 
	txtFile << oldName << '\n';
	txtFile << newName << '\n';
}

inline void updateCount(std::ofstream& txtFile, int count) {
	txtFile << count << '\n';
}

void move(std::string oldName, std::string targetDir, std::ofstream& txtFile);
void autoMove(std::string oldName, std::string targetDir);
std::map<std::string, DefaultString> initMap(std::string inFile);
int cleanFile(std::string filePath, std::string fileName,
		std::map<std::string, DefaultString> groupings);
