#pragma once
#include<iostream>
#include<string>
using namespace std;

#include "worker.h"

class Manager : public Worker
{
public:

	Manager(int id, string name, int dId);

	void showInfo();
};