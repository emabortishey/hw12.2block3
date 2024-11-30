#pragma once
#include "Header.h"

template<class T>
class mass
{
	T* mas;
	int size;
public:
	mass() : mass(nullptr, 10) { }
	mass(const T** mas_P) : mass(mas_P, sizeof(mas_P)) { }
	mass(const T** mas_P, const int size_P) : mas{ new T[size_P]{*mas_P} }, size{size_P} { }
	mass(const initializer_list<T>& mas_P, const int size_P);
	mass(const mass& obj) : mas{ new T[obj.size]{*obj.mas} }, size{ obj.size } { }
	mass(mass&& obj);

	void set_mas(T* obj);
	void set_size(int obj) { size = obj; }

	template<typename T>
	friend ostream& operator<<(ostream& cout, mass<T>& obj);
	template<typename T>
	friend istream& operator>>(istream& cin, mass<T>& obj);

	T max() const;

	T min() const;

	const T& search(T seek);

	void adding(T el);

	void deleting();

	mass& operator=(const mass& obj);

	mass& operator=(mass&& obj);

	T operator[](const int index) const { return mas[index]; }

	int get_size() { return size; };
	const T* get_mas() { return mas; };

	~mass() { delete[] mas; }

};

template<>
class mass<char*>
{
	// в специализации char* обычный сайз разделился на сайз колумн и сайз роу
	// для того, чтобы в случае размера строки в 5, подстроки могли содержать
	// любое количество символов (то есть больше чем размер строки-1)

	char** mas;
	int size_row;
	int size_col;
public:
	mass() : mass(nullptr, 10, 100) { }
	mass(char** mas_P) : mass(mas_P, sizeof(mas_P), sizeof(mas_P[0])) { }
	mass(char** mas_P, const int size_P_row) : mass(mas_P, size_P_row, sizeof(mas_P[0])) { }
	mass(char** mas_P, const int size_P_row, const int size_P_col) : mas{ new char* [size_P_row] }, size_row{ size_P_row }, size_col{ size_P_col }
	{
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, mas_P[i]);
		}
	}
	mass(const initializer_list<const char*>& mas_P, const int size_P_row, const int size_P_col) : mas{ new char* [size_P_row] }, size_row{ size_P_row }, size_col{ size_P_col }
	{
		int index = 0;
		// в цикле при каждом обходе элементу присваивается текуций параметр по индексу
		// масс поинтер, обход продолжается до тех пор пока не будет достигнут конец
		// масс поинтера

		for (auto elem : mas_P) {
			mas[index] = new char[size_col];
			strcpy_s(mas[index++], size_col, elem);
		}
	}
	mass(const mass& obj) : mas{ new char* [obj.size_row] }, size_row{ obj.size_row }, size_col{ obj.size_col }
	{
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, obj.mas[i]);
		}
	}
	mass(mass&& obj) : mas{ new char* [obj.size_row] }, size_row{ obj.size_row }, size_col{ obj.size_col }
	{
		mas = obj.mas;
		obj.mas = nullptr;
		obj.size_row = 0;
		obj.size_col = 0;
	}

	void set_mas(char** obj)
	{ // такой же алгоритм как и в конструкторе, но с удалением
		delete[] mas;
		size_row = sizeof(obj);
		size_col = sizeof(obj[0]);
		mas = new char* [size_row];

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

	char* max() const
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

	char* min() const
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
			if (strcmp(mas[i], seek) == 0)
			{
				return mas[i];
			}
		}
	}

	void adding(char* el)
	{
		size_row++;
		char** buff = new char* [size_row];
		// перенос всех значений в буферный массив и его попутная инициализация
		for (int i = 0; i < size_row-1; i++)
		{
			buff[i] = new char[size_col];
			strcpy_s(buff[i], size_col, mas[i]);
		}
		//удаление массива и его пересоздание с новым размеров
		delete[] mas;
		mas = new char* [size_row];
		// перенос данных в новый массив из буфера
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, buff[i]);
		}
		// инициализация последней ячейки полученным элементов
		strcpy_s(mas[size_row - 1], size_row, el);
	}

	void deleting()
	{
		// то же самое что и с добавлением, но без инициализации
		// последней ячейки
		size_row--;
		char** buff = new char* [size_row] { *mas };
		for (int i = 0; i < size_row; i++)
		{
			buff[i] = new char[size_col];
			strcpy_s(buff[i], size_col, mas[i]);
		}
		delete[] mas;
		mas = new char* [size_row];
		for (int i = 0; i < size_row; i++)
		{
			mas[i] = new char[size_col];
			strcpy_s(mas[i], size_col, buff[i]);
		}
	}

	mass& operator=(const mass& obj)
	{
		// то же самое что и с сет_мас
		delete[] mas;
		mas = new char* [obj.size_row];
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
		// то же самое что и с сет_мас но с обнулением принятых данных
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

	char* operator[](const int index) const { return mas[index]; }

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
	// тут не обычный сайз, а сайз роу потому что я сначала
	// начала переделывать специализацию стринг ведь забыла, что 
	// в переменной стринг размер определять при инициализации не нужно
	// а после осознания и удаления сайз колумн забыла переименовать
	// сайз назад и решила не заморачиваться, ведь в вынесенных
	// закоментированных методах уже сайз роу
	int size_row;
public:
	mass() : mass(nullptr, 10) { }
	mass(const string* mas_P) : mass(mas_P, sizeof(mas_P)) { }
	mass(const string* mas_P, const int size_P) : mas{ new string[size_P]{*mas_P} }, size_row{ size_P } { }
	mass(const initializer_list<string>& mas_P, const int size_P) : mas{ new string[size_P] }, size_row{ size_P }
	{
		int index = 0;
		// в цикле при каждом обходе элементу присваивается текуций параметр по индексу
		// масс поинтер, обход продолжается до тех пор пока не будет достигнут конец
		// масс поинтера
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
		// такой же алгоритм как и в конструкторе, но с удалением
		delete[] mas;
		size_row = obj[0].size();
		mas = new string[size_row]{ *obj };
	}
	void set_size(int obj) { size_row = obj; }

	friend ostream& operator<<(ostream& cout, mass<string>& obj);
	friend istream& operator>>(istream& cin, mass<string>& obj);

	char max() const
	{
		char max_el = mas[0][0];

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

	char min() const
	{
		char min_el = mas[0][0];

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

	string operator[](const int index) const { return mas[index]; }

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


#include "massINL.inl"



// закоментированная часть со специализациями класса в которых вынесены
// все методы и оставлены только их прототипы



//template<>
//class mass<char*>
//{
//	char** mas;
//	int size_row;
//	int size_col;
//public:
//	mass() : mass(nullptr, 10, 100) { }
//	mass(char** mas_P) : mass(mas_P, sizeof(mas_P), sizeof(mas_P[0])) { }
//	mass(char** mas_P, const int size_P_row) : mass(mas_P, size_P_row, sizeof(mas_P[0])) { }
//	mass(char** mas_P, const int size_P_row, const int size_P_col);
//	mass(const initializer_list<const char*>& mas_P, const int size_P_row, const int size_P_col);
//	mass(const mass& obj);
//	mass(mass&& obj);
//
//	void set_mas(char** obj);
//	void set_size_row(int obj) { size_row = obj; }
//	void set_size_col(int obj) { size_col = obj; }
//	friend ostream& operator<<(ostream& cout, mass<char*>& obj);
//	friend istream& operator>>(istream& cin, mass<char*>& obj);
//	char* max() const;
//	char* min() const;
//	const char* search(char* seek);
//	void adding(char* el);
//	void deleting();
//	mass& operator=(const mass& obj);
//	mass& operator=(mass&& obj);
//	char* operator[](const int index) const { return mas[index]; }
//	int get_size_row() { return size_row; }
//	int get_size_col() { return size_col; }
//	char** get_mas() { return mas; };
//
//	~mass()
//	{
//		for (int i = 0; i < size_row; i++)
//		{
//			delete[] mas[i];
//		}
//		delete[] mas;
//	}
//};
//
// 
// 
// 
//template<>
//class mass<string>
//{
//	string* mas;
//	int size_row;
//public:
//	mass() : mass(nullptr, 10) { }
//	mass(const string* mas_P) : mass(mas_P, sizeof(mas_P)) { }
//	mass(const string* mas_P, const int size_P) : mas{ new string[size_P]{*mas_P} }, size_row{ size_P } { }
//	mass(const initializer_list<string>& mas_P, const int size_P);
//	mass(const mass& obj) : mas{ new string[obj.size_row]{*obj.mas} }, size_row{ obj.size_row } { }
//	mass(mass&& obj);
//
//	void set_mas(string* obj);
//	void set_size(int obj) { size_row = obj; }
//	friend ostream& operator<<(ostream& cout, mass<string>& obj);
//	friend istream& operator>>(istream& cin, mass<string>& obj);
//	char max() const;
//	char min() const;
//	const string& search(string seek);
//	void adding(string el);
//	void deleting();
//	mass& operator=(const mass& obj);
//	mass& operator=(mass&& obj);
//	string operator[](const int index) const { return mas[index]; }
//	int get_size() { return size_row; };
//	const string* get_mas() { return mas; };
//
//	~mass()
//	{
//		for (int i = 0; i < size_row; i++)
//		{
//			mas[i].clear();
//		}
//		delete[] mas;
//	}
//};