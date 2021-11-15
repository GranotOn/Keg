#pragma once
#include <iostream>

namespace Keg {
	static class FileSystem
	{
	public:
		static bool createFolder(std::string folderPath, std::string folderName);
		static bool removeFolder(std::string folderPath, std::string folderName);
		static bool changeFolderName(std::string folderPath, std::string newName);
		static bool copyFile(std::string filePath, std::string fileNewPath);
		static std::string getPath(std::string path);
		static std::string getCurrentPath();
	};
}


