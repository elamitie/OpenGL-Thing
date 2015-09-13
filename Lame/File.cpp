#include "File.h"
#include <fstream>

namespace lame {

	bool File::readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail())
		{
			perror(filepath.c_str());
			return false;
		}

		// Seek to end
		file.seekg(0, std::ios::end);

		// Get the file size
		unsigned int filesize = (unsigned int)file.tellg();
		file.seekg(0, std::ios::beg);

		// Reduce file size by any header bytes that might be present
		filesize -= (unsigned int)file.tellg();

		buffer.resize(filesize);
		file.read((char*)&(buffer[0]), filesize);
		file.close();

		return true;
	}

	bool File::readFileToBuffer(std::string filepath, std::string& buffer)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail())
		{
			perror(filepath.c_str());
			return false;
		}

		// Seek to end
		file.seekg(0, std::ios::end);

		// Get the file size
		unsigned int filesize = (unsigned int)file.tellg();
		file.seekg(0, std::ios::beg);

		// Reduce the file size by any header bytes that might be present
		filesize -= (unsigned int)file.tellg();

		buffer.resize(filesize);
		file.read((char*)&(buffer[0]), filesize);
		file.close();

		return true;
	}

}
