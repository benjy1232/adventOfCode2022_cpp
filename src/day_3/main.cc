#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "include/read_file.h"
using namespace std;

inline bool stringContains(const string& s, char c) {
	for (auto sc : s)
		if (sc == c)
			return true;
	return false;
}

inline vector<char> intersectionCharHelper(const string& s1, const string& s2) {
	vector<char> vc;

	auto containsLambda = [&s2, &vc](char c) {
		if (stringContains(s2, c))
			vc.push_back(c);
	};

	for_each(s1.begin(), s1.end(), containsLambda);
	return vc;
}

vector<char> intersectionChar(const string* begin, const string* end) {
  if (!begin || !end) {
    throw new runtime_error("Begin or end cannot be null");
  }

  vector<char> ret(begin->begin(), begin->end());
  while (begin != end) {
    ret = intersectionCharHelper(ret.data(), *begin);
    begin++;
  }
  return ret;
}

inline uint32_t calculateScore(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 27;
	else
		return c - 'a' + 1;
}

void partOne(const std::vector<std::string>& lines) {
	uint32_t sum = 0;
	array<string, 2> arr;

	for (auto line : lines) {
		if (line.empty() || line.size() % 2 != 0)
			continue;

		uint32_t midPoint = line.size() / 2;
		arr[0] = line.substr(0, midPoint);
		arr[1] = line.substr(midPoint);
		sum += calculateScore(intersectionChar(arr.begin(), arr.end())[0]);
	}

	std::printf("Solution 1: %u\n", sum);
}

void partTwo(const std::vector<std::string>& lines) {
	uint32_t sum = 0;
	std::array<std::string, 3> stringArr;

	for (auto i = 0; i < lines.size(); i++) {
		stringArr[i % 3] = lines[i];
		if (i % 3 == 2)
		  sum += calculateScore(intersectionChar(stringArr.begin(), stringArr.end())[0]);
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
