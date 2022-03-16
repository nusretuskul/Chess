#ifndef ARRAY2D_H
#define ARRAY2D_H

template <class T>
class Array2D
{
public:
	Array2D(int = 0, int = 0);
	~Array2D();

	void clear();
	bool inBounds(int, int);
	T* operator[](int);

	int getRows();
	int getCols();

private:
	T** arr;
	int cols, rows;
};

template <class T>
Array2D<T>::Array2D(int _cols, int _rows) : cols(_cols), rows(_rows)
{
	arr = new T*[cols];
	for (int _col = 0; _col < cols; ++_col)
	{
		arr[_col] = new T[rows];
		for (int _row = 0; _row < rows; ++_row)
		{
			arr[_col][_row] = NULL;
		}
	}
}

template <class T>
Array2D<T>::~Array2D()
{
	for (int _i = 0; _i < cols; ++_i)
		delete[] arr[_i];
	delete[] arr;
}

template <class T>
void Array2D<T>::clear()
{
	for (int _col = 0; _col < cols; ++_col)
	{
		for (int _row = 0; _row < rows; ++_row)
		{
			delete arr[_col][_row];
			arr[_col][_row] = NULL;
		}
	}
}

template <class T>
bool Array2D<T>::inBounds(int _col, int _row)
{
	return _col >= 0 && _col < cols && _row >= 0 && _row < rows;
}

template <class T>
T* Array2D<T>::operator[](int _index)
{
	return arr[_index];
}

template <class T>
int Array2D<T>::getRows()
{
	return rows;
}

template <class T>
int Array2D<T>::getCols()
{
	return cols;
}

#endif