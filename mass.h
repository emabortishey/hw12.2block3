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
	mass(const T& mas_P) : mass(mas_P, sizeof(mas_P)) { }
	mass(const T& mas_P, const int size_P) : mas{ new T[size_P]{*mas_P} }, size{size_P} { }
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

	T* operator=(const mass& obj)
	{
		delete[] mas;
		mas = new T[obj.size]{ *obj.mas };
		size = obj.size;
	}

	T* operator=(mass&& obj)
	{
		delete[] mas;
		mas = obj.mas;
		size = obj.size;
		obj.mas = nullptr;
		obj.size = 0;
	}

	T operator[](const int index) const
	{
		return mas[index];
	}


	int get_size() { return size; };
	const T* get_mas() { return mas; };

	~mass() { delete[] mas; }

};

