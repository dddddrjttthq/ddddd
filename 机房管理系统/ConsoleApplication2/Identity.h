#pragma once
#include<iostream>
#include<string>
using namespace std;
class Ideentify
{
public:
	virtual void operMenu() = 0;
	//不同身份的操作菜单虚函数

public:
	string mName;//用户名
	string mPwd;//密码

};
