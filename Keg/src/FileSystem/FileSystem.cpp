#include "stadx.h"

#include "FileSystem.h"

bool Keg::FileSystem::createFolder(std::string folderPath, std::string folderName)
{
	return std::filesystem::create_directories(folderPath + "\\" + folderName);
}

bool Keg::FileSystem::removeFolder(std::string folderPath, std::string folderName)
{
	return std::filesystem::remove(folderPath + "\\" + folderName);
}

bool Keg::FileSystem::changeFolderName(std::string folderPath, std::string newName)
{
	try {
		std::string temp = folderPath;
		size_t index = folderPath.find_last_of("\\");
		folderPath = folderPath.substr(0, size_t(index + 1));
		folderPath += newName;
		std::filesystem::rename(temp, folderPath);
		return true;
	}
	catch(const std::exception& e) {
		return false;
	}
}

bool Keg::FileSystem::copyFile(std::string filePath, std::string fileNewPath)
{
	try {
		std::filesystem::copy(filePath, fileNewPath);
		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

std::string Keg::FileSystem::getPath(std::string path)
{
	return std::filesystem::current_path().string() + "\\" + path;
}

std::string Keg::FileSystem::getCurrentPath()
{
	return std::filesystem::current_path().string();
}
