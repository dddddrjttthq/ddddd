#include"boss.h"
boss::boss(int id, string name, int iID) {
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = iID;
}
void boss::showin() 
{
	cout << "职工编号： " << this->m_id
		<< " \t职工姓名： " << this->m_name
		<< " \t岗位：" << this->Getdepname()
		<< " \t岗位职责：管理公司所有事务" << endl;
 }
//显示信息
string boss::Getdepname()
{
	return string("老板");
}
