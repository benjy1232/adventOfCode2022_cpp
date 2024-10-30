#pragma once
#include <cstdio>

#include "include/solution.h"

namespace DayTwo {
	class Solution : public ::Solution {
	public:
		inline Solution(const std::vector<std::string>& lines);
        void run() override;
	};
}

DayTwo::Solution::Solution(const std::vector<std::string>& lines)
    : ::Solution(lines)
{
}
