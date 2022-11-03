#include "workerManager.h"
#include "employee.h"
#include "boss.h"
#include "Manager.h"

WorkerManager::WorkerManager()
{
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
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
		cout << "�ļ�Ϊ��" << endl;
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
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "�ݰ�������!" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "��������ӵ�ְ������: " << endl;

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
			cout << "������� " << i + 1 << " ����ְ���ı��: " << endl;
			cin >> id;			

			cout << "������� " << i + 1 << " ����ְ��������: " << endl;
			cin >> name;

			cout << "������� " << i + 1 << " ����ְ���ĸ�λ: " << endl;
			cout << "1. ְ��" << endl;
			cout << "2. ����" << endl;
			cout << "3. �ϰ�" << endl;
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
		cout << "�ɹ������" << addNum << "Ա��" << endl;

		Save();
	}
	else
	{
		cout << "��������" << endl;
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

	// �����ȡ�ɹ� ����1��ʧ���� ���� 0
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
		cout << "�ļ���¼����Ϊ��!" << endl;
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
		cout << "�ļ�����Ϊ��!" << endl;
	}
	else
	{
		Show_Emp();
		int id;
		cout << endl;
		cout << "������Ҫɾ����Ա��id" << endl;
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
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ��" << endl;
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
		cout << "�ļ�����Ϊ��!" << endl;
	}
	else
	{
		Show_Emp();
		int Emp_id;
		cout << "������Ҫ�޸�Ա����id" << endl;
		cin >> Emp_id;
		int result = IsExist(Emp_id);
		if (result != -1)
		{
			int choice;
			cout << "���� 1 �޸�ID" << endl;
			cout << "���� 2 �޸�����" << endl;
			cout << "���� 3 �޸�ְλ" << endl << endl;
			cin >> choice;

			Worker * worker = NULL;
			int id;
			string name;
			int dId;

			switch (choice)
			{
			case 1:
				cout << "��������id: " << endl;
				cin >> id;
				m_EmpArray[result]->m_Id = id;
				break;
			case 2:
				cout << "������������: " << endl;
				cin >> name;
				m_EmpArray[result]->m_name = name;
				break;
			case 3:
			{
				cout << "��������ְλ: " << endl;
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
				cout << "�������" << endl;
				break;
			}
			Save();
			cout << "�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "�Ҳ�������" << endl;
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

	cout << "�������" << endl;
	Save();
	Show_Emp();
	system("pause");
}

void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ���" << endl;
	}

	system("pause");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //��ְ���Ų���
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) //����������
		{
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_Id
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
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