#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>

#include "include/read_file.h"
#include "include/solution.h"
#include "include/day_1.h"
#include "include/day_2.h"
#include "include/day_3.h"

const char OPTS[] = "d:f:";

uint32_t highestCompletedDay = 3;

uint32_t dayNum = 0;
bool useStdin = false;
std::string filename = "";

void parseArgs(int argc, char** argv) {
    char opt = getopt(argc, argv, OPTS);
    while (opt != -1) {
		switch (opt) {
		case 'd':
		{
			dayNum = atoi(optarg);
			break;
		}
		case 'f':
		{
			filename = optarg;
			if (filename == "-" || filename == "--")
				useStdin = true;
			break;
		}
		default:
			break;
		}
		opt = getopt(argc, argv, OPTS);
	}

	if (filename.empty())
		useStdin = true;
}

int main(int argc, char** argv) {
	parseArgs(argc, argv);
	std::vector<std::string> lines;

	if (useStdin) {
		readStrings(std::cin, lines);
	} else {
		std::ifstream ifs(filename);
		readStrings(ifs, lines);
		ifs.close();
	}

	if (dayNum == -1) {
		std::fprintf(stderr, "Expected a day\n");
		return 1;
	} else if (dayNum > highestCompletedDay || dayNum == 0) {
		std::fprintf(stderr, "Expected a day in range [1, %u]\n",
				highestCompletedDay);
        return 1;
	}

	std::unique_ptr<Solution> soln = nullptr;

	switch(dayNum) {
	case 1:
		soln = std::make_unique<DayOne::Solution>(lines);
		break;
	case 2:
		soln = std::make_unique<DayTwo::Solution>(lines);
		break;
        case 3:
		soln = std::make_unique<DayThreeSolution>(lines);
		break;
	default:
		break;
	};

	if (!soln) {
		return 1;
	}
	soln->run();
	std::printf("Day %u:\n", dayNum);
	std::printf("Part One: ");
	if (std::holds_alternative<uint32_t>(soln->getPartOneSolution()))
		std::printf("%d", std::get<uint32_t>(soln->getPartOneSolution()));
	else
		std::printf("%s", std::get<std::string>(soln->getPartOneSolution()).c_str());
	std::printf("\n");

	std::printf("Part Two: ");
	if (std::holds_alternative<uint32_t>(soln->getPartTwoSolution()))
		std::printf("%d", std::get<uint32_t>(soln->getPartTwoSolution()));
	else
		std::printf("%s", std::get<std::string>(soln->getPartTwoSolution()).c_str());
	std::printf("\n");
}
