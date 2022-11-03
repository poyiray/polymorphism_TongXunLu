#include<iostream>
#include<string>
using namespace std;

#include "workerManager.h"
//#include "worker.h"
//#include "employee.h"
//#include "Manager.h"
//#include "boss.h"

int main() {

	WorkerManager wm;
	int choice;

	while (true)
	{
		//展示菜单
		wm.Show_Menu();
		cout << "输入你的选择: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			system("pause");
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		}
		system("cls");
	}

	system("pause");
	return 0;
}