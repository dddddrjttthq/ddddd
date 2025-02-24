#include"teacher.h"
#include<vector>

//默认构造
Teacher::Teacher()
{
}

//有参构造 (职工编号，姓名，密码)
Teacher::Teacher(int empId, string name, string pwd)
{
	this->mTid = empId;
	this->mName = name;
	this->mPwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->mName << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//查看所有预约
void Teacher::showallapply()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：" << of.m_orderData[i]["date"]<<" ";
		cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")<<" ";
		cout << "学号：" << of.m_orderData[i]["stuId"] << " ";
		cout << "姓名：" << of.m_orderData[i]["stuName"] << " ";
		cout << "机房：" << of.m_orderData[i]["roomId"] << " ";
		string status = "状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核为通过";
		}
		else
		{
			status += "预约取消";
		}
		cout << status << endl;
	}
}

//审核预约
void Teacher::vaildapply()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		return;
	}
	cout << "待审核的记录，请选择你要审核的记录" << endl;
	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index+ 1 << "、";
			cout << "预约日期：" << of.m_orderData[i]["date"];
			cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "机房：" << of.m_orderData[i]["roomId"];
			cout << "状态" << of.m_orderData[i]["status"];
			string status = "状态：审核中";
			cout << status << endl;
			index++;
		}
	}
	cout << "请输入你想审核的记录，0表示返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			break;
		}
		else if(select>0&&select<v.size())
		{
			cout << "请输入你的选择" << endl;
			cout << "1.通过" << endl;
			cout << "2.不通过" << endl;
			int se;
			cin >> se;
			if (se == 1)
			{
				of.m_orderData[v[select - 1]]["status"] = "2";
			}
			else if (se == 2)
			{
				of.m_orderData[v[select - 1]]["status"] = "-1";
			}
			of.updateorder();
			//this->vaildapply();
			cout << "审核完毕" << endl;
			break;
		}

	}
}