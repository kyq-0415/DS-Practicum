#include<utils.h>
#include<string>
#include"../include/LinkedList.h"
using namespace std;

class datanode{
public:
    bool avail=true;
    int id, age;
    string name, cat, gender;

    int pdata() {
        cout << id << " " << name << " " << gender << " " << age << " " << cat << endl;
    }
};

datanode get_info(){
    datanode temp;
    cin >> temp.id >> temp.name >> temp.gender >> temp.age >> temp.cat;
    if (!(temp.id && temp.name.length() && temp.gender.length() && temp.age && temp.cat.length())) {
        cout << "Invalid Inputs！" << endl;
        temp.avail=false;
    }
    //temp.pdata(); //for test only
    return temp;
}

int main(){
    //list<datanode> l1;
    //datanode temp;
    //temp.age=1;
    //l1.Class_test(temp);

    list<datanode> info_list;
    datanode temp;
    int init_num;
    cin >> init_num;
    for (int i=0;i<init_num;++i) {
        temp=get_info();
        if (temp.avail) info_list.push_back(temp);
        else return 0;
        //info_list.plist(); //for test only
    }

    int op;
    while (true) {
        cin >> op;
        if (op>5 || op==0) continue;
        if (op==1) {
            int pos;
            cin >> pos;
            temp=get_info();
            if (temp.avail) info_list.insert(pos-2,temp);
            else return 0;
            //info_list.plist(); //for test only
        }
        if (op==2) {
            int id;
            cin >> id;
            info_list.del_by_id(id);
        }
        if (op==3) {
            int id;
            cin >> id;
            info_list.find_by_id(id);
        }
        if (op==4) {
            int id;
            cin >> id;
            temp = get_info();
            info_list.modify_by_id(id, temp);
        }
        if (op==5) info_list.plist();
    }
    return 0;
}