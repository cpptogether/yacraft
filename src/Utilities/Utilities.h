#ifndef YACRAFT_UTILITIES
#define YACRAFT_UTILITIES

#include <vector>
#include <string>

namespace Utilities {

	/*
	* @brief Splits string.
	* @param string String to split.
	* @param splitter Splitter.
	* @returns std::vector<std::string> Strings which was splitted.
	*/
	std::vector<std::string> SplitString(const std::string& string,
		const std::string& splitter);

	/*
	* @brief Number to string.
	* @returns std::string Converted number to string.
	*/
	template <class Type>
	std::string NumberToString(Type number);

	/*
	* @brief Converts string to number.
	* @returns number.
	*/
	template <class Type>
	Type StringToNumber(const std::string& string);

	namespace File {

		/*
		* @brief Reads whole file to string.
		* @returns std::string Readed file.
		*/
		std::string ReadWholeFile(const std::string& path);

	}

};  // namespace Utilities

#endif 
