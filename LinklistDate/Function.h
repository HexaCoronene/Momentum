#ifndef FUCTION_H
#define FUCTION_H

void Welcome(void)
{
	std::cout << "�������������ڣ���ʽyyyymmdd���Կո�ָ�" << std::endl;
}

void FuncChoose(void)
{
	std::cout << "�����������ѡ����" << "\n"
		<< "[1]�����Ϣ�գ���ʽyyyymmdd" << "\n"
		<< "[2]ɾ����Ϣ�գ���ʽyyyymmdd" << "\n"
		<< "[3]��ѯ���������Ƿ�Ϊ��Ϣ�ջ���Ϣ�գ���ʽyyyymmdd" << "\n"
		<< "[4]��ѯ��ǰ���ڼ������Ϣ������" << "\n"
		<< "[5]��ѯ��ǰ���ڼ���ڹ���������" << "\n"
		<< "[6]��ӡ��ǰ����" << "\n"
		<< "[#]����q���˳�" << std::endl;
}

void ListGen(TMyDateList<TMyNewDate> &ls, int &result)
{
	std::string in;
	std::cin >> in; TMyNewDate date1; date1.Input(in);
	std::cin >> in; TMyNewDate date2; date2.Input(in);
	result = date1.DaysBetween(date2);
	while( date1.DaysBetween(date2) > 0 )
	{
		if( date1.IsWeekend() )
		{
			ls.inputR(date1);
		}
		date1.AddDays(1);
	}
}

void AddHoliday(TMyDateList<TMyNewDate> &ls)
{
	std::string str;
	std::cin >> str;
	TMyNewDate date(str);
	if( ls.Search(date) == nullptr )
	{
		ls.inputR(date);
		std::cout << "����ɹ���" << std::endl;
	}
	else
	{
		std::cout << "�Ѵ��ڣ�" << std::endl;
	}
}

void DecHoliday(TMyDateList<TMyNewDate> &ls)
{
	std::string str;
	std::cin >> str;
	TMyNewDate date(str);
	if( ls.Search(date) == nullptr )
	{
		std::cout << "������ԭ����Ϊ��Ϣ�գ�" << std::endl;
	}
	else
	{
		ls.Delete(date);
		std::cout << "ɾ���ɹ�" << std::endl;
	}
}

void CheckDay(TMyDateList<TMyNewDate> &ls)
{
	std::string str;
	std::cin >> str;
	TMyNewDate date(str);
	if( ls.Search(date) != nullptr )
	{
		std::cout << "��Ϣ��" << std::endl;
	}
	else
	{
		std::cout << "������" << std::endl;
	}
}

void WorkDay(TMyDateList<TMyNewDate> &ls, int &result)
{
	std::cout << "������" << result + 1 - ls.Length() << "��" << std::endl;
}

void RestDay(TMyDateList<TMyNewDate> &ls)
{
	std::cout << "��Ϣ��" << ls.Length() << "��" << std::endl;
}

#endif // FUCTION_H
