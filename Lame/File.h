#pragma once

#include <vector>

namespace lame {

	class File
	{
	public:
		static bool ReadFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer);
		static bool ReadFileToBuffer(std::string filepath, std::string& buffer);
	};

}
