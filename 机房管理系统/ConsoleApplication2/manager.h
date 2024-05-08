#pragma once
#include<iostream>
#include<vector>
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
using namespace std;

class Maneger :public Ideentify
{
public:
	//默认构造
	Maneger();

	//有参构造  管理员姓名，密码
	Maneger(string name, string pwd);

	//选择菜单
	virtual void operMenu();

	//添加账号  
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();
	void initVector();

	//去重函数
	bool checkRepeat(int id, int type);
public:
	vector<Student>vStu;
	vector<Teacher>vTea;
	vector< cpmputerRoom>Vcom;//机房容器
};
