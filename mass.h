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

	int get_size() { return size; };
	const T* get_mas() { return mas; };

	~mass() { delete[] mas; }

};

