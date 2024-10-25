#include "include/day_1.h"

#include <queue>
#include <string>

void
DayOne::Solution::run()
{
  std::priority_queue<std::uint32_t> pq;
  std::uint32_t currentSum = 0;

  for (auto line : getLines())
    {
      if (line.empty())
	{
	  pq.push(currentSum);
	  currentSum = 0;
	}
      else
	{
	  currentSum += std::stoul(line);
	}
    }

  pq.push(currentSum);
  currentSum = 0;

  setPartOneSolution(pq.top());

  for (int i = 0; i < 3; i++)
    {
      currentSum += pq.top();
      pq.pop();
    }

  setPartTwoSolution(pq.top());
}

