#include "pch.h"
#include "CSpoolingOutput.h"
#include <iostream>
#include <string>

CSpoolingOutput::CSpoolingOutput(const int task1_nums, const int task2_nums)
	: nTask1(task1_nums), nTask2(task2_nums)
{
	InitAllTasks(nTask1, nTask2);
}

CSpoolingOutput::CSpoolingOutput()
{
	InitPcbs();
	InitReqBlocks();
	for (auto& i : C2)
	{
		for (int& j : i)
		{
			j = 0;
		}
	}

	for (COUNTER& c1 : C1)
	{
		c1 = 100;
	}

	C3 = 10;

	ptr0 = 0;
	ptr1 = 0;
}

void CSpoolingOutput::InitAllTasks(const int task1_nums, const int task2_nums)
{
	nTask1 = task1_nums;
	nTask2 = task2_nums;

	InitPcbs();
	InitReqBlocks();
	pcb[0].count = nTask1;
	pcb[1].count = nTask2;

	for (auto& i : C2)
	{
		for (int& j : i)
		{
			j = 0;
		}
	}

	for (COUNTER& c1 : C1)
	{
		c1 = 100;
	}

	C3 = 10;

	ptr0 = 0;
	ptr1 = 0;


	if (nTask1 == FILE_END)
	{
		pcb[0].status = FINISH_STATUS;
	}
	if (nTask2 == FILE_END)
	{
		pcb[1].status = FINISH_STATUS;
	}
}

void CSpoolingOutput::InitPcbs()
{
	COUNTER counter = 0;
	for (auto& i : pcb)
	{
		i.count = 0;
		i.x = 0;
		i.status = READY_STATUS;
		i.id = counter;
		counter++;
	}
}

void CSpoolingOutput::InitReqBlocks()
{
	for (Reqblock& r : reqblock)
	{
		r.length = 0;
		r.reqname = -1;
		r.addr = 0;
	}
}

auto CSpoolingOutput::PtrBufferNext(int& ptr) -> int
{
	int old = ptr;
	ptr = (ptr + 1) % 100;
	return old;
}

auto CSpoolingOutput::PtrReqBlocksNext(int& ptr) -> int
{
	int old = ptr;
	ptr = (ptr + 1) % 10;
	return old;
}

void CSpoolingOutput::Start()
{
	while (true)
	{
		double x = GetRandomDouble(0, 1);
		if (x <= 0.45 && pcb[0].status == READY_STATUS)
		{
			FillLogOutBuffer(0, "进程0启动");
			Thread0();
		}
		else if (0.45 < x && x <= 0.9 && pcb[1].status == READY_STATUS)
		{
			FillLogOutBuffer(1, "进程1启动");
			Thread1();
		}
		else if (pcb[2].status == READY_STATUS)
		{
			FillLogOutBuffer(2, "Spooling 进程启动");
			Spooling();
		}
		if (pcb[0].status == FINISH_STATUS && pcb[1].status == FINISH_STATUS && pcb[2].status == FINISH_STATUS)
		{
			FillLogOutBuffer(2, "程序运行结束！");
			break;
		}
	}
}

void CSpoolingOutput::Thread0()
{
	pcb[0].x = GetRandomInteger(0, 9);
	// pcb[0].status = RUN_STATUS;
	this->Request(0);
}

void CSpoolingOutput::Thread1()
{
	pcb[1].x = GetRandomInteger(0, 9);
	// pcb[1].status = RUN_STATUS;
	this->Request(1);
}

void CSpoolingOutput::Request(const int pid)
{
	if (C1[pid] == 0)
	{
		// std::cout << "// log: 输出井以满 进程" << pid << "等待" << std::endl;

		std::string logs = "输出井已满，进程" + std::to_string(pid) + "等待";
		FillLogOutBuffer(pid, logs);
		pcb[pid].status = WAITING_BUFFER_STATUS;
		return;
		// Spooling();
	}
	buffer[pid][C2[pid][0]] = pcb[pid].x;
	C1[pid] --;
	PtrBufferNext(C2[pid][0]);

	if (pcb[pid].x == FILE_END)
	{
		if (C3 == 0)
		{

			std::string logs2 = "进程" + std::to_string(pid) + "缺少输出空闲请求块等待";
			FillLogOutBuffer(pid, logs2);
			pcb[pid].status = WAIT_REQBLOCK_STATUS;
			// return;
			Spooling();
		}
		if (C3 > 0)
		{
			// log: 进程 pid 完成一个文件
			reqblock[ptr1].reqname = pid;
			reqblock[ptr1].addr = C2[pid][1];
			reqblock[ptr1].length = BufferPtrLength(C2[pid][0], C2[pid][1]);
			std::string logs = "空闲块请求成功!";
			FillLogOutBuffer(pid, logs);
			logs = "位置：" + std::to_string(reqblock[ptr1].addr) + ", 长度：" + std::to_string(reqblock[ptr1].length);
			FillLogOutBuffer(pid, logs);
			// C2[pid][1] = (C2[pid][1] + reqblock[ptr1].length) % 100;
			C2[pid][1] = C2[pid][0];
			PtrReqBlocksNext(ptr1);
			C3 --;
			pcb[pid].count --;
			if (pcb[2].status == WAIT_REQUEST_STATUS)
			{
				//唤醒spooling
				std::string logs_2 = "Spooling 唤醒";
				FillLogOutBuffer(2, logs_2);
				pcb[2].status = READY_STATUS;
				return;
				// Spooling();
			}
			// else
			if (pcb[pid].count == 0)
			{
				pcb[pid].status = FINISH_STATUS;
				// std::cout << "进程" << pid << "运行结束\n";
				std::string logs_2 = "进程" + std::to_string(pid) + "运行结束";
				FillLogOutBuffer(pid, logs_2);
				return;
			}
			// std::cout << "进程" << pid << "完成一个文件，还剩" << pcb[pid].count << "个文件\n";
			std::string logs_2 = "进程" + std::to_string(pid) + "完成一个文件，还剩" + std::to_string(pcb[pid].count) + "个文件";
			FillLogOutBuffer(pid, logs_2);
			if (pid == 0)
			{
				Thread0();
			}
			else
			{
				Thread1();
			}
		}
	}
	else
	{
		if (pid == 0)
		{
			Thread0();
		}
		else
		{
			Thread1();
		}
	}
}

void CSpoolingOutput::Spooling()
{
	// log spooling 启动
	int pid = 2;
	if (C3 == 10)
	{
		// std::cout << "spooling请求输出块空\n";
		FillLogOutBuffer(pid, "spooling 请求输出块空");
		if (pcb[0].status == FINISH_STATUS && pcb[1].status == FINISH_STATUS)
		{
			pcb[pid].status = FINISH_STATUS;
			// log 所有输出完成
			return;
		}
		pcb[pid].status = WAIT_REQUEST_STATUS;
		// puts("无申请块,SPOOLING进程等待");
		FillLogOutBuffer(pid, "无申请块， Spooling进程等待");
		return;
	}
	// log
	// std::cout << "来自进程" << reqblock[ptr0].reqname << "的输出" << std::endl;
	FillLogOutBuffer(pid, "来自进程" + std::to_string(reqblock[ptr0].reqname) + "的输出");
	std::string logs;
	for (int i = reqblock[ptr0].addr; i != (reqblock[ptr0].addr + reqblock[ptr0].length) % 100; i = (i + 1) % 100)
	{
		// std::cout << buffer[reqblock[ptr0].reqname][i];
		logs += std::to_string(buffer[reqblock[ptr0].reqname][i]);
		C1[reqblock[ptr0].reqname] ++;
	}
	FillLogOutBuffer(pid, logs);
	FillLogOutBuffer(pid, "Spooling输出完成");
	for (int i = 0; i < 2; i++)
	{
		if (pcb[i].status == WAITING_BUFFER_STATUS)
		{
			pcb[i].status = READY_STATUS;
			// log 进程i唤醒
			FillLogOutBuffer(i, "进程被唤醒");
			// printf("进程%d又可以执行了\n", i);
			// return;
		}
	}
	PtrReqBlocksNext(ptr0);
	C3++;
	for (int i = 0; i < 2; i++)
	{
		if (pcb[i].status == WAIT_REQBLOCK_STATUS)
		{
			pcb[i].status = READY_STATUS;
			// log: 进程 i唤醒
			FillLogOutBuffer(i, "进程被唤醒");
			// printf("进程%d又可以执行了\n", reqblock[ptr0].reqname);
			// return;
		}
	}
	// Spooling();
}

int CSpoolingOutput::BufferPtrLength(const int ptrEnd, const int ptrBegin)
{
	if (ptrEnd > ptrBegin)
	{
		return ptrEnd - ptrBegin;
	}
	return ptrEnd - ptrBegin + 100;
}

void CSpoolingOutput::FillLogOutBuffer(const int pid, const std::string& logs)
{
	if (pid == 0)
	{
		vTask0Logs.push(logs);
	}
	else if (pid == 1)
	{
		vTask1Logs.push(logs);
	}
	else if (pid == 2)
	{
		vTask2Logs.push(logs);
	}
}