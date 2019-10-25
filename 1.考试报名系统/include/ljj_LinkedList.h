#pragma once
#include<iostream>

template <class T> struct __listNode {
    __listNode<T>* prev;
    __listNode<T>* next;
    T data;
};

template <class T> class list{
private:
    typedef __listNode<T> list_node;
    typedef list_node* link_type;
    link_type get_node(){
        link_type p=(link_type)malloc(sizeof(list_node));
        p->next=NULL;
        p->prev=NULL;
        return p;
    }
    void put_node(link_type p){
        p->prev=NULL;
        p->next=NULL;
        p=NULL;
        free(p);
    }
    link_type create_node(const T& x){
        link_type p = get_node();
        p->data = x;
        return p;
    }
    void destroy_node(link_type p){
        put_node(p);
    }
    void __insert(link_type p, const T &x){
        len++;
        link_type temp = create_node(x);
        p->next->prev = temp;
        temp->next = p->next;
        temp->prev = p;
        p->next = temp;
    }
    void __del(link_type p){
        len--;
        p->prev->next=p->next;
        p->next->prev=p->prev;
        destroy_node(p);
    }
    link_type loc(int pos){
        pos+=1;
        if (pos>len) return NULL;
        link_type temp = hnode;
        while (pos--) temp=temp->next;
        return temp;
    }
    link_type loc_by_id(int id){
        auto temp = hnode->next;
        while (temp!=hnode) {
            if (temp->data.id==id) return temp;
            temp=temp->next;
        }
        return NULL;
    }

public:
    list();
    ~list();
    int Class_test(T temp);
    int push_back(const T& x) {__insert(hnode->prev, x); return 0;}
    int empty();
    int plist();
    bool isEmpty() {return hnode==hnode->next;}

    int del(int pos);
    int find_by_id(int id);
    int del_by_id(int id);
    int insert(int pos, const T &x);
    int modify(int pos, const T &x);
    int modify_by_id(int id, const T &x);

    int len;
    link_type hnode; //head node
};

template <class T>
list <T>::list(){
    len = 0;
    hnode = get_node();
    hnode->next = hnode;
    hnode->prev = hnode;
}

template <class T>
list <T>::~list(){
    empty();
    put_node(hnode);
}

template <class T>
int list <T>::del(int pos) {
    link_type p = loc(pos);
    if (p==NULL) {
        std::cout << "Error: Out of range!" << std::endl;
        return 1;
    }
    __del(p);
    return 0;
}

template <class T>
int list <T>::del_by_id(int id) {
    link_type p = loc_by_id(id);
    if (p==NULL) {
        std::cout << "Error: ID not Found!" << std::endl;
        return 1;
    }
    __del(p);
    return 0;
}

template <class T>
int list <T>::insert(int pos, const T &x) {
    link_type p = loc(pos);
    if (p==NULL) {
        std::cout << "Error: Out of range!" << std::endl;
        return 1;
    }
    __insert(p, x);
    return 0;
}

template <class T>
int list <T>::modify(int pos, const T &x) {
    link_type p = loc(pos);
    if (p==NULL) {
        std::cout << "Error: Out of range!" << std::endl;
        return 1;
    }
    p->data=x;
    return 0;
}

template <class T>
int list <T>::modify_by_id(int id, const T &x) {
    link_type p = loc_by_id(id);
    if (p==NULL) {
        std::cout << "Error: ID not Found!" << std::endl;
        return 1;
    }
    p->data=x;
    return 0;
}

template <class T>
int list <T>::find_by_id(int id) {
    link_type p = loc_by_id(id);
    if (p==NULL) {
        std::cout << "Error: ID not Found!" << std::endl;
        return 1;
    }
    p->data.pdata();
    return 0;
}

template <class T>
int list <T>::empty(){
    while (!isEmpty()) __del(hnode->next);
    return 0;
}

template <class T>
int list <T>::plist(){
    auto temp = hnode->next;
    std::cout << "List:" << std::endl;
    while (temp!=hnode) {
        //std::cout << temp->data.age << " ";
        temp->data.pdata();
        temp = temp->next;
    }
    std::cout << std::endl;
    return 0;
}

template <class T>
int list <T>::Class_test(T temp){
    link_type t=create_node(temp);
    std::cout << len << std::endl;
    plist();
    push_back(temp);
    push_back(temp);
    std::cout << len << std::endl;
    plist();
    //empty();
    //std::cout << len << std::endl;
    //plist();
    std::cout << "V of 0 is:" << loc(0)->data.age << std::endl;
    temp.age=5;
    modify(0, temp);
    plist();
    std::cout << "V of 0 is:" << loc(0)->data.age << std::endl;
}