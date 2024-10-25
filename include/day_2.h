#pragma once
#include "solution.h"

namespace DayTwo
{
  class Solution : public ::Solution
  {
  public:
    inline Solution(const std::vector<std::string>& lines);
    inline void run() override;
  private:
    void partOne();
    void partTwo();
  };
}

DayTwo::Solution::Solution(const std::vector<std::string>& lines)
: ::Solution(lines)
{
}

void
DayTwo::Solution::run()
{
  partOne();
  partTwo();
}
