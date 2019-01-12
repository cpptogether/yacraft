#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

std::vector<std::string> Utilities::SplitString(const std::string& string,
	const std::string& splitter) {
	std::regex regex(splitter);
	std::sregex_token_iterator first{ string.begin(), string.end(), regex, -1 },
		last;
	return { first, last };
}

template <class Type>
std::string Utilities::NumberToString(Type number) {
	std::ostringstream stringStream;
	stringStream << number;
	return stringStream.str();
}

template <class Type>
Type Utilities::StringToNumber(const std::string& string) {
	Type number = 0;
	if (!(std::istringstream(string) >> number)) {
		return 0;
	}
	return number;
}

std::string Utilities::File::ReadWholeFile(const std::string& path) {
	std::ifstream file(path);
	if (file.is_open()) {
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	else {
		std::cout << strerror(errno) << "\n" << path << " is not opened. PROGRAM DESTRUCTION EXECUTED.\n";

		exit(3);
	}
}