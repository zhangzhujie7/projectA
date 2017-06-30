#pragma once
#include <Windows.h> 
#include <time.h>  
#include <iostream>  
#include <vector>
using namespace std;
struct Server
{
	string serverName;//server's name
	int cpuCores;//server's cpu core number
	int remainCPU;//server's cpu core number remaining
	int RAMSize;//server's ram size
	int remainRAM;//server's ram size remaining
};
struct Job
{
	string jobName;//job's name
	int jobCPU;//cpu cores the job needs
	int jobRAM;//ram size the job needs
	double time;//time the job costs
	int serverId;//server's Id
};

static vector<Job> jobs;
static vector<Server> servers;

class MyTimer
{
public:
	
	MyTimer();
	~MyTimer();
	void StartTimer(vector<Job> &jobs);
	void EndTimer();
	static DWORD WINAPI ThreadFunc(LPVOID pParam);
private:
	HANDLE m_hThread;
};


MyTimer::MyTimer() : m_hThread(NULL)
{
}
MyTimer::~MyTimer()
{
}
void MyTimer::StartTimer(vector<Job> &jobs)
{
	m_hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)(&jobs), 0, NULL);
}
void MyTimer::EndTimer()
{
	CloseHandle(m_hThread);
}
DWORD WINAPI MyTimer::ThreadFunc(LPVOID pParam)
{
	time_t t1, t2;
	double  Diff = 0;
	t1 = time(NULL);
	while (1)
	{		
		t2 = time(NULL);
		Diff = difftime(t2, t1);
		//refresh every one second
		if ((int)Diff == 1)
		{
			if (jobs.size() > 0)
			{
				for (auto it = jobs.begin(); it != jobs.end(); )
				{
					//finished
					if (it->time <= 0)
					{
						cout << "Job " + it->jobName + " has done!" << endl;
						//release the server's resource
						int serverId = it->serverId - 1;
						servers[serverId].remainCPU = servers[serverId].remainCPU + it->jobCPU;
						servers[serverId].remainRAM = servers[serverId].remainRAM + it->jobRAM;
						//delete from the jobs
						it = jobs.erase(it);
					}
					else//unfinished
					{
						it->time--;
					}
					if (it == jobs.end()) break;
					else it++;
				}
			}
			

			t1 = t2;
		}
	}
	return 0;
}