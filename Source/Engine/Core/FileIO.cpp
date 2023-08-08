#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Logger.h"

namespace ringo {
	std::string ringo::getFilePath()
	{
		return std::filesystem::current_path().string();
	}
	bool setFilePath(const std::filesystem::path& path)
	{
		std::error_code ec;
		std::filesystem::current_path(path, ec);
		return ec.value() == 0;
	}
	std::string getFileName(const std::filesystem::path& path)
	{
		return path.filename().string();
	}
	bool fileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}
	bool getFileSize(const std::filesystem::path& path, size_t& size)
	{
		std::error_code ec;
		size = std::filesystem::file_size(path, ec);
		return ec.value() == 0;
	}
	bool readFile(const std::filesystem::path& path, std::string& buffer)
	{
		if (!fileExists(path)) {    //this should work now. this is the code maple has
			WARNING_LOG("file not loaded: " << path.string());
			return false;
			}
		size_t size;
		if (!getFileSize(path, size)) return false;
		buffer.resize(size);
		std::ifstream stream(path);
		stream.read(buffer.data(), size);
		stream.close();
		return true;

		/*if (!std::filesystem::exists(path)) {
			std::cerr << "Error: File does not exist: " << path << std::endl;
			return false;
		}

		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cerr << "Error: Cannot open file: " << path << std::endl;
			return false;
		}

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		buffer.resize(size);
		if (!file.read(buffer.data(), size)) {
			std::cerr << "Error: Failed to read file: " << path << std::endl;
			return false;
		}

		file.close();
		return true;*/
	}
}