#include <iostream>
#include <fstream>
#include "cgi.h"
#include "stack.h"

using namespace std;
void show_content();
void show_menu();
void show_header();

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
	cout << "Скобки";
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
	cout << "<form method='get' action='stack.cgi'>";
	cout << "Введите выражение: <input type='text' value='' name='expression' maxlength='50' size='50'><br>";
	cout << "<input type='submit' value='Отправить'>";
	cout << "</form>";
	get_form_data(data);
	elem* stack = nullptr;
	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "expression", data);
		char* dec_str = new char[sz];
		str_decode(dec_str, value);
		int first_ind = -1;
		int second_ind = -1;
		checking_brackets(stack, dec_str, first_ind, second_ind);
		if (first_ind == -1 && second_ind == -1) {
			cout << "<div>";
			for (int j = 0; j < strlen(dec_str); j++) {
				cout << dec_str[j];
			}
			cout << "</div>";
		}
		else {
			cout << "<div>";
			for (int j = 0; j < strlen(dec_str); j++) {
				if (j == first_ind || j == second_ind) {
					cout << "<span style='background:red;'>" << dec_str[j] << "</span>";
				}
				else {
					cout << dec_str[j];
				}
			}
			cout << "</div>";
		}
		delete[] dec_str;
	}
	delete[] data;
}