#include "include/day_3.h"

#include <array>
#include <set>

inline bool stringContains(const std::string &s, char c) {
    return s.find(c) != std::string::npos;
}

inline uint32_t calculateScore(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return c - 'a' + 1;
}  

std::string intersectionChars(const std::string* begin, const std::string* end) {
    if (begin == end) {
        return "";
    }

    const std::string *iter = begin + 1;
    std::set<char> ret(begin->begin(), begin->end());
    while (iter != end) {
        auto retIter = ret.begin();
        while (retIter != ret.end()) {
            if (iter->find(*retIter) == std::string::npos)
                retIter = ret.erase(retIter);
            else
                retIter++;
        }
        iter++;
    }
    return std::string(ret.begin(), ret.end());
}

int partOneSolution(const std::vector<std::string>& lines) {
    int sum = 0;
    std::array<std::string, 2> arr;

    for (auto line : lines) {
        if (line.empty() || line.size() % 2 != 0)
            continue;
        uint32_t midpoint = line.size() / 2;
        arr[0] = line.substr(0, midpoint);
        arr[1] = line.substr(midpoint);
        sum += calculateScore(intersectionChars(arr.begin(), arr.end())[0]);
    }
    return sum;
}

int partTwoSolution(const std::vector<std::string> &lines) {
    int sum = 0;
    std::array<std::string, 3> stringArr;

    for (int i = 0; i < lines.size(); i++) {
        stringArr[i % 3] = lines[i];
        if (i % 3 == 2)
          sum += calculateScore(intersectionChars(stringArr.begin(), stringArr.end())[0]);
    }
    return sum;
}

void DayThreeSolution::run() {
    setPartOneSolution(partOneSolution(getLines()));
    setPartTwoSolution(partTwoSolution(getLines()));
}
