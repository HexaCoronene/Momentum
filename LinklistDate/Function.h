#ifndef FUCTION_H
#define FUCTION_H

void Welcome(void)
{
	std::cout << "请输入两个日期，格式yyyymmdd，以空格分隔" << std::endl;
}

void FuncChoose(void)
{
	std::cout << "请输入序号以选择功能" << "\n"
		<< "[1]添加休息日，格式yyyymmdd" << "\n"
		<< "[2]删除休息日，格式yyyymmdd" << "\n"
		<< "[3]查询给定日期是否为休息日或休息日，格式yyyymmdd" << "\n"
		<< "[4]查询当前日期间隔内休息日天数" << "\n"
		<< "[5]查询当前日期间隔内工作日天数" << "\n"
		<< "[6]打印当前链表" << "\n"
		<< "[#]输入q以退出" << std::endl;
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
		std::cout << "加入成功！" << std::endl;
	}
	else
	{
		std::cout << "已存在！" << std::endl;
	}
}

void DecHoliday(TMyDateList<TMyNewDate> &ls)
{
	std::string str;
	std::cin >> str;
	TMyNewDate date(str);
	if( ls.Search(date) == nullptr )
	{
		std::cout << "本日期原本不为休息日！" << std::endl;
	}
	else
	{
		ls.Delete(date);
		std::cout << "删除成功" << std::endl;
	}
}

void CheckDay(TMyDateList<TMyNewDate> &ls)
{
	std::string str;
	std::cin >> str;
	TMyNewDate date(str);
	if( ls.Search(date) != nullptr )
	{
		std::cout << "休息日" << std::endl;
	}
	else
	{
		std::cout << "工作日" << std::endl;
	}
}

void WorkDay(TMyDateList<TMyNewDate> &ls, int &result)
{
	std::cout << "工作日" << result + 1 - ls.Length() << "天" << std::endl;
}

void RestDay(TMyDateList<TMyNewDate> &ls)
{
	std::cout << "休息日" << ls.Length() << "天" << std::endl;
}

#endif // FUCTION_H
