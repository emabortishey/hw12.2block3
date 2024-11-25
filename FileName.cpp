#include "mass.h"

int main()
{
	mass<int> obj{ {1, 2, 3}, 3 };

	cout << obj;

	mass<char*> obj0{ {"meow", "bark", "mmmm", "boom"}, 4 };

	mass<string> obj1{{"meow", "bark", "mmmm", "boom"}, 4};

	cout << obj1;

	return 0;
}

ostream& operator<<(ostream& cout, mass<int>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cout << obj.mas[i] << ' ';
	}

	return cout;
}

istream& operator>>(istream& cin, mass<int>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}

ostream& operator<<(ostream& cout, mass<char*>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cout << obj.mas[i] << ' ';
	}

	return cout;
}

istream& operator>>(istream& cin, mass<char*>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}

ostream& operator<<(ostream& cout, mass<string>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cout << obj.mas[i] << ' ';
	}

	return cout;
}

istream& operator>>(istream& cin, mass<string>& obj)
{
	for (int i = 0; i < obj.size; i++)
	{
		cin >> obj.mas[i];
	}

	return cin;
}