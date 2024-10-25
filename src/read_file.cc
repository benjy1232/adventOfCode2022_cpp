#include <iostream>
#include <string>
#include <vector>

#include "include/read_file.h"

/**
 * @brief Reads strings from a given file and stores it into a vector of strings
 *
 * @param[in] in - input stream to read from
 * @param[out] out - vector to store data into
 */
void readStrings(std::istream& in, std::vector<std::string>& out) {
	std::string s;
	while (std::getline(in, s))
		out.emplace_back(s);
}
