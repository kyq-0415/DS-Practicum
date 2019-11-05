#pragma once
#include <iostream>
#include "../include/ljj_Vector.h"
using namespace std;

template <typename T>
class Heap{
private:
    Vector<T> data;
public:
    Heap(){};
    Heap(Vector<T> v);
    void adj(int curNode=0);
    void push_heap(T val);
    void push_heap(T val, int pos);
    void ergodic();
    T pop_heap();
    void swap(T &x,T &y){
        T temp;
        temp=x;
        x=y;
        y=temp;
    }
    int size() {return data.size();}
};

template <typename T>
Heap<T>::Heap(Vector<T> v){
    data = v;
    for (int i=size()-1; i>=0; --i) adj(i);
}

template <typename T>
T Heap<T>::pop_heap(){
    T temp=data[0];
    swap(data[0], data[size()-1]);
    data.Delete(size()-1);
    adj();
    return temp;
}

template <typename T>
void Heap<T>::adj(int curNode){
    int left=2*curNode+1;
    int right=2*curNode+2;
    int min=curNode;
    if (left<data.size()) min=data[min]<data[left]?min:left;
    if (right<data.size()) min=data[min]<data[right]?min:right;
    if (min!=curNode) swap(data[min],data[curNode]), adj(min);
}

template <typename T>
void Heap<T>::push_heap(T val){
    data.push_back(val);
    push_heap(val, size()-1);
}

template <typename T>
void Heap<T>::push_heap(T val, int pos){
    if (pos==0) return;
    int father = (pos-1)/2;
    if (data[father]>data[pos]) swap(data[father],data[pos]), push_heap(val, father);
}

