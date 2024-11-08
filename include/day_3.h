#pragma once
#include "include/solution.h"

class DayThreeSolution : public Solution {
public:
    inline DayThreeSolution(const std::vector<std::string>& lines);
    void run() override;
private:
};

DayThreeSolution::DayThreeSolution(const std::vector<std::string>& lines)
    : Solution(lines) {
}
