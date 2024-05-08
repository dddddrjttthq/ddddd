// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "globalFile.h"
#include <iostream>
#include<fstream>
#include<string>
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"Identity.h"
using namespace std;
//教师菜单
void teacherMenu(Ideentify*& teacher)
{//这里运用多态，先是将父类指针指向子类，调用子类的虚函数
	while (1)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;//这里将类型转换为子类指针，来调用子类的成员函数
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			tea->showallapply();
		}
		else if (select == 2)
		{
			tea->vaildapply();
		}
		else
		{
			delete tea;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//学生菜单
void studentMenu(Ideentify*& student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;

		if (select == 1) //申请预约
		{
			stu->apply();
		}
		else if (select == 2) //查看自身预约
		{
			stu->showapply();
		}
		else if (select == 3) //查看所有预约
		{
			stu->showallapply();
		}
		else if (select == 4) //取消预约
		{
			stu->cancelapply();
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void managerMenu(Ideentify* &manager)//管理员菜单
{
	while (true)
	{
		manager->operMenu();
		//将父类指针转为子类指针，调用其他接口
		Maneger* man = (Maneger*)manager;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//登录功能
void LoginIn(string fileName, int type)
{
	Ideentify* person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName,ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if(type==2)
	{
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}
	cout << "请输入用户名" << endl;
	cin >> name;

	cout << "请输入密码" << endl;
	cin >> pwd;

	if (type == 1)
	{
		int fId;
		string mname;
		string mpwd;
		while (ifs >> fId && ifs >> mname &&ifs >> mpwd)
		{
			if (id == fId && name == mname && pwd == mpwd)
			{
				cout << "学生验证登录成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
			}
		}
	}
	else if (type == 2)
	{
		//教师登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			cout << "fid" << fId << endl;
			cout << "fName" << fName << endl;

			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;
		cout << "开始读取管理员信息" << endl;
		while (ifs >> fName && ifs >> fPwd)
		{
			cout << "读取到管理员信息：" << fName << " " << fPwd << endl;
			if (name == fName && pwd == fPwd)
			{
				cout << "验证登录成功!" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Maneger(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "登录验证失败" << endl;
	ifs.close();
	return;
}
void Exit()
{
	cout << "欢迎下一次使用" << endl;
	exit(0);
}
int main()
{

	int select = 0;

	while (true)
	{

		cout << "======================  欢迎来到drj播客机房预约系统  =====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		cin >> select; //接受用户选择

		switch (select)
		{
		case 1:  //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:  //退出系统
			Exit();
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}

