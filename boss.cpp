#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Boss::showInfo()
{
	cout << "职工编号: " << m_Id
		<< "\t职工姓名: " << m_name
		<< "\t岗位: " << "老板"
		<< "\t岗位指责: 检查经理的工作" << endl;
}