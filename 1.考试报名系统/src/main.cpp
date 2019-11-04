#include<utils.h>
#include<string>
#include"../include/ljj_LinkedList.h"
using namespace std;

class datanode{
public:
    bool avail=true;
    int id, age;
    string name, cat, gender;

    int pdata() {
        cout << id << " " << name << " " << gender << " " << age << " " << cat << endl;
        return 0;
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
    cout << "首先请建立考生信息系统！" << endl << "请输入考生人数：";
    cin >> init_num;
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
    for (int i=0;i<init_num;++i) {
        temp=get_info();
        if (temp.avail) info_list.push_back(temp);
        else return 0;
        //info_list.plist(); //for test only
    }

    int op;
    while (true) {
        cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl
        << "请选择您要进行的操作:";
        cin >> op;
        if (op>5 || op==0) continue;
        if (op==1) {
            int pos;
            cout<<"请输入您要插入的考生的位置：";
            cin >> pos;
            cout << "请依次输入插入考生的考号，姓名，性别，年龄及报考类别！" << endl;
            temp=get_info();
            if (temp.avail) info_list.insert(pos-2,temp);
            else return 0;
            //info_list.plist(); //for test only
        }
        if (op==2) {
            int id;
            cout<<"请输入要删除的考生的考号：";
            cin >> id;
            info_list.del_by_id(id);
        }
        if (op==3) {
            int id;
            cout<<"请输入要查找的考生的考号：";
            cin >> id;
            info_list.find_by_id(id);
        }
        if (op==4) {
            int id;
            cout<<"请输入要修改的考生的考号：";
            cin >> id;
            cout << "请依次输入修改考生的考号，姓名，性别，年龄及报考类别！" << endl;
            temp = get_info();
            info_list.modify_by_id(id, temp);
        }
        if (op==5) info_list.plist();
    }
    return 0;
}