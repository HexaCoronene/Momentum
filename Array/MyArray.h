#ifndef MYARRAY_H
#define MYARRAY_H
#include <string>
#include <fstream>
#include <iostream>

template <class T>
class MyArray {
public:
	MyArray() :row(0), column(0), size(0), array(nullptr) {}
	//MyArray(MyArray &origin);
	MyArray(std::string filename) { FileRead(filename); }
	~MyArray();
	void FileRead(std::string filename);
	void KBRead();
	T Locate(int row, int col);
	void OrderLocate(int num);
	T *begin() { return array; }
	T *end() { return array + size; }
	T Sum();
	double Average();
	T Max();
	T Min();
	double Median();
	friend std::ostream &operator<<(std::ostream &os, MyArray<T> &A)
	{
		for( int i = 0; i < A.row; i++ )
		{
			for( int j = 0; j < A.column; j++ )
			{
				os << A.Locate(i + 1, j + 1) << " ";
			}
			os << std::endl;
		}
		return os;
	}
private:
	T *array;
	int row, column;
	int size;
	T *Copy();
};

template <class T>
MyArray<T>::~MyArray()
{
	delete[]array;
}

template<class T>
void MyArray<T>::FileRead(std::string filename)
{
	std::ifstream fin(filename, std::ios::in);
	if( !fin )
	{
		std::cerr << "File: " << filename << " does not exist!" << std::endl;
		return;
	}
	std::cout << "File:" << filename << " read successfully\n" << std::endl;

	fin >> row >> column;
	size = row * column;
	if( array != nullptr )
	{
		delete[]array;
	}
	array = new T[size];

	for( int i = 0; i < size; i++ )
	{
		fin >> *(array + i);
	}
}

template<class T>
void MyArray<T>::KBRead()
{
	std::cout << "Inpur row:";
	std::cin >> row;
	std::cout << "Input column:";
	std::cin >> column;
	size = row * column;
	if( array != nullptr )
	{
		delete[]array;
	}
	array = new T[size];
	std::cout << "Now Input data:" << std::endl;
	for( int i = 0; i < size; i++ )
	{
		std::cin >> array[i];
		if( (i + 1) % column == 0 )
		{
			std::cout << (i + 1) / column << " row read completely" << std::endl;
		}
	}
	std::cout << std::endl;
}

template<class T>
T MyArray<T>::Locate(int r, int col)
{
	if( r > row || col > column )
	{
		std::cerr << "Out of range!" << std::endl;
		return -1;
	}
	else
	{
		return array[(r - 1) * column + (col - 1)];
	}
}

template<class T>
void MyArray<T>::OrderLocate(int num)
{
	std::cout << "row: " << (num / column + 1) << "\n" << "column: " << num % column << "\ndata: " << array[num - 1] << std::endl;
}

template<class T>
T MyArray<T>::Sum()
{
	T sum = 0;
	for( int i = 0; i < size; i++ )
	{
		sum += array[i];
	}
	return sum;
}

template<class T>
double MyArray<T>::Average()
{
	return static_cast<double>(Sum()) / static_cast<double>(size);
}

template<class T>
T MyArray<T>::Max()
{
	T max = *array;
	for( T *beg = begin(); beg != end(); beg++ )
	{
		max = (*beg > max) ? *beg : max;
	}
	return max;
}

template<class T>
T MyArray<T>::Min()
{
	T min = *array;
	for( T *beg = begin(); beg != end(); beg++ )
	{
		min = (*beg < min) ? *beg : min;
	}
	return min;
	//std::cerr << "No Minimum for this data structure!" << std::endl;
}

template<class T>
double MyArray<T>::Median()
{
	T *copy = Copy();
	T min;

	//≈≈–Ú
	for( int i = 0; i < size; i++ )
	{
		min = *(copy + i);
		for( int j = 1; j < size; j++ )
		{
			if( *(copy + j) < min )
			{
				min = *(copy + j);
			}
		}
	}

	double num;
	if( size % 2 == 0 )
	{
		num = (static_cast<double>(copy[size / 2 - 1]) + static_cast<double>(copy[size / 2])) / 2;
	}
	else
	{
		num = static_cast<double>(copy[size / 2]);
	}
	delete[]copy;
	return num;
}

template<class T>
T *MyArray<T>::Copy()
{
	T *copy = new T[size];
	int i = 0;
	for( T *beg = begin(); beg != end(); beg++ )
	{
		*(copy + i++) = *beg;
	}
	return copy;
}

#endif // MYARRAY_H
