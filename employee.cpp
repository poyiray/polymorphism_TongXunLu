#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Employee::showInfo()
{
	cout << "ְ�����: " << m_Id
		<< "\tְ������: " << m_name
		<< "\t��λ: " << "Ա��"
		<< "\t��λָ��: ��ɾ�����������" << endl;
}