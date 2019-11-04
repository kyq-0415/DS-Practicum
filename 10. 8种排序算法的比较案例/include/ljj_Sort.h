#pragma once
#include <iostream>
//#include <vector>
#include "../include/ljj_Vector.h"
using namespace std;

void swap(long &x,long &y){
    long temp;
    temp=x;
    x=y;
    y=temp;
}

int qsort(Vector<long>& v, int L, int R){
    int i=L, j=R, x=v[L];
    long long count=0;
    if (L>=R) return 0;
    while (i<j) {
        while (i<j&&v[j]>=x) --j;
        if (i<j) v[i++]=v[j],++count;
        while (i<j&&v[i]<x) ++i;
        if (i<j) v[j--]=v[i],++count;
    }
    v[i]=x; ++count;
    count+=qsort(v,L,i-1);
    count+=qsort(v,i+1,R);
    return count;
}

int Quick_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    count+=qsort(v,0,len-1);
    return count;
}

int Bubble_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    for (int i=0;i<len-1;++i)
        for (int j=0;j<len-i-1;++j) {
            if (v[j] > v[j + 1]) swap(v[j], v[j + 1]);
            count++;
        }
    return count;
}

int Selection_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    for (int i=0;i<len;++i) {
        int p=0;
        for (int j = i+1; j < len; ++j) {
            count++;
            if (v[j] < v[p]) p = j;
        }
        swap(v[i],v[p]);
    }
    return count;
}

int Insertion_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    for (int i=0;i<len;++i) {
        int temp=v[i];
        int j=i;
        while (j>=0) {
            count++;
            if (j>0&&v[j-1]>temp) v[j]=v[j-1];
            else {v[j]=temp; break;}
            j--;
        }
    }
    return count;
}


int Shell_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    for (int gap=len/2;gap>0;gap/=2){
        for (int i=gap;i<len;++i) {
            int temp=v[i], j;
            for (j=i-gap;j>0&&v[j]>temp;j-=gap) v[j+gap]=v[j],++count;
            v[j+gap]=temp;++count;
        }
    }
    return count;
}


long long heapify(Vector<long>& v,int curNode, int size){
    long long count=0;
    int left=2*curNode+1;
    int right=2*curNode+2;
    int max=curNode;
    if (left<size) max=v[max]>v[left]?max:left;
    if (right<size) max=v[max]>v[right]?max:right;
    if (max!=curNode) {
        swap(v[max],v[curNode]);
        ++count;
        count+=heapify(v,max,size);
    }
    return count;
}

int Heap_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    for (int i = len - 1; i >= 0; i--)
        count += heapify(v, i, len);
    for (int size=len;size>0;size--) {
            count += heapify(v, 0, size);
        swap(v[0],v[size-1]);
    }
    return count;
}

int Msort(Vector<long>& v, int L, int R){
    long long count=0;
    if (L>=R) return 0;
    int mid=(L+R)/2;
    count+=Msort(v,L,mid);
    count+=Msort(v,mid+1,R);
    int p1=L, p2=mid+1;
    vector<long> temp;
    while (p1<=mid && p2<=R) temp.push_back(v[p1]<v[p2]?v[p1++]:v[p2++]),++count;
    while (p1<=mid) temp.push_back(v[p1++]),++count;
    while (p2<=R) temp.push_back(v[p2++]),++count;
    for (int i=0;i<temp.size();++i)
        v[L+i]=temp[i];
    return count;
}

int Merge_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    count += Msort(v,0,len-1);
    return count;
}

int maxbit(Vector<long>& v) {
    int max=0, len=v.size();
    for (int i=0;i<len;++i) max=v[max]<v[i]?i:max;
    int d=0,t=v[max];
    while (t>=10) t/=10,++d;
    return d+1;
}

int Radix_Sort(Vector<long>& v){
    int len=v.size();
    long long count=0;
    int counter[10], radix=1;
    for (int i=0;i<maxbit(v);++i) {
        Vector<long> tmp(v.size());
        memset(counter,0, sizeof(counter));
        for (int j = 0; j < len; ++j) ++counter[(v[j] / radix) % 10];
        for (int j = 1; j < 10; ++j) counter[j] += counter[j - 1];
        for (int j = len - 1; j >= 0; --j) tmp[--counter[(v[j] / radix) % 10]] = v[j], ++count;
        v=tmp;
        radix*=10;
    }
    return count;
}
