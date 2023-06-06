// Spooling Simulation build in 2021.07.01
// file name: Foundation_Data.h
// Edit by @Michael Zhou

#pragma once

#define READY_STATUS 0 // 0为可执行态；
#define WAITING_BUFFER_STATUS 1 // 1为等待状态1，表示输出井满，请求输出的用户进程等待；
#define WAIT_REQUEST_STATUS 2   // 2为等待状态2，表示请求输出井空，SP00LING输出进程等待；
#define WAIT_REQBLOCK_STATUS 3 	// 3为等待状态3，表示请求输出井满，请求输出的用户进程等待；
#define FINISH_STATUS 4        	// 4为结束态，进程执行完成。

typedef int COUNTER;
typedef int* Intptr;

struct Reqblock
{
	int reqname; // 请求进程名
	int length; // 本次输出信息长度
	int addr; // 信息在输出井的首地址
};

typedef Reqblock* ReqPtr;

struct PCB
{
	int id; //进程标识数 
	int status; //进程状态
	int count; //要输出的文件数
	int x; // 进程输出时的临时变量
};

double GetRandomDouble(double min, double max);
int GetRandomInteger(int min, int max);
