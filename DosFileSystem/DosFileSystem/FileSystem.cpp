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

/*��ʼ�������*/
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

// �����ļ�Ŀ¼ ������������ "MD"����   ���������������� ���·��
auto CFileSystem::CreateDirectory(FileNode* root, char* fileName) -> void
{
	auto fileNode = new FileNode;
	strcpy(root->name, fileName);

	/**
	 * To be fixed :
	 *		����ʹ�üӺ�
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
	// ��ʼ���ļ�ϵͳ
	auto root = InitRootNode();
	cout << "Welcome to Zinux " << "[�汾 1.0 Beta��]" << endl;
	cout << "��Ȩ���� (c) NCEPU ���1902 ���ʡ���������Ȩ���� " << endl << endl;
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
				cout << "'" << cmd << "'" << " �����ڲ����ⲿ���Ҳ���ǿ����еĳ�����������ļ���" << endl;
			}
		}
		cout << root->path << ">";
	}
}
