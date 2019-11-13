#pragma once
#include<iostream>
#include<string>
#include "../include/ljj_Vector.h"

using std::cout, std::endl, std::cerr;

template <class T> class __treenode {
private:
    Vector<__treenode<T>* > spring;
    __treenode<T>* father;
    T value;
public:
    __treenode(){
        register T temp;
        value = temp;
        father = nullptr;
    }
    __treenode(T theVal,__treenode<T> * theFather= nullptr):value(theVal){
        father = theFather;
    }
    ~__treenode(){
        father=nullptr;
    }

    T& getValue() {return value;}
    const T& getValue() const {return value;}
    void setValue(T val) {value = val;}

    __treenode<T>* getFather() const {return father; }
    void setFather(__treenode<T>* theFather) {father = theFather; }

    Vector<__treenode<T>* > &getSpring() {return spring;}
    const Vector<__treenode<T>* > &getSpring() const {return spring;}
    void setSpring(Vector<__treenode<T>* > theSpring) {spring = theSpring;}
};

template <class T>
class Tree {
private:
    __treenode<T>* root;
public:
    Tree() {root=nullptr;}
    Tree(T val) {root= new __treenode<T>(val);}
    ~Tree();
    bool isRoot(T val){return find(val)==root;}
    void ergodic();
    void ergodic(__treenode<T>* fa);
    void build(T val, Vector<__treenode<T>* > v);
    void clear();
    void clear(T val);
    bool clear(__treenode<T>* fa);
    void outSpring(T val);
    bool add(T target, T val);
    //void Delete(T val);
    bool change(T target, T val);
    __treenode<T>* find(T val);
    __treenode<T>* find(__treenode<T>* cur, T val);
};

template <class T>
void Tree<T>::build(T val, Vector<__treenode<T>* > v) {
    Vector<__treenode<T>* > &tempv = find(val)->getSpring();
    while (tempv.size()) tempv.Delete(0);
    while (v.size())
        if (find(v[0]->getValue())!= nullptr) {
            cerr << "This name '"<< v[0]->getValue() <<"' already exists! try again plz" << endl;
            v.Delete(0);
        }
        else {
            tempv.push_back(v[0]);
            v.Delete(0);
        }
}


template <class T>
bool Tree<T>::add(T target, T val){
    if (find(val)!= nullptr) {
        cerr << "The name '"<< val <<"' already exists! try again plz" << endl;
        return false;
    }
    if (find(target) == nullptr) {
        cerr << "The target '"<< target <<"' doesn't exist! try again plz" << endl;
        return false;
    }
    __treenode<T>* thefather = find(target);
    __treenode<T>* theSpring = new __treenode<T>(val, thefather);
    thefather->getSpring().push_back(theSpring);
    return true;
}

template <class T>
bool Tree<T>::change(T target, T val){
    if (find(val)!= nullptr) {
        cerr << "The name '"<< val <<"' already exists! try again plz" << endl;
        return false;
    }
    if (find(target) == nullptr) {
        cerr << "The target '"<< target <<"' doesn't exist! try again plz" << endl;
        return false;
    }
    __treenode<T>* father = find(target);
    father->setValue(val);
    return true;
}

template <class T>
__treenode<T>* Tree<T>::find(T val){
    return find(root, val);
}


template <class T>
__treenode<T>* Tree<T>::find(__treenode<T>* cur, T val){
    if (cur->getValue()==val) return cur;
    int len=cur->getSpring().size();
    for (int i=0;i<len;++i) {
        __treenode<T>* temp = find(cur->getSpring()[i], val);
        if (temp) return temp;
    }
    return nullptr;
}



template <class T>
void Tree<T>::ergodic() {
    ergodic(root);
    cout << endl;
}

template <class T>
void Tree<T>::ergodic(__treenode<T>* fa) {
    int len=fa->getSpring().size();
    cout << fa->getValue() << " ";
    for (int i=0;i<len;++i) ergodic(fa->getSpring()[i]);
}

template <class T>
void Tree<T>::outSpring(T val){
    Vector<__treenode<T>* > &v = find(val)->getSpring();
    int len=v.size();
    for (int i=0;i<len;++i) cout << v[i]->getValue() << " ";
    cout << endl;
}



template <class T>
Tree<T>::~Tree(){
    clear();
}

template <class T>
void Tree<T>::clear(){
    clear(root);
}

template <class T>
void Tree<T>::clear(T val){
    clear(find(val));
}

template <class T>
bool Tree<T>::clear(__treenode<T>* fa){
    if (fa==root) {
        cerr << "The name '"<< fa->getValue() <<"' is protected as the ancestor" << endl;
        return false;
    }
    int len=fa->getSpring().size();
    Vector<__treenode<T>* > v = fa->getSpring();
    for (int i=0;i<len;++i) clear(v[i]);
    if (fa->getFather()!= nullptr)
        for (int i=0;i<fa->getFather()->getSpring().size();++i)
            if (fa->getFather()->getSpring()[i] == fa) {
                fa->getFather()->getSpring().Delete(i);
                break;
            }
    delete fa;
    return true;
}