#include "workerManager.h"
#include "employee.h"
#include "boss.h"
#include "Manager.h"

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		m_EmpNum = 0;
		m_EmpArray = NULL;
		m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		m_EmpNum = 0;
		m_EmpArray = NULL;
		m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = get_EmpNum();
	m_EmpNum = num;

	m_EmpArray = new Worker*[m_EmpNum];
	init_Emp();
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "拜拜了您嘞!" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加的职工人数: " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		int newSize = m_EmpNum + addNum;

		Worker ** newSpace = new Worker*[newSize];
		if (m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第 " << i + 1 << " 个新职工的编号: " << endl;
			cin >> id;			

			cout << "请输入第 " << i + 1 << " 个新职工的名字: " << endl;
			cin >> name;

			cout << "请输入第 " << i + 1 << " 个新职工的岗位: " << endl;
			cout << "1. 职工" << endl;
			cout << "2. 经理" << endl;
			cout << "3. 老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			newSpace[m_EmpNum + i] = worker;
		}
		delete[] m_EmpArray;
		m_EmpArray = newSpace;
		m_EmpNum = newSize;
		cout << "成功添加了" << addNum << "员工" << endl;

		Save();
	}
	else
	{
		cout << "输入有误" << endl;
	}
	m_FileIsEmpty = false;
	system("pause");
}

void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < m_EmpNum; i++)
	{
		ofs << m_EmpArray[i]->m_Id << " "
			<< m_EmpArray[i]->m_name << " "
			<< m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;

	// 如果读取成功 返回1，失败则 返回 0
	while (ifs >> id && ifs >> name && ifs >> dId) 
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;

		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

void WorkerManager::Show_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件记录不能为空!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			m_EmpArray[i]->showInfo();
		}
	}
}

void WorkerManager::Del_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不能为空!" << endl;
	}
	else
	{
		Show_Emp();
		int id;
		cout << endl;
		cout << "输入你要删除人员的id" << endl;
		cin >> id;
		int result = IsExist(id);
		if (result != -1)
		{
			for (int i = result; i < m_EmpNum - 1; i++)
			{
				m_EmpArray[i] = m_EmpArray[i + 1];
			}
			m_EmpNum--;
			Save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败" << endl;
		}
	}

	system("pause");
}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < m_EmpNum; i++)
	{
		if (m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Mod_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不能为空!" << endl;
	}
	else
	{
		Show_Emp();
		int Emp_id;
		cout << "输入需要修改员工的id" << endl;
		cin >> Emp_id;
		int result = IsExist(Emp_id);
		if (result != -1)
		{
			int choice;
			cout << "输入 1 修改ID" << endl;
			cout << "输入 2 修改名称" << endl;
			cout << "输入 3 修改职位" << endl << endl;
			cin >> choice;

			Worker * worker = NULL;
			int id;
			string name;
			int dId;

			switch (choice)
			{
			case 1:
				cout << "请输入新id: " << endl;
				cin >> id;
				m_EmpArray[result]->m_Id = id;
				break;
			case 2:
				cout << "请输入新名称: " << endl;
				cin >> name;
				m_EmpArray[result]->m_name = name;
				break;
			case 3:
			{
				cout << "请输入新职位: " << endl;
				cin >> dId;
				id = m_EmpArray[result]->m_Id;
				name = m_EmpArray[result]->m_name;
				if (dId == 1)
				{
					worker = new Employee(id, name, dId);
				}
				else if (dId == 2)
				{
					worker = new Manager(id, name, dId);
				}
				else if (dId == 3)
				{
					worker = new Boss(id, name, dId);
				}
				delete m_EmpArray[result];
				m_EmpArray[result] = worker;
				delete worker;
			}
				break;
			default:
				cout << "输入错误" << endl;
				break;
			}
			Save();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "找不到此人" << endl;
		}
	}
	system("pause");
}

void WorkerManager::Sort_Emp()
{
	int index = 0;
	for (int i = 0; i < m_EmpNum; i++)
	{
		index = i;
		for (int j = i; j < m_EmpNum; j++)
		{
			if (m_EmpArray[index]->m_Id > m_EmpArray[j]->m_Id)
			{
				index = j;
			}
		}

		Worker * temp = m_EmpArray[i];
		m_EmpArray[i] = m_EmpArray[index];
		m_EmpArray[index] = temp;
	}

	cout << "排序完成" << endl;
	Save();
	Show_Emp();
	system("pause");
}

void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}


	system("pause");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		this->m_EmpNum = 0;
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
	}
}