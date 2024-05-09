#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
class boss :public work
{
public :
	boss(int id, string name, int iID);
	//显示信息
	virtual void showin();
	//显示岗位
	virtual string Getdepname() ;
};