#include "Manager.h"

Manager::Manager(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Manager::showInfo()
{
	cout << "职工编号: " << m_Id
		<< "\t职工姓名: " << m_name
		<< "\t岗位: " << "经理"
		<< "\t岗位指责: 分配任务给员工" << endl;
}