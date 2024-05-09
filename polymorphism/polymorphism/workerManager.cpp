#include"workerManager.h"
#include"manager.h"
#include"boss.h"
#include<iostream>
using namespace std;

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl; //测试输出
		this->m_NUM = 0;  //初始化人数
		this->m_FileIsEmpty = true; //初始化文件为空标志
		this->m_EmpArray = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}
	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->m_NUM = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//文件存在，并且有记录
	int num = this->get_EmpNum();
	cout << "职工个数为：" << num << endl;  //测试代码
	this->m_NUM = num;  //更新成员属性 

	//根据职工数创建数组
	this->m_EmpArray = new work * [this->m_NUM];
	//初始化职工
	init_Emp();

	//测试代码
	for (int i = 0; i < m_NUM; i++)
	{
		cout << "职工号： " << this->m_EmpArray[i]->m_id
			<< " 职工姓名： " << this->m_EmpArray[i]->m_name
			<< " 部门编号： " << this->m_EmpArray[i]->m_deptid << endl;
	}
}

workerManager::~workerManager()
{

}
void workerManager::Exit()
{
	exit(0);
}
void workerManager:: Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//增加职工
void workerManager::Add_Emp()
{
	cout << "请输入增加职工数量：" << endl;

	int addnum = 0;
	cin >> addnum;
	if (addnum > 0)
	{ 
		 //计算新空间大
		int newsize = this->m_NUM + addnum;

		//开辟
		work** newspace = new work * [newsize];
		//将原来空间的放入新空间内
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_NUM; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//输入新数据
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int select;
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的名字" << endl;
			cin >> name;
			cout << "选择该职工的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> select;
			work* w1 = NULL;
			switch (select)
			{
			case 1: //普通员工
				w1 = new employee(id, name, 1);
				break;
			case 2: //经理
				w1 = new manager(id, name, 2);
				break;
			case 3:  //老板
				w1 = new boss(id, name, 3);
				break;
			default:
				break;
			}
			newspace[this->m_NUM + i] = w1;
		}
		//释放原有的空间
		delete[] this->m_EmpArray;
		//更改空间的指向
		this->m_EmpArray = newspace;
		this->m_NUM = newsize;
		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		cout << "添加成功" << addnum << "名新职工" << endl;
		
		this->save();
	}
	else
	{
		cout << "输入错误" << endl;

	}
	system("pause");
	system("cls");
}//保存文件
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);


	for (int i = 0; i < this->m_NUM; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}

	ofs.close();
}
int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}
void workerManager::init_Emp()
{

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		work* worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)  // 1普通员工
		{
			worker = new employee(id, name, dId);
		}
		else if (dId == 2) //2经理
		{
			worker = new manager(id, name, dId);
		}
		else //总裁
		{
			worker = new boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
}
void workerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空！" << endl;
	}
	else {
		for (int i = 0; i < m_NUM; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showin();
		}
	}
}
void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照编号删除
		cout << "请输入你想删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_NUM - 1; ++i)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_NUM--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，没有发现该职工" << endl;


		}

	}

}
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_NUM; ++i)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改的职工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newid = 0;
			string newname = " ";
			int dselect = 0;
			cout << "查找到：" << id << "好职工，请输入新职工号：" << endl;
			cin >> newid;
			cout << "请输入新名字：" << endl;
			cin >> newname;
			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;
			work* worker = NULL;
			switch (dselect)
			{
			case1:
				worker = new employee(newid, newname, dselect);
				break;
			case2:
				worker = new manager(newid, newname, dselect);
				break;
			case 3:
				worker = new boss(newid, newname, dselect);
				break;
			default:
				break;
			}
			//更新数据
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			this->save();


		}
		else
		{
			cout << "修改失败，无此人" << endl;
		}
	}

}
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件吧存在或者记录为空" << endl;

	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id = 0;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功，该职工信息如下" << endl;
				this->m_EmpArray[ret]->showin();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入你要查找的姓名：" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_NUM; ++i)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功，职工编号为："
						<< m_EmpArray[i]->m_id
						<< " 号的如下信息为：" << endl;
					this->m_EmpArray[i]->showin();
					flag = true;
				}
			}
		}

	}
}
