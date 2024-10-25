#include "include/day_2.h"

namespace {
	/**
	* Moves are in order:
	* <OPP_MOVE> <YOUR_MOVE>
	*/
	const std::size_t OPP_IDX = 0;
	const std::size_t YOUR_IDX = 2;
  
	enum class RPS : std::uint32_t {
		R = 1,
		P = 2,
		S = 3
	};

	const std::uint32_t OUTCOME_MULTIPLIER = 3;
	enum class RoundOutcome : std::uint32_t {
		L = 0 * OUTCOME_MULTIPLIER,
		D = 1 * OUTCOME_MULTIPLIER,
		W = 2 * OUTCOME_MULTIPLIER
	};

	struct Move {
		RPS  move;
		char symbol;
	};

	struct Outcome {
		RoundOutcome outcome;
		char         symbol;
	};

	const Move OPP_MOVES[] = {
		{ .move = RPS::R, .symbol = 'A' },
		{ .move = RPS::P, .symbol = 'B' },
		{ .move = RPS::S, .symbol = 'C' }
	};

	inline RPS getOppMove(const char move) {
		for (auto oppMove : OPP_MOVES) {
			if (oppMove.symbol == move)
				return oppMove.move;
		}
		return RPS::R;
	}
}

RoundOutcome calculateOutcome(RPS you, RPS opp) {
	if (you == opp)
		return RoundOutcome::D;

	switch (you) {
	case RPS::R:
		if (opp == RPS::P) { return RoundOutcome::L; }
		break;
	case RPS::P:
		if (opp == RPS::S) { return RoundOutcome::L; }
		break;
	case RPS::S:
		if (opp == RPS::R) { return RoundOutcome::L; }
		break;
	}
	return RoundOutcome::W;
}

RPS getMoveFromOutcome(RPS oppMove, RoundOutcome outcome) {
	if (outcome == RoundOutcome::D) return oppMove;

	switch(oppMove)	{
	case RPS::R:
		if (outcome == RoundOutcome::L) { return RPS::P; }
		return RPS::S;
	case RPS::P:
		if (outcome == RoundOutcome::L) { return RPS::S; }
		return RPS::R;
	case RPS::S:
		if (outcome == RoundOutcome::L) { return RPS::R; }
		return RPS::P;
	}
}

void DayTwo::Solution::partOne() {
	const Move YOUR_MOVES[] = {
		{ .move = RPS::R, .symbol = 'X' },
		{ .move = RPS::P, .symbol = 'Y' },
		{ .move = RPS::S, .symbol = 'Z' }
	};

	uint32_t score = 0;
	auto getYourMove = [YOUR_MOVES](const char move) -> RPS {
		for (auto yourMove : YOUR_MOVES) {
			if (yourMove.symbol == move)
				return yourMove.move;
		}
		return RPS::R;
	};

	for (const auto& line : getLines()) {
		if (line.empty())
			continue;

		RPS oppMove = getOppMove(line[OPP_IDX]);
		RPS yourMove = getYourMove(line[YOUR_IDX]);
		score += static_cast<uint32_t>(calculateOutcome(oppMove, yourMove));
	}

	setPartOneSolution(score);
}

void
DayTwo::Solution::partTwo()
{
	Outcome OUTCOMES[] = {
		{ .outcome = RoundOutcome::L, .symbol = 'X' },
		{ .outcome = RoundOutcome::D, .symbol = 'Y' },
		{ .outcome = RoundOutcome::W, .symbol = 'Z' }
	};

	auto getExpectedOutcome = [OUTCOMES](const char input) -> RoundOutcome {
		for (auto outcome : OUTCOMES) {
			if (outcome.symbol == input)
				return outcome.outcome;
		}

		return RoundOutcome::L;
	};

	uint32_t score = 0;
	for (const auto& line : getLines()) {
		if (line.empty())
			continue;
		
		RPS oppMove = getOppMove(line[OPP_IDX]);
		RoundOutcome outcome = getExpectedOutcome(line[YOUR_IDX]);
		RPS yourMove = getMoveFromOutcome(oppMove, outcome);
		score += static_cast<uint32_t>(calculateOutcome(oppMove, yourMove));
	}

	setPartTwoSolution(score);

}
