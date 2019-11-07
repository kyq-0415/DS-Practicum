#include<utils.h>
#include<string>
#include<sstream>
#include"../include/ljj_LinkedList.h"
using namespace std;

class datanode{
public:
    bool avail=true;
    int id, age;
    string s_id, s_age;     //should be integer
    string name, cat, gender;

    int pdata() {
        cout << id << " " << name << " " << gender << " " << age << " " << cat << endl;
        return 0;
    }
};

datanode get_info(){
    datanode temp;
    cin >> temp.s_id >> temp.name >> temp.gender >> temp.s_age >> temp.cat;
    stringstream s1(temp.s_id), s2(temp.s_age);

    if (!(temp.s_id.length() && temp.name.length() && temp.gender.length() && temp.s_age.length() && temp.cat.length())) {
        cerr << "Invalid Inputs！Incomplete information!!" << endl;
        temp.avail=false;
        return temp;
    }
    if (!(s1>>temp.id)) {
        cerr << "Invalid Inputs！'" << temp.s_id << "' should be an integer! " << endl;
        temp.avail=false;
        return temp;
    }
    if (!(s2>>temp.age)) {
        cerr << "Invalid Inputs！'" << temp.s_age << "' should be an integer! " << endl;
        temp.avail=false;
        return temp;
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
    cout << "First of all, please establish the candidate information system! " << endl << "Please enter the number of candidates: ";
    cin >> init_num;
    cout << "Please enter candidate's ID, Name, Gender, Age and Examination in order! " << endl;
    for (int i=0;i<init_num;++i) {
        temp=get_info();
        if (temp.avail) info_list.push_back(temp);
        else --i;
        //info_list.plist(); //for test only
    }

    int op;
    while (true) {
        cout << endl << "Please select operation(1-Insert, 2-Delete，3-Search, 4-Modify, 5-Statistics, 0-EXIT)" << endl
        << "Please select operation: ";
        cin >> op;
        if (op>5) {
            cerr << "Invaild Selection, please enter aa number from 0 to 5! " << endl;
            continue;
        }
        if (op==0) return 0;
        if (op==1) {
            int pos;
            cout<<"Please enter the pos to insert: ";
            cin >> pos;
            cout << "Please enter candidate's ID, Name, Gender, Age and Examination in order! " << endl;
            temp=get_info();
            if (temp.avail) info_list.insert(pos-2,temp);
            else continue;
            //info_list.plist(); //for test only
        }
        if (op==2) {
            int id;
            cout<<"Please enter the candidate's ID to Delete: ";
            cin >> id;
            info_list.del_by_id(id);
        }
        if (op==3) {
            int id;
            cout<<"Please enter the candidate's ID to Search: ";
            cin >> id;
            info_list.find_by_id(id);
        }
        if (op==4) {
            int id;
            cout<<"Please enter the candidate's ID to modify: ";
            cin >> id;
            cout << "Please enter candidate's ID, Name, Gender, Age and Examination in order! " << endl;
            temp = get_info();
            info_list.modify_by_id(id, temp);
        }
        if (op==5) info_list.plist();
    }
    return 0;
}