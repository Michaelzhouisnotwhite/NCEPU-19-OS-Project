#pragma once
#include <vector>
using namespace std;

const int NAMESIZE = 100; // 文件名或者目录名长度
const int PATHSIZE = 100; // 路径长度
const int TIMESIZE = 16; // 创建时间长度


typedef struct FileNode
{
	char name[NAMESIZE]; // 文件名或者目录名
	char path[PATHSIZE]; // 文件路径
	char createTime[TIMESIZE]; // 创建时间
	bool readOnly; // 只读属性
	bool hidden; // 隐藏属性
	bool directory; // 目录   true--目录， false--文件
	// FileNode** files; 
	vector<FileNode*> files;//文件夹包含的文件（夹）列表
	FileNode* pNode; // 上级目录
	
} FileNode, *FileTree;
	