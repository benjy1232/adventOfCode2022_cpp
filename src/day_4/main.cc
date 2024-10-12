#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "include/read_file.h"

class IntRange {
public:
	IntRange() = default;

	IntRange(int32_t bottom, int32_t top) :
		m_Top(top), m_Bottom(bottom) {}
	inline int32_t getTop() const { return m_Top; }
	inline int32_t getBottom() const { return m_Bottom; }
	inline void setTop(int32_t top) { m_Top = top; }
	inline void setBottom(int32_t bottom) { m_Bottom = bottom; }

	inline bool contains(const IntRange& other);
	inline bool overlaps(const IntRange& other);
private:
	int32_t m_Top;
	int32_t m_Bottom;
};

bool IntRange::contains(const IntRange& other) {
	return other.m_Top <= this->m_Top && other.m_Bottom >= this->m_Bottom &&
		other.m_Top >= this->m_Bottom && other.m_Bottom <= this->m_Top;
}

bool IntRange::overlaps(const IntRange& other) {
	return (other.m_Bottom >= m_Bottom && other.m_Bottom <= m_Top) ||
		(other.m_Top >= m_Bottom && other.m_Top <= m_Top);
}

IntRange parseRangeString(std::string& strRange) {
	size_t dashIdx = strRange.find('-');

	if (dashIdx == strRange.npos) {
		return IntRange();
	}

	return IntRange(std::stoi(strRange.substr(0, dashIdx)),
		      std::stoi(strRange.substr(dashIdx + 1)));
}

std::array<IntRange, 2> parseLine(std::string& line) {
	size_t commaIdx = line.find(',');

	if (commaIdx == line.npos)
		return {};

	std::array<IntRange, 2> ret;
	memset(ret.data(), 0, sizeof(ret));
	std::array<std::string, 2> stringRange  = {
		line.substr(0, commaIdx), 
		line.substr(commaIdx + 1)
	};

	IntRange* iter = ret.begin();
	auto parseRangeStrIter = [&iter, &ret](std::string strRange) {
		if (iter != ret.end())
			*iter++ = parseRangeString(strRange);
	};

	std::for_each(stringRange.begin(), stringRange.end(), parseRangeStrIter);

	return ret;
}

void solution(const std::vector<std::array<IntRange, 2>>& intRanges) {
	int containsCount = 0;
	int overlapCount = 0;
	for (auto iRange : intRanges) {
		bool contained = iRange[0].contains(iRange[1]) || iRange[1].contains(iRange[0]);
		if (contained) {
			containsCount++;
		}

		if (iRange[0].overlaps(iRange[1]) || iRange[1].overlaps(iRange[0])) {
			overlapCount++;
		}
	}
	std::printf("Contains Count: %d\n", containsCount);
	std::printf("Overlap Count: %d\n", overlapCount);
}

int main(int argc, char** argv) {
	std::vector<std::string> strings;

	if (argc == 1) {
		readStrings(std::cin, strings);
	} else {
		std::ifstream ifs(argv[1]);
		readStrings(ifs, strings);
		ifs.close();
	}

	std::vector<std::array<IntRange, 2>> intRanges;
	intRanges.reserve(strings.size());
	for (auto string : strings) {
		intRanges.push_back(std::move(parseLine(string)));
	}

	solution(intRanges);
}
