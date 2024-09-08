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


	std::printf("Top Elf is carrying:\n");
	std::printf("  %d\n", pq.top());
	std::printf("\n");

	for (int i = 0; i < 3; i++) {
		current_sum += pq.top();
		pq.pop();
	}

	std::printf("Top 3 Elves are carrying:\n");
	std::printf("  %d\n", current_sum);
	std::printf("\n");
}
