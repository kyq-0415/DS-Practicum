#include<utils.h>
#include<cmath>
#include<string>
#include"../include/ljj_Stack.h"
#include"../include/ljj_Queue.h"
using namespace std;


int main(){
    int n,temp;
    queue<int> a,b;
    cin >> n;
    for (int i=0;i<n;++i) cin>>temp,temp%2==1?a.push(temp):b.push(temp);
    while (!(a.empty()&&b.empty())) {
        if (!a.empty()) cout<<a.front()<<" ",a.pop();
        if (!a.empty()) cout<<a.front()<<" ",a.pop();
        if (!b.empty()) cout<<b.front()<<" ",b.pop();
    }
    return 0;
}