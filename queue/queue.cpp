#include <iostream>
#include <fstream>
#include <windows.h>
#include "queue.h"
#include "cgi.h"
using namespace std;
void load_data(const char* filename, queue& empl, queue& unempl);
void show_data(queue& q);
void show_content();
void show_menu();
void show_header();
void conversion_data(char* man, char*& fullName, char*& gender, int& age, char*& jobAddress, double& income, char*& purpose);
void conversion_data(char* man, char*& fullName, char*& gender, int& age, char*& jobAddress, double& income, char*& purpose) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char* s_copy = new char[strlen(man) + 1];
	strcpy_s(s_copy, strlen(man) + 1, man);
	char* context;
	char* temp = s_copy;
	int i = 0;
	while (char* p = strtok_s(temp, "|", &context)) {
		if (i == 0) {
			fullName = p;
		}
		else if (i == 1) {
			gender = p;
		}
		else if (i == 2) {
			age = atoi(p);
		}
		else if (i == 3) {
			jobAddress = p;
		}
		if (i == 4 && isdigit(p[1])) {
			income = atoi(p);
		}
		else if (i == 5 || i == 4) {
			purpose = p;
			if (i == 4)income = 0;
		}
		i += 1;
		temp = nullptr;
	}

}
void load_data(const char* filename, queue& debt, queue& contribution)
{
	ifstream f(filename);
	if (f.is_open())
	{
		while (!f.eof())
		{

			char man[65536];
			f.getline(man, 65536);
			char* fullName = new char[1024];
			char* gender = new char[1024];
			int age;
			char* jobAddress = new char[1024];
			double income;
			char* purpose = new char[1024];
			conversion_data(man, fullName, gender, age, jobAddress, income, purpose);
			if (strcmp(purpose, " кредит") == 0)
				enqueue(debt, fullName, gender, age, jobAddress, income, purpose);
			else
				enqueue(contribution, fullName, gender, age, jobAddress, income, purpose);
		}
		f.close();
	}
}
void show_data(queue& q)
{
	int i = 0;
	while (q.size > 0)
	{
		man m;
		if (dequeue(q, m))
		{
			cout << ++i << ".\t" << m.fullName << "\tВозраст:" << m.age << "\tПол:" << m.gender << "\tМесто работы:" << m.jobAddress << "\tДоход:" << m.income << "<br>";
		}
	}
}




void main()
{

	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f("_index");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];

		while (!f.eof())
		{
			f.getline(buf, sz);
			if (strcmp(buf, "<!--#CONTENT#-->") == 0)
			{
				show_content();
			}
			else if (!strcmp(buf, "<!--#MENU#-->"))
			{
				show_menu();
			}
			else if (!strcmp(buf, "<!--#HEADER#-->"))
			{
				show_header();
			}
			cout << buf;
		}
		delete[] buf;
		f.close();
	}
	else
	{
		cout << "Не удалось вывести страницу :(";
	}

}

void show_header()
{
	cout << "Очереди";
}
void show_menu()
{
	ifstream f("menu");
	if (f.is_open())
	{
		auto sz = 1024;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			char* name;
			char* addrr = strtok_s(buf, " ", &name);
			cout << "<div class='menu-item'>"
				"<a href='" << addrr << "'>" <<
				name << "</a>"
				"</div>";
		}
	}
	f.close();
}
void show_content()
{
	auto sz = 65536;
	char* data = nullptr;

	setlocale(LC_ALL, "Rus");

	cout << "<form method='get' action='queue.cgi'>";
	cout << "Введите адрес файла: <input type='text' value='' name='expression' maxlength='50' size='50'><br>";
	cout << "<input type='submit' value='Отправить'>";
	cout << "</form>";


	get_form_data(data);
	if (data && strlen(data) > 0) {
		queue debt;
		queue contribution;
		char* value = nullptr;
		get_param_value(value, "expression", data);
		char* dec_str = new char[sz];
		str_decode(dec_str, value);
		load_data(dec_str, debt, contribution);
		cout << "Лица со вкладом" << "<br>";
		show_data(contribution);
		cout << "Лица с кредитами" << "<br>";
		show_data(debt);
		delete[] dec_str;
	}
	delete[] data;
}