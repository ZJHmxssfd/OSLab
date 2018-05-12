#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define Name_length 14	 //�ļ�������󳤶�
#define iNode_NUM 256		 //iNode������
#define DIR_NUM 8				 //ÿ��Ŀ¼�ļ��µ��ļ�������
#define PATH_LENGTH 100	//·���ַ�����󳤶�
#define MAX_BLOCK 1024	 //���̿�����
#define FBLK_NUM 4			 //�ļ���block�ĸ���
#define CURRENT_TIME 123 //��ǰʱ�䣬����
//���ļ���ģʽf_mode
#define RDONLY 00 //ֻ��
#define WRONLY 01 //ֻд
#define RDWR 02		//��д

//iNode
typedef struct INODE
{
	unsigned short i_mode;			 // �ļ����ͣ�0Ŀ¼��1��ͨ
	int i_size;									 //�ļ���С���ֽ�����
												 //int permission;//�ļ��Ķ���д��ִ��Ȩ��
												 /*int ctime; //�ļ���ʱ�����inode��һ�α䶯��ʱ��
												 int mtime; //�ļ���ʱ������ļ�������һ�α䶯��ʱ��
												 int atime;//�ļ���ʱ������ļ���һ�δ򿪵�ʱ�䡣*/
	int nlinks;									 //�����������ж����ļ�Ŀ¼��ָ�����inode �ж�һ�� i�ڵ��Ƿ�Ӧ�ñ��ͷ�
	int block_address[FBLK_NUM]; //�ļ�����block��λ��
	int open_num;								 //0û�б��򿪣�1�Ѿ����򿪣���ֹ��δ��ļ�
} iNode;

//�ļ�Ŀ¼��ṹ:��ǰĿ¼��һϵ��Ŀ¼����б�
typedef struct directory
{
	string file_name;			 //�ļ���
	unsigned int iNode_no; //iNode���
} dir;

//�ļ��ľ��
typedef struct OS_FILE
{
	//unsigned short f_mode;//�ļ�����ģʽ��RWλ�� ------------������-------------
	//unsigned short f_flag;
	//unsigned short f_count;//��Ӧ�ļ����ü���ֵ
	iNode *f_iNode; //ָ���ӦiNode
	long int f_pos; //��ָ��
} os_file;

////ȫ�ֱ���
extern iNode iNode_table[iNode_NUM]; //iNode table�����飬�����±��ӦiNode���
extern dir root_dir[DIR_NUM];				 //��Ŀ¼ ����ʵ��  ���µ�ÿ����Ŀ¼Ҳ��dir���͵����飬ÿһ����һ���ļ�Ŀ¼��
extern dir *current_dir;						 //����ÿ�θ���analyse_path���ص�dir���飬����ǰĿ¼��dir����

void init_iNode(iNode *blankiNode);		//iNode��ʼ������
void format_iNode(iNode *blankiNode); //iNode��ʽ������
void init_dir(dir blankdir[]);				//dir�����ʼ������

											//string path;//��¼·��

iNode *Create_File(string pathname, string cur_path, unsigned short f_type); //�����ļ� �����������ݶ�
int Delete_File(string f_name, int f_i, string path);												 //ɾ���ļ� rm filename (����ֵ���ɹ�0��ʧ��-1)
os_file *Open_File(string f_name);																					 //���ļ�
void Close_File(os_file *f);																								 //�ر��ļ�

unsigned int dirlookup(string son_name, dir *father); //���������ƣ��ҵ���iNode���
unsigned int get_empty_iNode();												//�ҵ����е�iNode,���ر�ţ������±꣩
iNode Fill_in_iNode(unsigned short f_type);						//����iNode��Ϣ
dir *analyse_Path(string path, int *i_no);						//����·�����������ҵ���ǰĿ¼/�ļ�����
int find_dir_no(string f_name);												//��current_dir�в��Ҹ��ļ���dir��Ŀ¼�������±�
void get_dir(void *dir_buf, iNode *f_iNode);

//����Ŀ¼�ļ� mkdir dirName  ����Create_File
//ɾ����ͨ�ļ� rm filename ����Delete_File
//ɾ��Ŀ¼��Ŀ¼�������ļ� rmdir dirName  ����os_rmdir()

//////////////�⼸�������ڵ�ǰĿ¼�µĲ��������Խ����Ǳߵù�ͨ��///////////////
int os_rm(string f_name, string path);					 //ɾ���ļ�
bool os_rmdir(string dir_name, string path);		 //ɾ��Ŀ¼��Ŀ¼�������ļ�
vector<string> os_ls();													 //�г�Ŀ¼�������ļ�
bool os_cd(string &currentpath, string newpath); // �л�Ŀ¼  �����л� or ����ȫ·���Զ��л�
