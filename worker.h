#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
	virtual void showInfo() = 0;

	int m_Id;
	string m_name;
	int m_DeptId;
};