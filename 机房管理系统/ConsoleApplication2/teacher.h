#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Identity.h"
#include<fstream>
#include"orderFile.h"
using namespace std;
class Teacher :public Ideentify
{
public:
	//默认构造函数
	Teacher();
	//有参构造
	Teacher(int empId, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//查看所有预约
	void showallapply();

	//审核预约
	void vaildapply();

	int mTid;//教师编号
};