#pragma once
#include<iostream>
#include"worker.h"
#include <fstream>
#define  FILENAME "empFile.txt"
using namespace std;
class workerManager {
public:
	workerManager();
	void Show_Menu();
	void Exit();
	//增加职工
	void Add_Emp();
	//保存文件
	void save();
	//统计人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();

	//删除职工
	void Del_Emp();
	~workerManager();
	//显示职工
	void Show_Emp();
	//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	int m_NUM;

	//员工数组的指针
	work ** m_EmpArray;
	//标志文件是否为空
	bool m_FileIsEmpty;
	 
};