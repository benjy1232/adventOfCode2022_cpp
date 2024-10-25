#pragma once
#include "solution.h"

namespace DayOne {
  class Solution : public ::Solution
  {
  public:
    inline Solution(const std::vector<std::string>& lines);
    void run() override;
  };
}

DayOne::Solution::Solution(const std::vector<std::string>& lines)
  : ::Solution(lines)
{
}

