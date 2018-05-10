#pragma once

#include<list>
#include<vector>
#include"PCB.h"

using namespace std;


#define MAXMEMORYSIZE 10240//��������ڴ�(Bytes)  10MB
#define MAXPAGESIZE 32//���ҳ��С(Bytes) 
#define MAXSWAPFILESIZE 20480 //����ҳ�ļ���С 20MB

#define MAXPROC 64 //�������� readlist��waitlist���ܽ�����

#define MAXPROCMEM 160 // �����������ռ���ڴ� 160Bytes


struct PCB_Show
{
	unsigned int PID; //����PID
	string Name; // ��������
	int Size; //����ռ���ڴ���С
	procstate State;  //����״̬
	unsigned int Prio;//���ȼ�
	int ServiceTime;//���̷���ʱ��
	int RunTime;//�Ѿ�ռ��CPUʱ��
};




enum  schedulestrategies { FCFS, SJF, RR, PRIO } ; // ��������:	�����ȷ���	���ʣ��ʱ������	ʱ��Ƭ��ת	���ȼ�����


class PM
{
public:
	PM(int t = 0, schedulestrategies s = RR, int tp = 2) // ���캯�� Ĭ�ϵ�ǰʱ��0��RR�����㷨��ʱ��ƬΪ2��
	{
		currenttime = t;
		strategy = s;
		currentnumproc = 0;
		currentmemory = 0;
		timepiece = tp;
	}
	list<PCB> readylist; //���м��������� ��ռ���ڴ�Ķ���
	list<PCB> waitlist; // �ȴ����У��ڴ��������������ڴ治����ԭ����޷������ڴ�Ľ���

	unsigned int createPID(); // ά��һ��PID�أ�����PID
	

	void addproc(string path); // ��ӽ���
	void killproc(unsigned int PID); // ǿ�ƽ�������
	void scheduleproc(); // ���Ƚ���
	vector<PCB_Show> showreadylist();
	vector<PCB_Show> showwaitlist();
private:
	int currenttime; //��ǰʱ��
	int currentnumproc; // ��ǰ������ ���� readylist �� waitlist
	int currentmemory; // ��ǰ���н�����ռ���ڴ��С
	schedulestrategies strategy; // ���Ȳ���
	int timepiece; // ʱ��Ƭ��С
};


unsigned int PM::createPID()
{


}


void PM::addproc(string path)
{
	if (currentnumproc >= MAXPROC)
	{
		// �޷��������� ���log�� �����û�
		return;
	}

	os_file* f = Open_File(path);
	if (f) // �ļ�����
	{
		int buf[2];
		if (os_fread(buf, sizeof(buf), f)) // ��ȡ�ɹ� ��ȡǰ8���ֽ�
		{
			int memsize = buf[0];
			int servicetime = buf[1];
			if (memsize == 0 || servicetime == 0)
			{
				//�����ڴ�Ϊ0 ���� ����ʱ��Ϊ0
				// log �������̲�������
				return;
			}
			vector<int> mem = osMalloc(memsize);
			unsigned int PID = createPID();

			int pos = path.rfind('/');
			string name = path.substr(pos + 1);

			PCB p(PID, path, name, f, mem, currenttime, servicetime);
			if (mem.size == 0)
			{
				p.State = WAITING;
				waitlist.push_back(p);
			}
			else
			{
				p.State = READY;
				readylist.push_back(p);
			}
			

		}
	}
	else
	{
		// �ļ�������
	}
}

void PM::killproc(unsigned int PID)
{

}


/*
���̵��Ⱥ���
ˢ��readylist�� ������״̬ΪFINISH�Ľ����Ƴ����ͷ������Դ��PID���ڴ棬���ļ��ȣ����������Դ�����ʣ���д��log��
ˢ��readylist��waitlist����״̬ΪDIED�Ľ����Ƴ����ͷ�PID�����ļ���readylist�еĻ����ͷ��ڴ棻д��log��
����waitlist��Ϊwaitlist�п��еĽ��̣��ڴ�����룩�����ڴ棬�Ƴ�waitlist������readylistĩβ����״̬��Ϊready��
���ݵ��Ȳ��Դ�readylist��ѡȡһ�����ʵĽ��̷��� readylist ͷ������ʾ��ǰʱ��Ƭ���и�ѡ�г���
ˢ��readlist
*/
void PM::scheduleproc()
{

}


// ��vector<PCB_Show>����readylist�е�PCB
vector<PCB_Show> PM::showreadylist()
{
	vector<PCB_Show> pr;
	for (list<PCB>::iterator i = readylist.begin(); i != readylist.end(); i++)
	{
		PCB_Show p;
		p.PID = i->PID;
		p.Name = i->Name;
		p.Size = i->Size;
		p.State = i->State;
		p.Prio = i->Prio;
		p.ServiceTime = i->ServiceTime;
		p.RunTime = i->RunTime;
		pr.push_back(p);
	}

	return pr;
}


// ��vector<PCB_Show>����waitlist�е�PCB
vector<PCB_Show> PM::showwaitlist()
{
	vector<PCB_Show> pw;
	for (list<PCB>::iterator i = waitlist.begin(); i != waitlist.end(); i++)
	{
		PCB_Show p;
		p.PID = i->PID;
		p.Name = i->Name;
		p.Size = i->Size;
		p.State = i->State;
		p.Prio = i->Prio;
		p.ServiceTime = i->ServiceTime;
		p.RunTime = i->RunTime;
		pw.push_back(p);
	}

	return pw;
}
