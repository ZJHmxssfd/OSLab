#pragma once
#include<vector>
using namespace std;

struct os_file
{

};

os_file* Open_File(string path)
{

}

int os_fread(void* buf, int size, os_file* fp)
{

}

vector<int> osMalloc(int memSize)
{

}


enum procstate { NEW, READY, RUNNING, WAITING, FINISH, DIED}; // ����״̬���½� ���� ���� �ȴ� ��� ����

class PCB
{
public:
	PCB();
	PCB(
		unsigned int PID, string Path, string Name, os_file* f,
		vector<int> Mem, int ArriveTime, int ServiceTime);
	~PCB();

	unsigned int PID; //����PID
	string Path; //���������ļ�·��
	string Name; // ��������
	os_file* procftr; // �����ļ�ָ��

	vector<int> Mem; //�����ڴ��
	int Size; //����ռ���ڴ���С
	procstate State;  //����״̬
	unsigned int Prio;//���ȼ�

	int ArrivalTime; //���̴���ʱ��  
	int StartTime;  //���̿�ʼ����ʱ��  
	int ServiceTime;//���̷���ʱ��
	int RunTime;//�Ѿ�ռ��CPUʱ��
	int NeedTime;//��Ҫռ��CPUʱ��
	int FinishTime;//���̽���ʱ��

	bool operator == (const PCB &a)const
	{
		return PID == a.PID ? true : false;
	}

	bool operator <(const PCB &a)const
	{
		return PID < a.PID;
	}

private:
};



PCB::PCB(){} // �չ��캯��

PCB::PCB(
	unsigned int PID, string Path, string Name, os_file* f,
	vector<int> Mem, int ArrivalTime, int ServiceTime
	)
{
	this->PID = PID;
	this->Path = Path;
	this->Name = Name;
	this->procftr = f;

	this->Mem = Mem;
	this->Size = Mem.size();
	this->State = NEW;
	this->Prio = Prio;
	
	this->ArrivalTime = ArrivalTime;
	this->StartTime = -1; //-1 ��ʾ���̴�δ��ʼ����
	this->ServiceTime = ServiceTime;
	this->RunTime = 0;
	this->NeedTime = ServiceTime;
	this->FinishTime = -1; //-1 ��ʾ����δ���
}

PCB::~PCB(){}


