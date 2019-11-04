#pragma once
#include<iostream>

template <class T>
class Vector {
public:
    Vector(int size=0):theSize(size),theCapacity(size+SPACE_CAPACITY){ data = new T[theCapacity];} //    构造函数
    ~Vector(void) { delete[] data;} //    析构函数
    Vector& operator=(Vector& other){
        //    判断是否为自身赋值
        if (this == &other)
            return *this;
        else {
            delete[]data;
            theSize = other.theSize;
            theCapacity = other.theCapacity;
            this->data = new T[theCapacity];

            for (int i = 0; i < theSize; ++i) {
                data[i] = other.data[i];
            }
            return *this;
        }
    } //    重载赋值函数
    Vector(Vector& other) :theSize(0),theCapacity(0),data(NULL){ *this=other; }//    复制构造函数

    //    重新分配空间大小函数
    void reServe(int newCapacity) {
        if (newCapacity <= theCapacity)
            return;

        T *temp = data;
        data = new T[newCapacity];
        theCapacity=newCapacity;
        //std::cout << newCapacity << std::endl;
        for (int i = 0; i < theSize; ++i)
            data[i] = temp[i];
        delete[] temp;
    }
    //    push_back函数
    void push_back(T val) {
        if (theSize == theCapacity)
            reServe(2 * theCapacity + 1);
        data[theSize++] = val;
    }
    T& operator[] (int n) {return data[n];}
    T *data;
    int size() const {return theSize;}
private:
    const int SPACE_CAPACITY = 16;
    int theCapacity;
    int theSize;
};