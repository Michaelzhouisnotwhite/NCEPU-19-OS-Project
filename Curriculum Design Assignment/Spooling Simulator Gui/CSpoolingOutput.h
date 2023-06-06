// Spooling Simulation build in 2021.07.01
// file name: CSpoolingOutput.h
// Edit by @Michael Zhou
#pragma once
#include "Foundation_Data.h"
#include "pch.h"

#include <string>
#include <vector>
#include <queue>

#define FILE_END 0

class CSpoolingOutput
{
protected:
	PCB pcb[3]{};
	int buffer[2][100]{};
	COUNTER C1[2]{}; // 可用输出井
	COUNTER C3{}; // reqBlock计数器
	int C2[2][2]{}; // 输出井指针
	/**
	 *0: end;
	 *1: begin;
	 *C2[0][0]代表buffer[0]的第一个可用空缓冲指针，C2[0][1]代表buffer[0]的第一个满缓冲指针；
	 *C2[1][0]代表buffer[1]的第一个可用空缓冲指针，C2[1][1]代表buffer [1]的第一个满缓冲指针。
	 **/

	Reqblock reqblock[10]{};
	int ptr0{}; //begain;
	int ptr1{}; // end;
	// Ptr1是要输出的第一个请求输出块指针，初值为0: begin；
	// Ptr2是空闲请求输出块指针，初值也为0 : end;
	COUNTER nTask1{};
	COUNTER nTask2{};

	std::queue<std::string> vTask0Logs;
	std::queue<std::string> vTask1Logs;
	std::queue<std::string> vTask2Logs;
public:
	CSpoolingOutput(int task1_nums, int task2_nums);
	CSpoolingOutput();
	void InitAllTasks(int task1_nums, int task2_nums);
	~CSpoolingOutput() = default;
	void InitPcbs();
	void InitReqBlocks();
	static auto PtrBufferNext(int& ptr) -> int;
	static auto PtrReqBlocksNext(int& ptr) -> int;
	void Start();

	void Thread0();
	void Thread1();

	void Request(int pid);
	void Spooling();
	static int BufferPtrLength(int ptrEnd, int ptrBegin);

	void FillLogOutBuffer(int pid, const std::string& logs);
};
