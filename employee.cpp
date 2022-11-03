#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Employee::showInfo()
{
	cout << "职工编号: " << m_Id
		<< "\t职工姓名: " << m_name
		<< "\t岗位: " << "员工"
		<< "\t岗位指责: 完成经理分配的任务" << endl;
}