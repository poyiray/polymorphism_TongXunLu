#include "Manager.h"

Manager::Manager(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Manager::showInfo()
{
	cout << "ְ�����: " << m_Id
		<< "\tְ������: " << m_name
		<< "\t��λ: " << "����"
		<< "\t��λָ��: ���������Ա��" << endl;
}