#include"workerManager.h"
#include "worker.h"
#include "manager.h"
#include "boss.h"
void text();
int main()
{
	workerManager wm;
	int a;
	while (1) 
	{
		wm.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> a;
		switch (a)
		{
		case 0: //退出系统
			wm.Exit();
			break;
		case 1: //添加职工
			wm.Add_Emp();
			break;
		case 2: //显示职工
			wm.Show_Emp();
			break;
		case 3: //删除职工
			wm.Del_Emp();
			break;
		case 4: //修改职工
			wm.Mod_Emp();
			break;
		case 5: //查找职工
			break;
		case 6: //排序职工
			break;
		case 7: //清空文件
			break;
		default:
			system("cls");
			break;
		}

	}
	return 0;

}

//void text()
//{
//	work* w1 = NULL;
//	w1 = new employee(1, "zs", 1);
//	w1->showin();
//	delete w1;
//}