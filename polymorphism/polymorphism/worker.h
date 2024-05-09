#pragma once
#include<iostream>
#include<string>
using namespace std;
//创建职工抽象类
class work
{
public:
	//显示信息
	virtual void showin()=0;
	//显示岗位
	virtual string Getdepname() = 0;

	//编号
	int m_id;
	//姓名
	string m_name;
	//部门编号
	int m_deptid;
};
//创建普通员工

class employee:public work
{
public:
	employee(int id, string name, int dID);
	virtual void showin();
	virtual string Getdepname();
};