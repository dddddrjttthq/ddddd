#include"orderFile.h"
orderFile::orderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;      //日期
	string interval;  //时间段
	string stuId;     //学生编号
	string stuName;   //学生姓名
	string roomId;    //机房编号
	string status;    //预约状态
	this->m_Size = 0;
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		string key;
		string value;
		map<string, string> m;
		int pos = date.find(":");
		if (pos == -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
}
void orderFile::updateorder()
{
	if (this->m_Size == 0)
	{
		return;
	}
	//如果没有预约记录就不用更新
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	//写文件流
	for (int i = 0; i < m_Size; i++)
	{
		//将所以的预约写到文件内
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
}
