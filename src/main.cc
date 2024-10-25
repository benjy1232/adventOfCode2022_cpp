#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
	#include <unistd.h>
}

const char OPTIONS[] = "df";
std::string filename;
std::uint32_t dayNumber;

/**
 * \brief Reads the lines from a given file and stores them in a vector of strings
 *
 * \param[in] in - The Input Stream to read data from
 * \return Returns a list of strings where each string is the equivalent to a single line
 */
std::vector<std::string> readStrings(std::istream& in) {
	std::vector<std::string> ret;
	std::string s;
	while (std::getline(in, s))
		ret.push_back(s);
	return ret;
}

void parseArgs(int argc, char** argv) {
	char opt = getopt(argc, argv, OPTIONS);
	while (opt != -1) {
		switch (opt)
		{
		case 'd':
			dayNumber = atoi(optarg);
			break;
		case 'f':
			filename = optarg;
			break;
		default:
			break;
		}
	}
};

int main(int argc, char** argv)
{
	filename = "";

	parseArgs(argc, argv);

	std::cout << "Day Number: " << dayNumber << std::endl;
	std::cout << "File Name: " << filename << std::endl;
}
