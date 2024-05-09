#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
class manager :public work
{
public:
	manager(int id, string name, int dID);
	//显示信息
	virtual void showin();
	//显示岗位
	virtual string Getdepname();

};