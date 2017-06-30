/*This is a simple server controller designed and implemented by
 *Zhang Zhujie,StudentId:5140309368.
 *All operations are in a console window.
 *More details in readme.txt.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "MyTimer.h"
using namespace std;


int main()
{
	string fileName = "ServerInfo.inf";//Infomation of all servers with saved status
	string jobFName = "JobInfo.inf";//Infomation of all unfinished jobs with saved status

	ifstream fs(fileName, ios::in);
	ifstream js(jobFName, ios::in);
	string buffer;
	string serverName = "";
	string op;
	int cpuCores = 0;
	int remainCPU = 0;
	int RAMSize = 0;
	int remainRAM = 0;

	string jobName;
	int jobCPU;
	int jobRAM;
	double time;
	int serverId;
	//load servers' information

	if (fs.is_open())
	{
		stringstream ss;
		Server tmp;
		while (!fs.eof())
		{
			getline(fs, buffer);
			ss.str(buffer);
			ss >> serverName >> cpuCores >>remainCPU >> RAMSize >> remainRAM ;
			tmp.serverName = serverName;
			tmp.cpuCores = cpuCores;
			tmp.RAMSize = RAMSize;
			tmp.remainCPU = remainCPU;
			tmp.remainRAM = remainRAM;
			servers.push_back(tmp);
			ss.clear();
		}
	}
	fs.close();

	//load jobs' information
	if (js.is_open())
	{
		stringstream ss;
		Job tmp;
		while (!js.eof())
		{
			getline(js, buffer);
			ss.str(buffer);
			ss >> jobName >> jobCPU >> jobRAM >> time >> serverId;
			tmp.jobName=jobName;
			tmp.jobCPU = jobCPU;
			tmp.jobRAM=jobRAM;
			tmp.time=time;
			tmp.serverId = serverId;
			if (tmp.jobName!="") jobs.push_back(tmp);
			ss.clear();
		}
	}
	fs.close();

	//start multithread to simulate doing jobs
	MyTimer ct;
	ct.StartTimer(jobs);
	while (true)
	{
		cout << endl;
		cout << "Please input your operation here:"
			<< "(1)list: list the status of servers\t"
			<< "(2)show: show jobs\t"
			<< "(3)work: give servers a job\t"
			<< "(4)free: free a job\t"
			<< "(5)save: save the status of servers and jobs\t"
			<< "(6)restart: restart servers\t"
			<< "(7)exit: exit\t"
			<< endl;;
		cin >> op;
		if (op == "list")
		{

			cout << setw(12) << "ServerName" << "\t" << setw(12) << "CPUCores" << "\t" << setw(12) << "remainCPU" << "\t" << setw(12) << "RAMSize" << "\t" << setw(12) << "remainRAM" << endl;
			for (int i = 0; i < servers.size(); i++)
			{
				cout << setw(12) << servers[i].serverName << "\t" << setw(12) << servers[i].cpuCores << "\t" << setw(12) << servers[i].remainCPU << "\t" << setw(12) << servers[i].RAMSize << "\t" << setw(12) << servers[i].remainRAM << endl;
			}
		}

		if (op == "show")
		{

			cout << setw(12) << "JobName" << "\t" << setw(12) << "JobCPU" << "\t" << setw(12) << "JobRAM" << "\t" << setw(12) << "ServerName" << "\t" << setw(12) << "Time" << endl;
			for (int i = 0; i < jobs.size(); i++)
			{
				cout << setw(12) << jobs[i].jobName << "\t" << setw(12) << jobs[i].jobCPU << "\t" << setw(12) << jobs[i].jobRAM << "\t" << setw(12) << servers[jobs[i].serverId - 1].serverName << "\t" << setw(12) << jobs[i].time << endl;
			}
		}
		if (op == "work")
		{
			Job jobT;
			cout << "Please input the name of job: ";
			cin >> jobT.jobName;
			cout << "How many cpu cores are needed: ";
			cin >> jobT.jobCPU;
			cout << "How much RAM is needed: ";
			cin >> jobT.jobRAM;
			cout << "How much time is needed: ";
			cin >> jobT.time;
			double mark;
			double max = -1;
			int sId = -1;
			for (int i = 0; i<servers.size(); i++)
			{
				if (servers[i].remainCPU >= jobT.jobCPU && servers[i].remainRAM >= jobT.jobRAM)
				{
					mark = (double)jobT.jobCPU / (double)servers[i].remainCPU + (double)jobT.jobRAM / (double)servers[i].remainRAM;
					if (max < mark)
					{
						max = mark;
						sId = i;

					}

				}
			}
			if (sId==-1) cout << "No available server now! Please try again!" << endl;
			else
			{
				jobT.serverId = sId+ 1;
				servers[sId].remainCPU = servers[sId].remainCPU - jobT.jobCPU;
				servers[sId].remainRAM = servers[sId].remainRAM - jobT.jobRAM;
				jobs.push_back(jobT);
				cout << "working in " << servers[jobT.serverId - 1].serverName << endl;
			}		
		}
		if (op == "free")
		{
			string jobName;
			cout << "Please input the name of job: ";
			cin >> jobName;
			if (jobName == "all")
			{
				for (int i = 0; i < servers.size(); i++)
				{
					servers[i].remainCPU = servers[i].cpuCores;
					servers[i].remainRAM = servers[i].RAMSize;
				}

				jobs.clear();
			}
			else
			{
				bool isExist = false;

				for (auto it = jobs.begin(); it != jobs.end(); it++)
				{
					if (it->jobName == jobName)
					{
						int serverId = it->serverId - 1;
						servers[serverId].remainCPU = servers[serverId].remainCPU + it->jobCPU;
						servers[serverId].remainRAM = servers[serverId].remainRAM + it->jobRAM;
						jobs.erase(it);
						isExist = true;
						break;
					}
				}
				if (isExist)
				{
					cout << "freed job " << jobName << endl;
				}
				else cout << jobName << " doesn't exist!" << endl;
			}

		}
		if (op == "save")
		{
			ofstream fs(fileName, ios::out);
			if (fs.is_open())
			{
				for (int i = 0; i < servers.size() - 1; i++)
				{
					fs << servers[i].serverName << "\t" << servers[i].cpuCores << "\t" << servers[i].remainCPU << "\t" << servers[i].RAMSize << "\t" << servers[i].remainRAM << endl;

				}
				int e = servers.size() - 1;
				fs << servers[e].serverName << "\t" << servers[e].cpuCores << "\t" << servers[e].remainCPU << "\t" << servers[e].RAMSize << "\t" << servers[e].remainRAM;
			}
			fs.close();

			ofstream js(jobFName, ios::out);
			if (js.is_open())
			{
				if (jobs.size() > 1)
				{
					for (int i = 0; i < jobs.size() - 1; i++)
					{
						js << jobs[i].jobName << "\t" <<jobs[i].jobCPU << "\t" << jobs[i].jobRAM << "\t" <<  jobs[i].time << "\t" << jobs[i].serverId << endl;

					}
					int e = jobs.size() - 1;
					js << jobs[e].jobName << "\t" << jobs[e].jobCPU << "\t" << jobs[e].jobRAM << "\t" << jobs[e].time << "\t" << jobs[e].serverId;
				}
				else if (jobs.size() == 1)
				{
					int e = 0;
					js << jobs[e].jobName << "\t" << jobs[e].jobCPU << "\t" << jobs[e].jobRAM << "\t" << "\t" << jobs[e].time << "\t" << jobs[e].serverId;
				}
				
			}
			js.close();

			cout << "saved!" << endl;
		}

		if (op == "restart")
		{
			for (int i = 0; i < servers.size(); i++)
			{
				servers[i].remainCPU = servers[i].cpuCores;
				servers[i].remainRAM = servers[i].RAMSize;
			}

			jobs.clear();
			cout << "restarted!" << endl;
		}

		//default discard all unsaved status
		if (op == "exit")
		{
			//ofstream fs(fileName, ios::out);
			//if (fs.is_open())
			//{
			//	for (int i = 0; i < servers.size()-1; i++)
			//	{
			//		fs << servers[i].serverName << "\t" << servers[i].cpuCores << "\t" << servers[i].cpuCores << "\t" << servers[i].RAMSize << "\t" << servers[i].RAMSize << endl;
			//		
			//	}
			//	int e = servers.size() - 1;
			//	fs << servers[e].serverName << "\t" << servers[e].cpuCores << "\t" << servers[e].cpuCores << "\t" << servers[e].RAMSize << "\t" << servers[e].RAMSize;
			//}
			//
			//fs.close();

			//ofstream js(jobFName, ios::out);
			//if (js.is_open())
			//{
			//}
			//js.close();

			cout << "exited!" << endl;
			break;
		}


	}



	ct.EndTimer();
	system("pause");
	return 0;
}