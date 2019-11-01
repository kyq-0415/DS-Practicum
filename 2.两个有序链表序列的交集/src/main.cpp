#include<utils.h>
#include<string>
#include"../include/ljj_LinkedList.h"
using namespace std;

class datanode{
public:
    bool avail=true;
    int data;
    int pdata() {
        cout <<  data << " ";
        return 0;
    }
};

int main(){
    list<datanode> list1, list2, list3;
    datanode temp;
    while (temp.data!=-1) cin>>temp.data, list1.push_back(temp);
    list1.del(list1.len-1);
    temp.data=0;
    while (temp.data!=-1) cin>>temp.data, list2.push_back(temp);
    list2.del(list2.len-1);
    //list1.plist();
    //list2.plist();
    while (!list1.isEmpty() && !list2.isEmpty()) {
        int h1=list1.hnode->next->data.data;
        int h2=list2.hnode->next->data.data;
        if ( h1 == h2) {
            //cout << h1 << " ";
            list3.push_back(list1.hnode->next->data);
            list1.del(0);
            list2.del(0);
        }
        if (h1 < h2) list1.del(0);
        if (h1 > h2) list2.del(0);

    }
    list3.plist();
    return 0;
}