#include "mass.h"

int main()
{
	mass<int> obj{ {1, 2, 3}, 3 };

	cout << obj;

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