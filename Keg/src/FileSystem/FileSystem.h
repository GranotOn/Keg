#pragma once

namespace Keg {
	class FileSystem
	{
	public:
		static bool CreateFolder(std::string folderPath, std::string folderName);
		static bool RemoveFolder(std::string folderPath, std::string folderName);
		static bool ChangeFolderName(std::string folderPath, std::string newName);
		static bool CopyFile(std::string filePath, std::string fileNewPath);
		static std::string GetPath(std::string path);
		static std::string GetCurrentPath();
	};
}


