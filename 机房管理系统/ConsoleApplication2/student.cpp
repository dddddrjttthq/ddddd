#include"student.h"
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"

//默认构造
Student::Student()
{

}
//有参构造
Student::Student(int id, string name, string pwd)
{
	this->mID = id;
	this->mName = name;
	this->mPwd = pwd;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "读取文件失败" << endl;
		return;
	}
	cpmputerRoom c;
	while (ifs >> c.mcomid && ifs >> c.mmax)
	{
		vCom.push_back(c);
	}
	ifs.close();

}

//登录界面
void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->mName << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::apply()
{
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int data = 0;
	int interval = 0;
	int room = 0;
	while (true)
	{
		cin >> data;
		if (data >= 1 && data <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "选择有误，请重新输入" << endl;
	}
	cout << "请选择机房：" << endl;
	cout << "1号机房容量：" << vCom[0].mmax << endl;
	cout << "2号机房容量：" << vCom[1].mmax << endl;
	cout << "3号机房容量：" << vCom[2].mmax << endl;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功,正在审核" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);//追加方式
	ofs << "date:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->mID << " ";
	ofs << "stuName:" << this->mName << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();
}

//查看我的预约
void Student::showapply()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "当前无预约" << endl;
		system("pause");
		system("cls");
		return;
	}
	//遍历所有的id
	for (int i = 0; i < of.m_Size; i++)
	{/*
atoi 是 C++ 标准库中的一个函数，它用于将字符串转换为整型（int）。
它接受一个指向 C 字符串的指针（即以空字符 \\0 结尾的字符数组）作为参数，并返回转换后的整数值。
.c_str() 是 std::string 类的一个成员函数，它返回一个指向与 std::string 内容相同的以空字符终止的字符数组的指针。*/
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->mID)
		{
			cout << "预约日期：" << of.m_orderData[i]["date"];
			cout << "时间段：" << (of.m_orderData[i]["interval"]=="1"?"上午":"下午");
			cout << "机房：" << of.m_orderData[i]["roomId"];
			cout << "状态" << of.m_orderData[i]["status"];
			string status = "状态：";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "审核通过";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else
			{
				status += "预约取消";
			}
			cout << status << endl;
		}
		system("pause");
		system("cls");
	}


}

//查看所有预约
void Student::showallapply()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：" << of.m_orderData[i]["date"];
		cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "机房：" << of.m_orderData[i]["roomId"];
		cout << "状态" << of.m_orderData[i]["status"];
		string status = "状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "审核通过";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else
		{
			status += "预约取消";
		}
		cout << status << endl;
	}
}

//取消预约
void Student::cancelapply()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		return;
	}
	cout << "审核中或者成功的预约可以取消，请输入去选的记录" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->mID)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);//存放预约成功和审核中的的数据记录
				cout << i + 1 << "、";
				cout << "预约日期：" << of.m_orderData[i]["date"];
				cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "机房：" << of.m_orderData[i]["roomId"];
				cout << "状态" << of.m_orderData[i]["status"];
				string status = "状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "审核通过";
				}
				cout << status << endl;
			}
		}
	}
	cout << "输入你想删除的记录，0表示返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			break;
		}
		else
		{
			cout << v[select - 1] << endl;//索引值
			of.m_orderData[select - 1]["status"] == "0";
			of.updateorder();
			cout << "已取消预约" << endl;
			break;
		}
	}
	cout << "输入有误，请重新输入" << endl;
}