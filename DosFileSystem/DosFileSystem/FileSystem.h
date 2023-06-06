#pragma once
#include "fileNode.h"

class CFileSystem
{
public:
	CFileSystem();
	FileNode* InitRootNode();
	auto CreateDirectory(FileNode* root, char* fileName) -> void;
	void Start();
	~CFileSystem();
};
