#include <iostream>
#include <fstream>
#include <queue>
#include <string>

int main(void) {
	std::string file_name = "input";
	std::priority_queue<int> pq;
	std::ifstream ifs(file_name.c_str());
	int current_sum = 0;

	for (std::string line; std::getline(ifs, line, '\n');) {
		if (line.empty()) {
			pq.push(current_sum);
			current_sum = 0;
		} else {
			current_sum += std::stoi(line);
		}
	}
	pq.push(current_sum);
	current_sum = 0;

	ifs.close();

	std::cout << "Top Elf is carrying: " << std::endl;
	std::cout << "\t" << pq.top() << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 3; i++) {
		current_sum += pq.top();
		pq.pop();
	}

	std::cout << "Top 3 Elves are carrying: " << std::endl;;
	std::cout << "\t" << current_sum << std::endl;;
}
