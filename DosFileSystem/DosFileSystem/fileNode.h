#pragma once
#include <vector>
using namespace std;

const int NAMESIZE = 100; // �ļ�������Ŀ¼������
const int PATHSIZE = 100; // ·������
const int TIMESIZE = 16; // ����ʱ�䳤��


typedef struct FileNode
{
	char name[NAMESIZE]; // �ļ�������Ŀ¼��
	char path[PATHSIZE]; // �ļ�·��
	char createTime[TIMESIZE]; // ����ʱ��
	bool readOnly; // ֻ������
	bool hidden; // ��������
	bool directory; // Ŀ¼   true--Ŀ¼�� false--�ļ�
	// FileNode** files; 
	vector<FileNode*> files;//�ļ��а������ļ����У��б�
	FileNode* pNode; // �ϼ�Ŀ¼
	
} FileNode, *FileTree;
	