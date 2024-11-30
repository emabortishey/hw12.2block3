// вынос методов основного шаблона

template<typename T>
mass<T>::mass(mass&& obj) : mas{ new T[obj.size] }, size{ obj.size } {
	mas = obj.mas;
	obj.mas = nullptr;
	obj.size = 0;
}

template<typename T>
void mass<T>::set_mas(T* obj)
{
	delete[] mas;
	size = sizeof(obj.mas);
	mas = new T[size]{ *obj.mas };
}

template<typename T>
mass<T>::mass(const initializer_list<T>& mas_P, const int size_P) : mas{ new T[size_P] }, size{ size_P }
{
	int index = 0;
	// в цикле при каждом обходе элементу присваивается текуций параметр по индексу
	// масс поинтер, обход продолжается до тех пор пока не будет достигнут конец
	// масс поинтера

	for (auto elem : mas_P) {
		mas[index++] = elem;
	}
}

template<class T>
T mass<T>::max() const
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

template<typename T>
T mass<T>::min() const
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

template<typename T>
const T& mass<T>::search(T seek)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] == seek)
		{
			return mas[i];
		}
	}
}

template<typename T>
void mass<T>::adding(T el)
{
	size++;
	T* buff = new T[size]{ *mas };
	delete[] mas;
	mas = new T[size]{ *buff };
	mas[size - 1] = el;
}

template<typename T>
void mass<T>::deleting()
{
	size--;
	T* buff = new T[size]{ *mas };
	delete[] mas;
	mas = new T[size]{ *buff };
}

template<typename T>
mass<T>& mass<T>::operator=(const mass& obj)
{
	delete[] mas;
	mas = new T[obj.size]{ *obj.mas };
	size = obj.size;

	return *this;
}

template<typename T>
mass<T>& mass<T>::operator=(mass&& obj)
{
	delete[] mas;
	mas = obj.mas;
	size = obj.size;
	obj.mas = nullptr;
	obj.size = 0;

	return *this;
}




// закоментированный вынос методов специализаций класса



//mass<char*>::mass(char** mas_P, const int size_P_row, const int size_P_col) : mas{ new char* [size_P_row] }, size_row{ size_P_row }, size_col{ size_P_col }
//{
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, mas_P[i]);
//	}
//}
//mass<char*>::mass(const initializer_list<const char*>& mas_P, const int size_P_row, const int size_P_col) : mas{ new char* [size_P_row] }, size_row{ size_P_row }, size_col{ size_P_col }
//{
//	int index = 0;
//	for (auto elem : mas_P) {
//		mas[index] = new char[size_col];
//		strcpy_s(mas[index++], size_col, elem);
//	}
//}
//mass<char*>::mass(const mass& obj) : mas{ new char* [obj.size_row] }, size_row{ obj.size_row }, size_col{ obj.size_col }
//{
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, obj.mas[i]);
//	}
//}
//mass<char*>::mass(mass&& obj) : mas{ new char* [obj.size_row] }, size_row{ obj.size_row }, size_col{ obj.size_col }
//{
//	mas = obj.mas;
//	obj.mas = nullptr;
//	obj.size_row = 0;
//	obj.size_col = 0;
//}
//void mass<char*>::set_mas(char** obj) 
//{
//	delete[] mas;
//	size_row = sizeof(obj);
//	size_col = sizeof(obj[0]);
//	mas = new char* [size_row];
//
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, obj[i]);
//	}
//}
//char* mass<char*>::max() const
//{
//	char* max_el = mas[0];
//
//	for (int i = 0; i < size_row; i++)
//	{
//		if (strcmp(mas[i], max_el) == 1)
//		{
//			max_el = mas[i];
//		}
//	}
//
//	return max_el;
//}
//char* mass<char*>::min() const
//{
//	char* min_el = mas[0];
//
//	for (int i = 0; i < size_row; i++)
//	{
//		if (strcmp(mas[i], min_el) == -1)
//		{
//			min_el = mas[i];
//		}
//	}
//
//	return min_el;
//}
//const char* mass<char*>::search(char* seek)
//{
//	for (int i = 0; i < size_row; i++)
//	{
//		if (strcmp(mas[i], seek) == 0)
//		{
//			return mas[i];
//		}
//	}
//}
//void mass<char*>::adding(char* el)
//{
//	size_row++;
//	char** buff = new char* [size_row];
//	for (int i = 0; i < size_row; i++)
//	{
//		buff[i] = new char[size_col];
//		strcpy_s(buff[i], size_col, mas[i]);
//	}
//	delete[] mas;
//	mas = new char* [size_row];
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, buff[i]);
//	}
//	strcpy_s(mas[size_row - 1], size_row, el);
//}
//void mass<char*>::deleting()
//{
//	size_row--;
//	char** buff = new char* [size_row] { *mas };
//	for (int i = 0; i < size_row; i++)
//	{
//		buff[i] = new char[size_col];
//		strcpy_s(buff[i], size_col, mas[i]);
//	}
//	delete[] mas;
//	mas = new char* [size_row];
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, buff[i]);
//	}
//}
//mass<char*>& mass<char*>::operator=(const mass& obj)
//{
//	delete[] mas;
//	mas = new char* [obj.size_row];
//	size_row = obj.size_row;
//	size_col = obj.size_col;
//	for (int i = 0; i < size_row; i++)
//	{
//		mas[i] = new char[size_col];
//		strcpy_s(mas[i], size_col, obj.mas[i]);
//	}
//
//	return *this;
//}
//mass<char*>& mass<char*>::operator=(mass&& obj)
//{
//	for (int i = 0; i < size_row; i++)
//	{
//		delete[] mas[i];
//	}
//	delete[] mas;
//	mas = obj.mas;
//	size_row = obj.size_row;
//	size_col = obj.size_col;
//	obj.mas = nullptr;
//	obj.size_row = 0;
//	obj.size_col = 0;
//
//	return *this;
//}
//
//mass<string>::mass(const initializer_list<string>& mas_P, const int size_P) : mas{ new string[size_P] }, size_row{ size_P }
//{
//	int index = 0;
//	for (auto elem : mas_P) {
//		mas[index++] = elem;
//	}
//}
//mass<string>::mass(mass&& obj) : mas{ new string[obj.size_row] }, size_row{ obj.size_row } {
//	mas = obj.mas;
//	obj.mas = nullptr;
//	obj.size_row = 0;
//}
//void mass<string>::set_mas(string* obj)
//{
//	delete[] mas;
//	size_row = obj[0].size();
//	mas = new string[size_row];
//}
//char mass<string>::max() const
//{
//	char max_el = mas[0][0];
//
//	for (int i = 0; i < size_row; i++)
//	{
//		for (int j = 0; j < size_row; j++)
//		{
//			if (mas[i][j] > max_el)
//			{
//				max_el = mas[i][j];
//			}
//		}
//	}
//
//	return max_el;
//}
//char mass<string>::min() const
//{
//	char min_el = mas[0][0];
//
//	for (int i = 0; i < size_row; i++)
//	{
//		for (int j = 0; j < size_row; j++)
//		{
//			if (mas[i][j] < min_el)
//			{
//				min_el = mas[i][j];
//			}
//		}
//	}
//
//	return min_el;
//}
//const string& mass<string>::search(string seek)
//{
//	for (int i = 0; i < size_row; i++)
//	{
//		if (mas[i] == seek)
//		{
//			return mas[i];
//		}
//	}
//}
//void mass<string>::adding(string el)
//{
//	size_row++;
//	string* buff = new string[size_row]{ *mas };
//	delete[] mas;
//	mas = new string[size_row]{ *buff };
//	mas[size_row - 1] = el;
//}
//void mass<string>::deleting()
//{
//	size_row--;
//	string* buff = new string[size_row]{ *mas };
//	delete[] mas;
//	mas = new string[size_row]{ *buff };
//}
//mass<string>& mass<string>::operator=(const mass& obj)
//{
//	delete[] mas;
//	mas = new string[obj.size_row]{ *obj.mas };
//	size_row = obj.size_row;
//
//	return *this;
//}
//mass<string>& mass<string>::operator=(mass&& obj)
//{
//	delete[] mas; 
//	mas = obj.mas;
//	size_row = obj.size_row;
//	obj.mas = nullptr;
//	obj.size_row = 0;
//
//	return *this;
//}