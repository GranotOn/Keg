#include "stadx.h"

#include "FileSystem.h"

bool Keg::FileSystem::CreateFolder(std::string folderPath, std::string folderName)
{
	return std::filesystem::create_directories(folderPath + "\\" + folderName);
}

bool Keg::FileSystem::RemoveFolder(std::string folderPath, std::string folderName)
{
	return std::filesystem::remove(folderPath + "\\" + folderName);
}

bool Keg::FileSystem::ChangeFolderName(std::string folderPath, std::string newName)
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
		KEG_ENGINE_ERROR("FileSystem::ChangeFolderName : {0}", e.what());
		return false;
	}
}

bool Keg::FileSystem::CopyFile(std::string filePath, std::string fileNewPath)
{
	try {
		std::filesystem::copy(filePath, fileNewPath);
		return true;
	}
	catch (const std::exception& e) {
		KEG_ENGINE_ERROR("FileSystem::CopyFile : {0}", e.what());
		return false;
	}
}

std::string Keg::FileSystem::GetPath(std::string path)
{
	return std::filesystem::current_path().string() + "\\" + path;
}

std::string Keg::FileSystem::GetCurrentPath()
{
	return std::filesystem::current_path().string();
}
