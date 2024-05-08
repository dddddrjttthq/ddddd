#pragma once
#include"Identity.h"
#include<vector>
#include"computerRoom.h"
class Student :public Ideentify
{
public:
	//默认构造
	Student();
	//有参构造
	Student(int id, string name, string pwd);

	//登录界面
	virtual void operMenu();

	//申请预约
	void apply();

	//查看我的预约
	void showapply();

	//查看所有预约
	void showallapply();

	//取消预约
	void cancelapply();

	//学生学号
	int mID;
  //机房容器    
	 vector<cpmputerRoom> vCom;
};