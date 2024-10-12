#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
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

struct RpsMove {
	RPS  move;
	char symbol;
};

struct OutcomeSyms {
	RoundOutcome outcome;
	char         symbol;
};
const std::array<RpsMove, 3> OPP_MOVES = {{
	{ R, 'A' },
	{ P, 'B' },
	{ S, 'C' }
}};

const std::array<RpsMove, 3> YOUR_MOVES = {{
	{ R, 'X' },
	{ P, 'Y' },
	{ S, 'Z' }
}};

const std::array<OutcomeSyms, 3> OUTCOMES = {{
	{ L, 'X' },
	{ D, 'Y' },
	{ W, 'Z' }
}};

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

inline RPS getOppMove(char move) {
	for (auto m : OPP_MOVES)
		if (m.symbol == move)
			return m.move;
	return R;
}

inline uint32_t calculateScore(const RPS yourMove, const RoundOutcome outcome) {
	return static_cast<uint32_t>(yourMove) +
		static_cast<uint32_t>(outcome) * 3;
}

void solutionOne(std::vector<std::string>& strs) {
	uint32_t score = 0;
	auto getYourMove = [](char move) -> RPS {
		for (auto yourMove : YOUR_MOVES)
			if (yourMove.symbol == move)
				return yourMove.move;
		return R;
	};
	RPS oppMove;
	RPS yourMove;
	for (auto str : strs) {
		oppMove = getOppMove(str[0]);

		yourMove = getYourMove(str[2]);
		score += calculateScore(yourMove, calculateOutcome(yourMove, oppMove));
	}
	std::printf("Solution 1: %u\n", score);
}

void solutionTwo(std::vector<std::string>& strs) {
	uint32_t score = 0;
	RPS oppMove;
	RoundOutcome outcome;

	auto getOutcome = [](char outcomeSym) {
		for (auto m : OUTCOMES)
			if (m.symbol == outcomeSym)
				return m.outcome;
		return L;

	};

	auto getNext = [](RPS rps) {
		if (rps == R) return P;
		if (rps == P) return S;
		return R;
	};

	for (auto str : strs) {
		oppMove = getOppMove(str[0]);
		outcome = getOutcome(str[2]);
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
