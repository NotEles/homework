#ifndef _DEQUE_H
#define _DEQUE_H

#include <iostream>
using namespace std;

template <class T>
class Deque
{
public:
	Deque();
	~Deque();
	void pushFront(T*);
	void pushBack(T*);
	T* popFront();
	T* popBack();
	void showInfo(bool);

private:
	T** rootArr;
	int rootCapacity;
	int rootFrontIndex;
	int rootBackIndex;
	void expandRoot();

	int indexOfFrontArr;
	int indexOfBackArr;
	void addFrontArr();
	void removeFrontArr();
	void addBackArr();
	void removeBackArr();

	const int ARR_SIZE = 16;
};

template <class T>
Deque<T>::Deque()
{
	rootCapacity = ARR_SIZE;
	rootArr = new T * [rootCapacity];
	rootFrontIndex = rootCapacity >> 1;
	rootBackIndex = rootFrontIndex;
	rootArr[rootFrontIndex] = new T[ARR_SIZE];
	indexOfFrontArr = -1;
	indexOfBackArr = -1;
}
template <class T>
Deque<T>::~Deque()
{
	for (int i = rootBackIndex; i <= rootFrontIndex; i++)
		delete[] rootArr[i];
	delete[] rootArr;
}
template <class T>
void Deque<T>::expandRoot()
{
	T** newRootArr = new T * [rootCapacity * 2];
	int amountOfRootElement = rootFrontIndex - rootBackIndex + 1;
	int newRootBackIndex = (rootCapacity * 2 - amountOfRootElement) >> 1;
	for (int i = 0; i < amountOfRootElement; i++)
		newRootArr[newRootBackIndex + i] = rootArr[rootBackIndex + i];
	rootBackIndex = newRootBackIndex;
	rootFrontIndex = newRootBackIndex + amountOfRootElement - 1;
	delete[] rootArr;
	rootArr = newRootArr;
	rootCapacity *= 2;
}
template <class T>
void Deque<T>::addFrontArr()
{
	if (rootFrontIndex == rootCapacity - 1)
		expandRoot();
	rootFrontIndex++;
	rootArr[rootFrontIndex] = new T[ARR_SIZE];
	indexOfFrontArr = -1;   
}
template <class T>
void Deque<T>::addBackArr()
{
	if (rootBackIndex == 0)
		expandRoot();
	rootBackIndex--;
	rootArr[rootBackIndex] = new T[ARR_SIZE];
	indexOfBackArr = -1;    //有了新的边界数组，但暂无元素，置为负
}

template <class T>
void Deque<T>::removeFrontArr()
{
	delete[] rootArr[rootFrontIndex];
	rootFrontIndex--;
	indexOfFrontArr = ARR_SIZE - 1;
}

template <class T>
void Deque<T>::removeBackArr()
{
	delete[] rootArr[rootBackIndex];
	rootBackIndex++;
	indexOfBackArr = 0;
}

template <class T>
void Deque<T>::pushFront(T* s)
{
	
	if (rootFrontIndex == rootBackIndex && indexOfFrontArr < 0)
	{
		indexOfFrontArr = 7;
		indexOfBackArr = 8;
	}
	if (indexOfFrontArr == 15) {
		addFrontArr();
	}

	rootArr[rootFrontIndex][++indexOfFrontArr] = *s;
}
template <class T>
void Deque<T>::pushBack(T* s)
{
	if (rootFrontIndex == rootBackIndex && indexOfBackArr < 0)
	{
		indexOfFrontArr = 8;
		indexOfBackArr = 9;
	}
	if (indexOfBackArr == 0) {
		addBackArr();
	}
	if (indexOfBackArr == -1)
		indexOfBackArr = 16;
	rootArr[rootBackIndex][--indexOfBackArr] = *s;
}
template <class T>
T* Deque<T>::popFront()
{
	//整个队列还剩最后一个元素，或为空
	if (rootFrontIndex == rootBackIndex && indexOfFrontArr == indexOfBackArr)
	{
		if (indexOfFrontArr >= 0) //最后一个元素
		{
			T& tem2 = rootArr[rootFrontIndex][indexOfFrontArr];
			indexOfFrontArr = -1;
			indexOfBackArr = -1;
			return &tem2;
		}
		else 
			return nullptr;
	}
	if (indexOfFrontArr == -1)
	{
		removeFrontArr();
	}
	T& tem1 = rootArr[rootFrontIndex][indexOfFrontArr--];
	return &tem1;
}

template <class T>
T* Deque<T>::popBack()
{
	if (rootFrontIndex == rootBackIndex && indexOfFrontArr == indexOfBackArr)
	{
		if (indexOfFrontArr >= 0) //最后一个元素
		{
			T& tem1 = rootArr[rootBackIndex][indexOfBackArr];
			indexOfFrontArr = -1;
			indexOfBackArr = -1;
			return &tem1;

		}
		else //空，无元素可弹出
			return nullptr;
	}
	if (indexOfBackArr == -1)
		removeBackArr();
	 T* tem2  =&rootArr[rootBackIndex][indexOfBackArr++];
	if (indexOfBackArr == 16)
		indexOfBackArr = -1;
	return tem2;
}
template <class T>
void Deque<T>::showInfo(bool showAllDetails)
{
	using namespace std;
	cout << "Deque Status:" << endl
		<< "Root Array: capacity: " << rootCapacity << ", from " << rootBackIndex << " to " << rootFrontIndex << endl
		<< "Element Arrays: capacity: " << ARR_SIZE << endl
		<< "Left most element of left most array: " << indexOfBackArr << endl
		<< "Right most element of right most array: " << indexOfFrontArr << endl;
	if (showAllDetails)
	{
		cout << endl;
		cout << "All Elements:" << endl;
		for (int i = indexOfBackArr; i < ARR_SIZE; i++)
			cout<<rootArr[rootBackIndex][i];
		for (int m = rootBackIndex + 1; m < rootFrontIndex; m++)
			for (int i = 0; i < ARR_SIZE; i++)
				cout<<rootArr[m][i];
		for (int i = 0; i <= indexOfFrontArr; i++)
			cout<<rootArr[rootFrontIndex][i];
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << "Left most element: ";
		cout<<rootArr[rootBackIndex][indexOfBackArr];
		cout << "Right most element: ";
		cout<<(rootArr[rootFrontIndex][indexOfFrontArr]);
		cout << endl;
	}
}

//请填写程序

#endif
