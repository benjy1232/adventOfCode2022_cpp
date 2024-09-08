#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "include/read_file.h"

enum RPS {
	R = 1,
	P,
	S
};

/**
 * \brief RoundOutcome enum to multiply by 3 for score
 */
enum RoundOutcome {
	L = 0,
	D,
	W
};

const std::array<std::tuple<char, RPS>, 3> OPP_MOVES = {
	std::tuple('A', R),
	std::tuple('B', P),
	std::tuple('C', S)
};

const std::array<std::tuple<char, RPS>, 3> YOUR_MOVES = {
	std::tuple('X', R),
	std::tuple('Y', P),
	std::tuple('Z', S)
};

const std::array<std::tuple<char, RoundOutcome>, 3> OUTCOMES = {
	std::tuple('X', L),
	std::tuple('Y', D),
	std::tuple('Z', W)
};

RoundOutcome calculateOutcome(const RPS yourMove, const RPS oppMove) {
	if (yourMove == oppMove)
		return D;

	RoundOutcome o = W;
	switch (yourMove)
	{
	case R:
		if (oppMove == P) { o = L; }
		break;
	case P:
		if (oppMove == S) { o = L; }
		break;
	case S:
		if (oppMove == R) { o = L; }
		break;
	}
	return o;
}

inline uint32_t calculateScore(const RPS yourMove, const RoundOutcome outcome) {
	return static_cast<uint32_t>(yourMove) +
		static_cast<uint32_t>(outcome) * 3;
}

void solutionOne(std::vector<std::string>& strs) {
	uint32_t score = 0;
	RPS oppMove;
	RPS yourMove;
	for (auto str : strs) {
		for (auto t : OPP_MOVES)
			if (std::get<0>(t) == str[0]) oppMove = std::get<1>(t);

		for (auto t : YOUR_MOVES)
			if (std::get<0>(t) == str[2]) yourMove = std::get<1>(t);
		score += calculateScore(yourMove, calculateOutcome(yourMove, oppMove));
	}
	std::printf("Solution 1: %u\n", score);
}

void solutionTwo(std::vector<std::string>& strs) {
	uint32_t score = 0;
	RPS oppMove;
	RoundOutcome outcome;

	auto getNext = [](RPS rps) {
		if (rps == R) return P;
		if (rps == P) return S;
		return R;
	};

	for (auto str : strs) {
		for (auto t : OPP_MOVES)
			if (std::get<0>(t) == str[0]) oppMove = std::get<1>(t);

		for (auto t : OUTCOMES)
			if (std::get<0>(t) == str[2]) outcome = std::get<1>(t);

		RPS rps = R;
		while (calculateOutcome(rps, oppMove) != outcome)
				rps = getNext(rps);

		score += calculateScore(rps, outcome);
	}
	std::printf("Solution 2: %u\n", score);
}

int main(int argc, char** argv) {
	std::vector<std::string> strings;

	if (argc == 1) { /* No argument - read stdin */
		readStrings(std::cin, strings);
	} else {
		std::ifstream ifs(argv[1]);
		readStrings(ifs, strings);
	}
	solutionOne(strings);
	solutionTwo(strings);
}
