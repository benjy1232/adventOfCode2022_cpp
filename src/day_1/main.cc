#include <cstdio>
#include <fstream>
#include <queue>
#include <string>
#include "include/read_file.h"

int main(int argc, char** argv) {
	std::vector<std::string> strings;

	if (argc == 1) {
		readStrings(std::cin, strings);
	} else {
		std::ifstream ifs(argv[1]);
		readStrings(ifs, strings);
		ifs.close();
	}

	std::priority_queue<int> pq;
	int current_sum = 0;

	for (auto line : strings) {
		if (line.empty()) {
			pq.push(current_sum);
			current_sum = 0;
		} else {
			current_sum += std::stoi(line);
		}
	}
	pq.push(current_sum);
	current_sum = 0;


	std::printf("Solution 1:  %d\n", pq.top());

	for (int i = 0; i < 3; i++) {
		current_sum += pq.top();
		pq.pop();
	}

	std::printf("Solution 2:  %d\n", current_sum);
}
