#include <iostream>
#include <fstream>
//#include <vector>
//#include <clocale>
//#include <Windows.h>90

using namespace std;

struct Date
{
	int day;
	int month;
	int year;
};

struct ThemesOfWorks
{
	string name;
	string topic;
	Date* date = NULL;
	ThemesOfWorks* ind;

	~ThemesOfWorks()
	{
		delete[] date;
	}
};

Date* ReadingTheDate(ifstream& ist)
{
	char buf;
	Date* date = new Date;
	ist >> date->day;
	ist.get(buf);
	ist >> date->month;
	ist.get(buf);
	ist >> date->year;

	return date;
}

ThemesOfWorks* ReadingTheThemesOfWork(ifstream& ist)
{
	ThemesOfWorks* PointerToTheList = new ThemesOfWorks, * indicator = NULL;
	PointerToTheList->ind = NULL;

	while (!ist.eof())
	{
		ist >> PointerToTheList->name >> PointerToTheList->topic;
		PointerToTheList->date = ReadingTheDate(ist);
		indicator = PointerToTheList;

		if (!ist.eof())
		{
			PointerToTheList = new ThemesOfWorks;
			PointerToTheList->ind = indicator;
		}
	}

	return indicator;
}

void DateOutput(Date* date)
{
	printf("%d.%d.%d\n", date->day, date->month, date->year);
}

void ListOutputToTheConsole(ThemesOfWorks* PointerToTheList)
{
	ThemesOfWorks* indicator = PointerToTheList;
	printf("\tName\tTopic\tDate\n");

	while (PointerToTheList != NULL)
	{
		printf("\t%s\t%s\t", PointerToTheList->name.c_str(), PointerToTheList->topic.c_str());
		DateOutput(PointerToTheList->date);
		PointerToTheList = PointerToTheList->ind;
		delete indicator;
		indicator = PointerToTheList;
	}
}


int main()
{
	ifstream ist("Themes Of Works.txt");
	ThemesOfWorks* PointerToTheList = ReadingTheThemesOfWork(ist);
	ist.close();
	ListOutputToTheConsole(PointerToTheList);

	return 0;
}