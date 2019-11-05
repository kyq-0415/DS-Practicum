#include <random>
#include <algorithm>
#include <iomanip>
#include <string>
#include "../include/ljj_Vector.h"
#include "../include/ljj_Tree.h"

using namespace std;

void info() {
    cout << endl;
    cout<<setfill('=')<<setw(75)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "Genealogy management system"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(75)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "A -- Build family"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "B -- Add family member"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "C -- Disband a part of the family"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "D -- Change family member's name"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(50)<< left << "E -- EXIT"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(75)<<" "<<endl<<endl;
}

int main(){
    info();
    string name,name_t;
    int n;
    cout << "Please input the name of ancestor: ";
    cin >> name;
    cout << "The ancestor's name is: " << name << endl << endl;
    Tree<string> geneTree(name);

    bool tag_exit=false;
    while (!tag_exit) {
        char selection;
        cout << "Please select operation: ";
        cin >> selection;
        switch (selection) {
            case ('A'): {
                cout << "Please input the name to establish family: ";
                cin >> name;
                if (geneTree.find(name)== nullptr) {
                    cerr << "The name '" << name << "' doesn't exist! try again plz" << endl;
                    break;
                }
                __treenode<string>* father = geneTree.find(name);
                cout << "Please input the number of " << name << "'s offsprings: ";
                cin >> n;
                Vector<__treenode<string> *> temp;
                cout << "Please input the names of " << name << "'s offsprings in order: ";
                for (int i=0; i<n; ++i) {
                    cin >> name_t;
                    __treenode<string> *son = new __treenode<string>(name_t, father);
                    temp.push_back(son);
                }
                geneTree.build(name, temp);
                cout << name << "'s first generation offsprings are: ";
                geneTree.outSpring(name);
                cout << endl;
                break;
            }
            case ('B'): {
                cout << "Please input the name to add offspring: ";
                cin >> name;
                if (geneTree.find(name)== nullptr) {
                    cerr << "The name '" << name << "' doesn't exist! try again plz" << endl;
                    break;
                }
                cout << "Please input the names of " << name << "'s offspring: ";
                cin >> name_t;
                geneTree.add(name, name_t);
                cout << name << "'s first generation offsprings are: ";
                geneTree.outSpring(name);
                cout << endl;
                break;
            }
            case ('C') : {
                cout << "Please input the name to disband the family: ";
                cin >> name;
                if (geneTree.find(name)== nullptr) {
                    cerr << "The name '" << name << "' doesn't exist! try again plz" << endl;
                    break;
                }
                if (!geneTree.isRoot(name)) {
                    cout << name << "'s family is going to be disbanded. " << endl;
                    cout << name << "'s first generation offsprings are: ";
                    geneTree.outSpring(name);
                }
                geneTree.clear(name);
                cout << endl;
                break;
            }
            case ('D'): {
                cout << "Please input the current name to change: ";
                cin >> name;
                if (geneTree.find(name)== nullptr) {
                    cerr << "The name '" << name << "' doesn't exist! try again plz" << endl;
                    break;
                }
                cout << "Please input the new names of " << name << "' : ";
                cin >> name_t;
                geneTree.change(name, name_t);
                cout << name << "'s has been changed to " << name_t << endl <<endl;
                break;
            }
            case ('E'): {
                tag_exit=true;
                break;
            }
            default:
                cerr << "Invaild Selection, please input a character from A to E!" <<endl << endl;
        }
    }

    return 0;
}