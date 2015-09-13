#pragma once

#include <vector>

namespace lame {

	class File
	{
	public:
		static bool readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filepath, std::string& buffer);
	};

}
