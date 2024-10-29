#include <charconv>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <array>
#include <stack>
#include <string>
#include "include/read_file.h"

using CargoStack = std::stack<char>;
static const size_t NUM_STACKS = 10;

struct CargoMoveCmd {
	std::uint32_t count;
	std::uint32_t from;
	std::uint32_t to;
};

struct ShipCargo {
	std::array<CargoStack, NUM_STACKS> stacks;
	std::vector<CargoMoveCmd> moveCmds;
};

CargoMoveCmd parseMoveCmd(const std::string& line) {
	CargoMoveCmd ret;
	std::array<std::string, 3> constStrings = {
		"move ",
		" from ",
		" to "
	};

	const char* ptr = line.data();
	const char* const end = line.data() + line.size();
	for (std::size_t i = 0; i < constStrings.size(); i++) {
		const char* begin = ptr + constStrings.at(i).length();
		std::uint32_t* out = nullptr;
		bool decrementAfter = true;
		switch (i % constStrings.size()) {
			case 0:
				out = &ret.count;
				decrementAfter = false;
				break;
			case 1:
				out = &ret.from;
				break;
			default:
				out = &ret.to;
				break;
		}
		auto fromCharsResult = std::from_chars(begin, end, *out);
		if (decrementAfter)
			*out -= 1;
		ptr = fromCharsResult.ptr;
	}
	return ret;
}

ShipCargo parseLines(const std::vector<std::string>& lines) {
	ShipCargo shipCargo;
	std::array<CargoStack, NUM_STACKS> stacks;
	auto reverseStack = [](CargoStack cargoStack, CargoStack& out) {
		while (!cargoStack.empty()) {
			out.push(cargoStack.top());
			cargoStack.pop();
		}
	};

	size_t i = 0;
	for (; i < lines.size(); i++) {
		const std::string& line = lines[i];
		if (line.empty())
			break;

		size_t leftBracketIdx = line.find('[');
		while (leftBracketIdx != std::string::npos) {
			size_t cargoIdx = (leftBracketIdx + 1);
			size_t cargoStackIdx = cargoIdx / 4;
			stacks[cargoStackIdx].push(line[cargoIdx]);
			leftBracketIdx = line.find('[', cargoIdx + 1);
		}
	}
	i++;

	for (auto& cargoStack : stacks) {
		CargoStack otherStack = cargoStack;
		while (!cargoStack.empty()) {
			cargoStack.pop();
		}
		reverseStack(otherStack, cargoStack);
	}

	shipCargo.stacks = stacks;

	for (auto it = lines.begin() + i; it != lines.end(); it++) {
		shipCargo.moveCmds.push_back(parseMoveCmd(*it));
	}
	return shipCargo;
}

void partOne(ShipCargo shipCargo) {
	for (auto cmd : shipCargo.moveCmds) {
		int i = 0;
		while (i < cmd.count) {
			shipCargo.stacks.at(cmd.to).push(shipCargo.stacks.at(cmd.from).top());
			shipCargo.stacks.at(cmd.from).pop();
			i++;
		}
	}

	for (auto stack : shipCargo.stacks) {
		if (!stack.empty())
			std::printf("%c", stack.top());
	}
	std::printf("\n");
}

void partTwo(ShipCargo shipCargo) {
	for (auto cmd : shipCargo.moveCmds) {
		int i = 0;
		CargoStack cs;
		while (i < cmd.count) {
			cs.push(shipCargo.stacks.at(cmd.from).top());
			shipCargo.stacks.at(cmd.from).pop();
			i++;
		}

		while (!cs.empty()) {
			shipCargo.stacks.at(cmd.to).push(cs.top());
			cs.pop();
		}
	}
	for (auto stack : shipCargo.stacks) {
		if (!stack.empty())
			std::printf("%c", stack.top());
	}
	std::printf("\n");
}

int main(int argc, char** argv) {
	std::vector<std::string> lines;

	if (argc == 1) {
		readStrings(std::cin, lines);
	} else {
		std::ifstream ifs(argv[1]);
		readStrings(ifs, lines);
		ifs.close();
	}
	ShipCargo shipCargo = parseLines(lines);
	partOne(shipCargo);
	partTwo(shipCargo);
}
