#include "include/day_1.h"

#include <queue>

void DayOne::Solution::run() {
	std::priority_queue<std::int32_t> pq;
	int currentSum = 0;

	for (const auto& line : getLines()) {
		if (line.empty()) {
			pq.push(currentSum);
			currentSum = 0;
		} else {
			currentSum += std::stoi(line);
		}
	}
	pq.push(currentSum);
	currentSum = 0;

	setPartOneSolution(pq.top());
	for (int i = 0; i < 3; i++) {
		currentSum += pq.top();
		pq.pop();
	}

	setPartTwoSolution(currentSum);
}
