#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	m_Id = id;
	m_DeptId = dId;
	m_name = name;
}

void Boss::showInfo()
{
	cout << "ְ�����: " << m_Id
		<< "\tְ������: " << m_name
		<< "\t��λ: " << "�ϰ�"
		<< "\t��λָ��: ��龭��Ĺ���" << endl;
}