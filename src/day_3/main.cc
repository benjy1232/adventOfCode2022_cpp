#include <array>
#include <cstdio>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "include/read_file.h"

inline bool stringContains(const std::string& s, char c) {
	for (auto sc : s)
		if (sc == c)
			return true;
	return false;
}

inline std::vector<char> intersectionChar(const std::string& s1, const std::string& s2) {
	std::vector<char> vc;
	for (auto c : s1)
		if (stringContains(s2, c))
			vc.push_back(c);
	return vc;
}

inline uint32_t calculateScore(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 27;
	else
		return c - 'a' + 1;
}

void partOne(const std::vector<std::string>& lines) {
	uint32_t sum = 0;

	for (auto line : lines) {
		if (line.empty() || line.size() % 2 != 0)
			continue;

		uint32_t midPoint = line.size() / 2;
		auto firstHalf = line.substr(0, midPoint);
		auto secondHalf = line.substr(midPoint);
		sum += calculateScore(intersectionChar(firstHalf, secondHalf)[0]);
	}

	std::printf("Solution 1: %u\n", sum);
}

void partTwo(const std::vector<std::string>& lines) {
	uint32_t sum = 0;
	std::array<std::string, 3> stringArr;
	
	for (auto i = 0; i < lines.size(); i++) {
		stringArr[i % 3] = lines[i];
		if (i % 3 != 2)
			continue;
		auto vc = intersectionChar(stringArr[0], stringArr[1]);
		for (auto c : vc) {
			if (stringContains(stringArr[2], c)) {
				sum += calculateScore(c);
				break;
			}
		}
	}
	std::printf("Solution 2: %u\n", sum);
}

int main(int argc, char** argv) {
	std::vector<std::string> lines;
	if (argc == 0) {
		readStrings(std::cin, lines);
	} else {
		std::ifstream ifs(argv[1]);
		readStrings(ifs, lines);
		ifs.close();
	}
	partOne(lines);
	partTwo(lines);
}
