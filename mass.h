#pragma once
#include <iostream>
#include <initializer_list>
#include "massinl.inl"
using namespace std;

template<class T>
class mass
{
	T* mas;
	int size;
public:
	mass() : mass(nullptr, 10) { }
	mass(const T** mas_P) : mass(mas_P, sizeof(mas_P)) { }
	mass(const T** mas_P, const int size_P) : mas{ new T[size_P]{*mas_P} }, size{size_P} { }
	mass(const initializer_list<T>& mas_P, const int size_P) : mas{ new T[size_P] }, size{ size_P }
	{
		int index = 0;
		for (auto elem : mas_P) {
			mas[index++] = elem;
		}
	}
	mass(const mass& obj) : mas{ new T[obj.size]{*obj.mas} }, size{ obj.size } { }
	mass(mass&& obj) : mas{ new T[obj.size] }, size{ obj.size } {
		mas = obj.mas;
		obj.mas = nullptr;
		obj.size = 0;
	}

	void set_mas(T* obj)
	{
		delete[] mas;
		size = sizeof(obj.mas);
		mas = new T[size]{ *obj.mas };
	}
	void set_size(int obj) { size = obj; }

	friend ostream& operator<<(ostream& cout, mass<int>& obj);
	friend istream& operator>>(istream& cin, mass<int>& obj);

	T max()
	{
		T max_el = mas[0];

		for (int i = 0; i < size; i++)
		{
			if (mas[i] > max_el)
			{
				max_el = mas[i];
			}
		}

		return max_el;
	}

	T min()
	{
		T min_el = mas[0];

		for (int i = 0; i < size; i++)
		{
			if (mas[i] < min_el)
			{
				min_el = mas[i];
			}
		}

		return min_el;
	}

	const T& search(T seek)
	{
		for (int i = 0; i < size; i++)
		{
			if (mas[i] == seek)
			{
				return mas[i];
			}
		}
	}

	void adding(T el)
	{
		size++;
		T* buff = new T[size]{ *mas };
		delete[] mas;
		mas = new T[size]{ *buff };
		mas[size - 1] = el;
	}

	void deleting()
	{
		size--;
		T* buff = new T[size]{ *mas };
		delete[] mas;
		mas = new T[size]{ *buff };
	}

	mass& operator=(const mass& obj)
	{
		delete[] mas;
		mas = new T[obj.size]{ *obj.mas };
		size = obj.size;

		return *this;
	}

	mass& operator=(mass&& obj)
	{
		delete[] mas;
		mas = obj.mas;
		size = obj.size;
		obj.mas = nullptr;
		obj.size = 0;

		return *this;
	}

	T operator[](const int index) const
	{
		return mas[index];
	}


	int get_size() { return size; };
	const T* get_mas() { return mas; };

	~mass() { delete[] mas; }

};

template<>
class mass<char*>
{
	char** mas;
	int size_row;
	int size_col;
public:
	mass() : mass(nullptr, 10, 100) { }
	mass(char** mas_P) : mass(mas_P, sizeof(mas_P), sizeof(mas_P[0])) { }
	mass(char** mas_P, const int size_P_row) : mass(mas_P, size_P_row, sizeof(mas_P[0])) { }
	mass(char** mas_P, const int size_P_row, const int size_P_col) : mas{ new char*[size_P_row] }, size_row{ size_P_row }, size_col{size_P_col}
	{  
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, mas_P[i]);
		}
	}
	mass(const initializer_list<const char*>& mas_P, const int size_P_row, const int size_P_col) : mas{ new char*[size_P_row] }, size_row{ size_P_row }, size_col{size_P_col}
	{
		int index = 0;
		for (auto elem : mas_P) {
			mas[index] = new char[size_col];
			strcpy_s(mas[index++], size_col, elem);
		}
	}
	mass(const mass& obj) : mas{ new char*[obj.size_row]}, size_row{ obj.size_row }, size_col{ obj.size_col }
	{
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, obj.mas[i]);
		}
	}
	mass(mass&& obj) : mas{ new char*[obj.size_row] }, size_row{ obj.size_row }, size_col{ obj.size_col } {
		mas = obj.mas;
		obj.mas = nullptr;
		obj.size_row = 0;
		obj.size_col = 0;
	}

	void set_mas(char** obj)
	{
		delete[] mas;
		size_row = sizeof(obj);
		size_col = sizeof(obj[0]);
		mas = new char*[size_row];

		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, obj[i]); 
		}
	}
	void set_size_row(int obj) { size_row = obj; }
	void set_size_col(int obj) { size_col = obj; }

	friend ostream& operator<<(ostream& cout, mass<char*>& obj);
	friend istream& operator>>(istream& cin, mass<char*>& obj);

	char* max()
	{
		char* max_el = mas[0];

		for (int i = 0; i < size_row; i++)
		{
			if (strcmp(mas[i], max_el) == 1)
			{
				max_el = mas[i];
			}
		}

		return max_el;
	}

	char* min()
	{
		char* min_el = mas[0];

		for (int i = 0; i < size_row; i++)
		{
			if (strcmp(mas[i], min_el) == -1)
			{
				min_el = mas[i];
			}
		}

		return min_el;
	}

	const char* search(char* seek)
	{
		for (int i = 0; i < size_row; i++)
		{
			if (strcmp(mas[i], seek)==0)
			{
				return mas[i];
			}
		}
	}

	void adding(char* el)
	{
		size_row++;
		char** buff = new char*[size_row];
		for (int i = 0; i < size_row; i++)
		{
			buff[i] = new char[size_col];
			strcpy_s(buff[i], size_col, mas[i]);
		}
		delete[] mas;
		mas = new char*[size_row];
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, buff[i]);
		}
		strcpy_s(mas[size_row - 1], size_row, el); 
	}

	void deleting()
	{
		size_row--;
		char** buff = new char*[size_row]{ *mas };
		for (int i = 0; i < size_row; i++)
		{
			buff[i] = new char[size_col];
			strcpy_s(buff[i], size_col, mas[i]);
		}
		delete[] mas;
		mas = new char*[size_row];
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, buff[i]);
		}
	}

	mass& operator=(const mass& obj)
	{
		delete[] mas;
		mas = new char*[obj.size_row];
		size_row = obj.size_row;
		size_col = obj.size_col;
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, obj.mas[i]); 
		}

		return *this;
	}

	mass& operator=(mass&& obj)
	{
		for (int i = 0; i < size_row; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;
		mas = obj.mas;
		size_row = obj.size_row;
		size_col = obj.size_col;
		obj.mas = nullptr;
		obj.size_row = 0;
		obj.size_col = 0;

		return *this;
	}

	char* operator[](const int index) const
	{
		return mas[index];
	}


	int get_size_row() { return size_row; }
	int get_size_col() { return size_col; }
	char** get_mas() { return mas; };

	~mass() 
	{ 
		for (int i = 0; i < size_row; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;
	}

};

template<>
class mass<string>
{
	string* mas;
	int size_row;
public:
	mass() : mass(nullptr, 10) { }
	mass(const string* mas_P) : mass(mas_P, sizeof(mas_P)) { }
	mass(const string* mas_P, const int size_P) : mas{ new string[size_P]{*mas_P} }, size_row{ size_P } { }
	mass(const initializer_list<string>& mas_P, const int size_P) : mas{ new string[size_P] }, size_row{ size_P }
	{
		int index = 0;
		for (auto elem : mas_P) {
			mas[index++] = elem;
		}
	}
	mass(const mass& obj) : mas{ new string[obj.size_row]{*obj.mas} }, size_row{ obj.size_row } { }
	mass(mass&& obj) : mas{ new string[obj.size_row] }, size_row{ obj.size_row } {
		mas = obj.mas;
		obj.mas = nullptr;
		obj.size_row = 0;
	}

	void set_mas(string* obj)
	{
		delete[] mas;
		size_row = obj[0].size();
		mas = new string[size_row];
	}
	void set_size(int obj) { size_row = obj; }

	friend ostream& operator<<(ostream& cout, mass<string>& obj);
	friend istream& operator>>(istream& cin, mass<string>& obj);

	auto max()
	{
		auto max_el = mas[0][0];

		for (int i = 0; i < size_row; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				if (mas[i][j] > max_el)
				{
					max_el = mas[i][j];
				}
			}
		}

		return max_el;
	}

	auto min()
	{
		auto min_el = mas[0][0];

		for (int i = 0; i < size_row; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				if (mas[i][j] < min_el)
				{
					min_el = mas[i][j];
				}
			}
		}

		return min_el;
	}

	const string& search(string seek)
	{
		for (int i = 0; i < size_row; i++)
		{
			if (mas[i] == seek)
			{
				return mas[i];
			}
		}
	}

	void adding(string el)
	{
		size_row++;
		string* buff = new string[size_row]{ *mas };
		delete[] mas;
		mas = new string[size_row]{ *buff };
		mas[size_row - 1] = el;
	}

	void deleting()
	{
		size_row--;
		string* buff = new string[size_row]{ *mas };
		delete[] mas;
		mas = new string[size_row]{ *buff };
	}

	mass& operator=(const mass& obj)
	{
		delete[] mas;
		mas = new string[obj.size_row]{ *obj.mas };
		size_row = obj.size_row;

		return *this;
	}

	mass& operator=(mass&& obj)
	{
		delete[] mas;
		mas = obj.mas;
		size_row = obj.size_row;
		obj.mas = nullptr;
		obj.size_row = 0;

		return *this;
	}

	string operator[](const int index) const
	{
		return mas[index];
	}


	int get_size() { return size_row; };
	const string* get_mas() { return mas; };

	~mass() 
	{ 
		for (int i = 0; i < size_row; i++)
		{
			mas[i].clear();
		}
		delete[] mas;
	}

};