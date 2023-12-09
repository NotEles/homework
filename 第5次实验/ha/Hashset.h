#ifndef _HASHSET_H
#define _HASHSET_H

#include <iostream>

template <class T>
class Node
{
public:
    Node<T> *next;
    T data;
};

template <class T, class HashFun, class EqualFun>
class Hashset
{
public:
    //请填写程序
    void insert(T* t1);
    void showInfo(bool b1);
    T* find(T& t1);
    void remove(T& t1);
    Hashset();
    ~Hashset();
    HashFun f3;
    EqualFun f5;
private:
    Node<T> **rootArr;
    int rootCapacity;	
    int totalCount;		
    void expandRoot();

    const int INITIAL_ROOT_CAPACITY = 16;
    //请填写程序
};

template <class T, class HashFun, class EqualFun>
Hashset<T,HashFun,EqualFun>::Hashset()
{
    rootCapacity = INITIAL_ROOT_CAPACITY;
    rootArr = new Node<T> * [rootCapacity];
    for (int i = 0; i < rootCapacity; i++)
        rootArr[i] = nullptr;
    totalCount = 0;
}

template <class T, class HashFun, class EqualFun>
Hashset<T, HashFun, EqualFun>::~Hashset()
{
    for (int i = 0; i < rootCapacity; i++)
    {
        Node<T>* p = rootArr[i], * q;
        while (p != nullptr)
        {
            q = p;
            p = p->next;
            delete q;
        }
    }
    delete[] rootArr;
}


//请填写程序
template <class T, class HashFun, class EqualFun>
void Hashset<T, HashFun, EqualFun>::expandRoot()
{
    Node<T>** oldRootArr = rootArr;
    int oldRootCapacity = rootCapacity;
    rootCapacity <<= 1;
    rootArr = new Node<T> * [rootCapacity];
    for (int i = 0; i < rootCapacity; i++)
        rootArr[i] = nullptr;
    for (int i = 0; i < oldRootCapacity; i++)
    {
        Node<T>* p = oldRootArr[i];
        while (p)
        {
            Node<T>* pOldNext = p->next;
            int hashValue = f3(p->data) % rootCapacity;
            p->next = rootArr[hashValue];
            rootArr[hashValue] = p;
            p = pOldNext;
        }
    }
    delete[] oldRootArr;
}

template <class T, class HashFun, class EqualFun>
void Hashset<T, HashFun, EqualFun>::insert(T* s)
{
    if (totalCount >= rootCapacity)
        expandRoot();
    int hashValue = f3(*s) % rootCapacity;
    Node<T>* f = new Node<T>;
    f->data = *s;
    f->next = rootArr[hashValue];
    rootArr[hashValue] = f;
    totalCount++;
}

template <class T, class HashFun, class EqualFun>
void Hashset<T, HashFun, EqualFun>::remove(T& s)
{
    int hashValue = f3(s) % rootCapacity;
    Node<T>* p = rootArr[hashValue];
    Node<T>* tem = nullptr;
    if (p == nullptr)
    {
        std::cout << "There is no such element.\0";
    }
    else if (f5(p->data, s))
    {
        rootArr[hashValue] = p->next;
        delete p;
        totalCount--;
        std::cout << "have removed...\0";
    }
    else
    {
        int cm = 0;
        for (; p != nullptr; p = p->next)
        {
            if (f5(p->data, s))
            {
                tem->next = p->next;
                delete p;
                totalCount--;
                cm++;
                //std::cout << "have removed...\0";
                return;
            }
            tem = p;
        }
        if (cm == 0)
            std::cout << "there is no such element.\0";
    }
}

template <class T, class HashFun, class EqualFun>
T* Hashset<T, HashFun, EqualFun>::find(T& s)
{
    int hashValue = f3(s) % rootCapacity;
    Node<T>* p = rootArr[hashValue];
    if (p == nullptr)
        std::cout << "there is no such element.\0";
    for (; p != nullptr; p = p->next)
    {
        if (f5(s, p->data))
        {
            T* tem = &p->data;
            return tem;
        }
    }
    std::cout << "there is no such element.\0";
    return nullptr;
}
//到ci
template <class T, class HashFun, class EqualFun>
void Hashset<T, HashFun, EqualFun>::showInfo(bool showAllDetails)
{
    using namespace std;
    cout << "Hashset Status:" << endl
        << "Root array capacity: " << rootCapacity << endl
        << "Total element count: " << totalCount << endl;
    if (!showAllDetails)
        return;
    cout << endl
        << "All Elements:" << endl;
    for (int i = 0; i < rootCapacity; i++)
    {
        cout << '[' << i << "] --> ";
        Node<T>* p = rootArr[i];
        while (p)
        {
            cout << f3(p->data);
            cout << " --> ";
            p = p->next;
        }
        cout << endl;
    }
    cout << endl;
}

#endif
