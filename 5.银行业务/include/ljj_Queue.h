#pragma once
#include<iostream>
#include"../include/ljj_LinkedList.h"

template <class T, class Sequence=list<T> >
class queue {
protected:
    Sequence c;
public:
    bool empty() const {return c.isEmpty();}
    int size() const {return c.len;}
    T front() {return c.isEmpty()?-1:c.hnode->next->data;}
    void push(const T& x) {c.push_back(x);}
    void pop() {c.del(0);}
};