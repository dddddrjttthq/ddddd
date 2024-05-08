#include "manager.h"
#include"fstream"
#include"student.h"
#include"teacher.h"
#include"globalFile.h"
#include<algorithm>
#include"computerRoom.h"

void printstudent(Student& s)
{
	cout << "学号：" << s.mID << "姓名：" << s.mName << "密码：" << s.mPwd << endl;
}
void printteacher(Teacher& t)
{
	cout << "职工号： " << t.mTid << " 姓名： " << t.mName << " 密码：" << t.mPwd<< endl;
}
//默认构造
Maneger::Maneger()
{
}

//有参构造
Maneger::Maneger(string name, string pwd)
{
	this->mName = name;
	this->mPwd = pwd;
	this->initVector();
}

//选择菜单
void Maneger::operMenu()
{
	cout << "欢迎管理员：" << this->mName << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//添加账号  
void Maneger::addPerson()
{
	cout << "请输入添加的账号类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	string fileName;
	string tip;
	ofstream ofs;//写入文件流
	string errorTip;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号";
		errorTip = "职工号重复，请重新输入";
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)//有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名： " << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	this->initVector();
}

//查看账号
void Maneger::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下 " << endl;
		for_each(vStu.begin(), vStu.end(), printstudent);
	}
	else
	{
		cout << "所有老师信息如下" << endl;
		for_each(vTea.begin(), vTea.end(), printteacher);
	}

}

//查看机房信息
void Maneger::showComputer()
{
	cout << "机房信息如下" << endl;
	for (vector< cpmputerRoom>::iterator it = Vcom.begin(); it != Vcom.end(); it++)
	{
		cout << "机房编号" << it->mcomid << "机房最大的容量" << it->mmax << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Maneger::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
		/*More Actions打开方式解释
		ios::in为读文件而打开文件
		ios::out为写文件而打开文件
		ios::ate初始位置：文件尾
		ios::app追加方式写文件
		ios::trunc如果文件存在先删除，再创建
		ios::binary二进制方式
		*/

	ofs.close();
	cout << "预约清空成功" << endl;
	system("pause");
	system("cls");
}

void Maneger::initVector()
{
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	vStu.clear();
	vTea.clear();

	Student s;
	while (ifs >> s.mID && ifs >> s.mName && ifs >> s.mPwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();
	//读取老师的文件信息
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.mTid && ifs >> t.mName &&ifs>>t.mPwd)
	{
		vTea.push_back(t);
	}
	cout << "当前教师的数量为：" << endl;
	ifs.close();
	ifs.open(COMPUTER_FILE, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	cpmputerRoom c;
	while (ifs >> c.mcomid && ifs >> c.mmax)
	{
		Vcom.push_back(c);
	}
	cout << "机房的数量" << Vcom.size() << endl;
	ifs.close();
}	
//去重函数
bool Maneger::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->mID)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->mTid)
			{
				return true;
			}
		}
	}
	return false;
}