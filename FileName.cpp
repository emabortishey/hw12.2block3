#include "Header.h"
#include "mass.h"

int main()
{
	// тест каждой из специализаций и основного шаблона 

	mass<int> obj{ {1, 2, 3, 4, 5}, 5 };

	cout << "Int output:\t" << obj << "\t" << obj.max();

	mass<char*> obj0{ {"char meow 1", "char meow 2", "char meow 3", "char meow 4", "char meow 5"}, 5, 100};

	cout << "\nChar output:\t" << obj0;

	mass<string> obj1{ {"string meow 1", "string meow 2", "string meow 3", "string meow 4", "string meow 5"}, 5};

	cout << "\nString output:\t" << obj1;

	return 0;
}

// перегрузки операторов ввода и вывода 

template<typename T>
ostream& operator<<(ostream& cout, mass<T>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cout << obj.mas[i] << " ";
	}

	return cout;
}

template<typename T>
istream& operator>>(istream& cin, mass<T>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}

ostream& operator<<(ostream& cout, mass<char*>& obj)
{
	for (int i = 0; i < obj.size_row; i++)
	{
		cout << obj.mas[i] << " ";
	}

	return cout;
}

istream& operator>>(istream& cin, mass<char*>& obj)
{
	for (int i = 0; i < obj.size_row; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}

ostream& operator<<(ostream& cout, mass<string>& obj)
{
	for (int i = 0; i < obj.size_row; i++)
	{
		cout << obj.mas[i] << " ";
	}

	return cout;
}

istream& operator>>(istream& cin, mass<string>& obj)
{
	for (int i = 0; i < obj.size_row; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}