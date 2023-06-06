#include "FileSystem.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "fileNode.h"
#include "utils.h"
using namespace std;


CFileSystem::CFileSystem()
{
	Start();
}


CFileSystem::~CFileSystem()
{
}

/*初始化根结点*/
FileNode* CFileSystem::InitRootNode()
{
	auto root = static_cast<FileNode*>(malloc(sizeof(FileNode)));
	strcpy(root->name, "root");
	strcpy(root->path, "\\root");
	strcpy(root->createTime, GetCurrentSystemTime());
	root->readOnly = false;
	root->hidden = false;
	root->directory = true;
	// root->files = nullptr;
	root->pNode = nullptr;
	return root;
}

// 创建文件目录 —————— "MD"命令   ———————— 相对路径
auto CFileSystem::CreateDirectory(FileNode* root, char* fileName) -> void
{
	auto fileNode = new FileNode;
	strcpy(root->name, fileName);

	/**
	 * To be fixed :
	 *		不能使用加号
	 */	
	// strcpy(root->path, root->path + "\\" + fileName);
	strcpy(root->createTime, GetCurrentSystemTime());
	root->readOnly = false;
	root->hidden = false;
	root->directory = true;
	root->pNode = nullptr;

	root->files.push_back(fileNode);
}

void CFileSystem::Start()
{
	// 初始化文件系统
	auto root = InitRootNode();
	cout << "Welcome to Zinux " << "[版本 1.0 Beta版]" << endl;
	cout << "版权所有 (c) NCEPU 软件1902 张仁。保留所有权力。 " << endl << endl;
	cout << root->path << ">";
	while (true)
	{
		char command[256];
		cin.getline(command, 256);
		if (strlen(command) != 0)
		{
			const auto delim = " ";
			char* param;
			char* cmd = strtok_s(command, delim, &param);
			const char* cmdUpper = ToUppercase(cmd);

			if (0 == strcmp(cmdUpper, "MD"))
			{
				cout << "'" << cmd << "'" << " not found" << endl;
			}
			else if (0 == strcmp(cmdUpper, "EXIT"))
			{
				exit(EXIT_SUCCESS);
			}
			else if (0 == strcmp(cmdUpper, "ATTRIB"))
			{
			}
			else if (0 == strcmp(cmdUpper, "DIR"))
			{
			}
			else if (0 == strcmp(cmdUpper, "RD"))
			{
			}
			else if (0 == strcmp(cmdUpper, "CD"))
			{
			}
			else if (0 == strcmp(cmdUpper, "TREE"))
			{
			}
			else if (0 == strcmp(cmdUpper, "COPY"))
			{
			}
			else if (0 == strcmp(cmdUpper, "DEL"))
			{
			}
			else if (0 == strcmp(cmdUpper, "TYPE"))
			{
			}
			else if (0 == strcmp(cmdUpper, "REN"))
			{
			}
			else if (0 == strcmp(cmdUpper, "CLS"))
			{
				system("cls");
			}
			else
			{
				cout << "'" << cmd << "'" << " 不是内部或外部命令，也不是可运行的程序或批处理文件。" << endl;
			}
		}
		cout << root->path << ">";
	}
}
