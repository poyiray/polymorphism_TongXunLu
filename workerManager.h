#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#define FILENAME "empFile.txt"

#include "worker.h"

class WorkerManager
{
public:

	WorkerManager();

	void Show_Menu();

	void exitSystem();

	int m_EmpNum;

	Worker ** m_EmpArray;

	void Add_Emp();

	void Save();

	bool m_FileIsEmpty;

	int get_EmpNum();

	void init_Emp();

	void Show_Emp();

	void Del_Emp();

	int IsExist(int id);

	void Mod_Emp();

	void Sort_Emp();

	void Clean_File();

	void Find_Emp();

	~WorkerManager();
};
