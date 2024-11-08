#include "include/day_2.h"

#include <array>

enum class RPS : uint32_t {
    R = 1,
    P,
    S
};

enum class RoundOutcome : uint32_t {
    L = 0,
    D,
    W
};

struct RpsMove {
    RPS  move;
    char symbol;
};

struct OutcomeSym {
    RoundOutcome outcome;
    char         symbol;
};

const std::array<RpsMove, 3> OPP_MOVES = {{
	{ RPS::R, 'A' },
	{ RPS::P, 'B' },
	{ RPS::S, 'C' }
}};

const std::array<RpsMove, 3> YOUR_MOVES = {{
	{ RPS::R, 'X' },
	{ RPS::P, 'Y' },
	{ RPS::S, 'Z' }
}};

const std::array<OutcomeSym, 3> OUTCOMES = {{
    { RoundOutcome::L, 'X' },
    { RoundOutcome::D, 'Y' },
    { RoundOutcome::W, 'Z' }
}};

RoundOutcome calculateOutcome(const RPS yourMove, const RPS oppMove) {
    if (yourMove == oppMove)
        return RoundOutcome::D;

    RoundOutcome o = RoundOutcome::W;
    switch (yourMove)
    {
    case RPS::R:
        if (oppMove == RPS::P) { o = RoundOutcome::L; }
        break;
    case RPS::P:
        if (oppMove == RPS::S) { o = RoundOutcome::L; }
        break;
    case RPS::S:
        if (oppMove == RPS::R) { o = RoundOutcome::L; }
        break;
    }
    return o;
}

inline RPS getOppMove(char move) {
    for (auto m : OPP_MOVES)
        if (m.symbol == move)
            return m.move;
    return RPS::R;
}

inline uint32_t calculateScore(const RPS yourMove, const RoundOutcome outcome) {
    return static_cast<uint32_t>(yourMove) +
        static_cast<uint32_t>(outcome) * 3;
}

uint32_t solutionOne(const std::vector<std::string>& strs) {
    uint32_t score = 0;
    auto getYourMove = [](char move) -> RPS {
        for (auto yourMove : YOUR_MOVES)
            if (yourMove.symbol == move)
                return yourMove.move;
        return RPS::R;
    };
    RPS oppMove;
    RPS yourMove;
    for (auto str : strs) {
        oppMove = getOppMove(str[0]);

        yourMove = getYourMove(str[2]);
        score += calculateScore(yourMove, calculateOutcome(yourMove, oppMove));
    }

    return score;
}

uint32_t solutionTwo(const std::vector<std::string>& strs) {
    uint32_t score = 0;
    RPS oppMove;
    RoundOutcome outcome;

    auto getOutcome = [](char outcomeSym) {
        for (auto m : OUTCOMES)
            if (m.symbol == outcomeSym)
                return m.outcome;
        return RoundOutcome::L;

    };

    auto getNext = [](RPS rps) {
        if (rps == RPS::R) return RPS::P;
        if (rps == RPS::P) return RPS::S;
        return RPS::R;
    };

    for (auto str : strs) {
        oppMove = getOppMove(str[0]);
        outcome = getOutcome(str[2]);
        RPS rps = RPS::R;
        while (calculateOutcome(rps, oppMove) != outcome)
                rps = getNext(rps);

        score += calculateScore(rps, outcome);
    }

    return score;
}

void DayTwo::Solution::run() {
    setPartOneSolution(solutionOne(getLines()));
    setPartTwoSolution(solutionTwo(getLines()));
}
