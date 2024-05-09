#include"manager.h"
manager::manager(int id, string name, int dID)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = dID;
}
void manager::showin()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名" << this->m_name
		<< "\t 岗位：" << this->Getdepname()
		<< "\t 岗位职责：完成经理交代的任务" << endl;
}

string manager::Getdepname()
{
	return string("经理");
}