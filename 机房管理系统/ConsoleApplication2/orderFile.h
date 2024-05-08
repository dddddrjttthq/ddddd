#pragma once
#include<iostream>
#include<map>
#include"globalFile.h"
#include<fstream>
#include<algorithm>
using namespace std;
class orderFile
{
public:
	orderFile();
	
	void updateorder();
	//更新容器
	//记录的容器  key --- 记录的条数  value --- 具体记录的键值对信息
	map<int, map<string, string>> m_orderData;
	//预约记录条数
	int m_Size;
};