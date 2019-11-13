#include <iomanip>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/ljj_Vector.h"
#include "../include/ljj_Heap.h"

using namespace std;

string temp, INPUT_PATH="../input.txt", OUTPUT_PATH="../output.txt";
ifstream inf(INPUT_PATH);
ofstream outf(OUTPUT_PATH);

struct course{
    string code;
    string name;
    string s_hours, s_Semester;
    int hours;
    int Semester;
    Vector<string> preCourse;
    friend ostream& operator<< (ostream& out, course& c) {
        cout << c.code << " " << c.name << " " << c.hours << " " << c.Semester << " ";
        for (int i=0; i<c.preCourse.size(); ++i) cout << c.preCourse[i] << " ";
        cout << endl;
        return out;
    }   //for test only
    friend ifstream& operator>> (ifstream& out, course& c) {
        string buffer;
        string temp;
        getline(inf, buffer);
        stringstream ss;
        ss << buffer;
        ss >> c.code >> c.name >> c.s_hours >> c.s_Semester;
        stringstream check1(c.s_hours), check2(c.s_Semester);
        if (!(check1>>c.hours)||!(check2>>c.Semester)) {
            cerr << "Invalid Input Format! Plz check again!" << endl;
            exit(1);
        }
        while (ss >> temp) c.preCourse.push_back(temp);
        //cout << buffer;
        return out;
    }
};

Vector<course> courses;
Vector<course> topoOrder[100];
Vector<int> nex[10000];
int ind[10000], hours[1000], semCount[10000];
bool used[10000];
int maxSem=0;
int totalHours=0, curTotalHours=0;

string semName[4]={"","1st", "2nd", "3rd"};
int jumpDay[11]={0,1,3,5,2,4,1,3,5,2,4};
int jumpTime[5]={0,1,3,6,8};
int weektime[6][5]={{0,0,0,0,0},
                {0,2,3,2,3},
                {0,2,3,2,3},
                {0,2,3,2,3},
                {0,2,3,2,3},
                {0,2,3,2,3}};

bool avai[6][5];
int table[15][15];
int atleast[1000];

void output(){
    for (int i=1; i<=maxSem; ++i) {
        memset(&table[0][0],0,sizeof(table));
        memset(avai,0,sizeof(avai));
        if (i<=3) outf <<endl<< "The " << semName[i] << " Semester: "<<endl;
        else outf <<endl<< "The " << i << "th Semester: "<<endl ;
        if (i==6) {

        }
        for (int j = 0; j < topoOrder[i].size(); ++j) {
                for (int d=1; d<=11; ++d)
                for (int t=4; t>=1; --t) {
                    if (!avai[jumpDay[d]][t] && weektime[jumpDay[d]][t] == 3 && topoOrder[i][j].hours >= 3) {
                        avai[jumpDay[d]][t] = true;
                        topoOrder[i][j].hours -= 3;
                        for (int k = 0; k < weektime[jumpDay[d]][t]; ++k) table[jumpDay[d]][jumpTime[t] + k] = j + 1;
                        break;
                    }

                    if (!avai[jumpDay[d]][t] && weektime[jumpDay[d]][t] == 2 && topoOrder[i][j].hours >= 2) {
                        avai[jumpDay[d]][t] = true;
                        topoOrder[i][j].hours -= 2;
                        for (int k = 0; k < weektime[jumpDay[d]][t]; ++k) table[jumpDay[d]][jumpTime[t] + k] = j + 1;
                        break;
                    }
                }
        }
        for (int j = 0; j < topoOrder[i].size(); ++j)
            while (topoOrder[i][j].hours>0)
                for (int k = 1; k<=50; ++k)
                    if (table[(k/10)+1][k%10+1]==0) {
                        table[(k/10)+1][k%10+1]=j;
                        --topoOrder[i][j].hours;
                        break;
                    }
        for (int p=1; p<=10; ++p) {
            for (int j = 1; j <= 5; ++j)
                if (table[j][p]==0) outf << setw(5) << setiosflags(ios::left) << "无  ";
                else outf << setw(5) << setiosflags(ios::left) << topoOrder[i][table[j][p]-1].name << "  ";
            outf << endl;
        }
        outf << endl;
    }
    cout << endl << "The Curriculum has been saved! " <<endl;
    inf.close();
    outf.close();
    exit(0);
}

int topoSearch(int sem, int count){
    if (count == courses.size()) output();
    if (sem == maxSem +1) return 0;
    if (curTotalHours + (maxSem-sem+1)*50 < totalHours) return 0;
    if (hours[sem]>50) return 0;

    for (int i=0; i<courses.size(); ++i)
        if (courses[i].Semester==0 || courses[i].Semester==sem)
        if (ind[i]==0 && !used[i] && sem>=atleast[i]) {
            int tempLeast[1000];
            for (int j=0; j<nex[i].size(); ++j) --ind[nex[i][j]], tempLeast[nex[i][j]]=atleast[nex[i][j]], atleast[nex[i][j]]=sem+1;
            used[i] = true; curTotalHours+=courses[i].hours; hours[sem]+=courses[i].hours;
            semCount[sem]-=(courses[i].Semester==sem)?1:0;
            topoOrder[sem].push_back(courses[i]);
            topoSearch(sem, count+1);
            used[i] = false; curTotalHours-=courses[i].hours; hours[sem]-=courses[i].hours;
            semCount[sem]+=(courses[i].Semester==sem)?1:0;
            topoOrder[sem].Delete(topoOrder[sem].size() - 1);
            for (int j=0; j<nex[i].size(); ++j) ++ind[nex[i][j]], atleast[nex[i][j]]=tempLeast[nex[i][j]];
        }
    if (semCount[sem]==0) topoSearch(sem+1, count);
    return 0;
}


void info() {
    cout << endl;
    cout<<setfill('=')<<setw(70)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "Welcome to the Curriculum software"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(70)<<" "<<endl<<endl;
    cout << "Do you want to use the default input file path? (Y/n)";
    cin >> temp;
    if (temp == "n") {
        cout << "Please enter the input file path: " ;
        cin >> INPUT_PATH;
        inf.open(INPUT_PATH);
        if (!inf) {
            cerr << endl << "The current input file path is incorrect and the default path is used instead. " <<endl;
            INPUT_PATH="../input.txt";
            inf.open(INPUT_PATH);
        }
    }
}

int main(){
    info();
    while (!inf.eof()) {
        course bufCourse;
        inf >> bufCourse;
        if (bufCourse.Semester > maxSem) maxSem = bufCourse.Semester;
        courses.push_back(bufCourse);
        totalHours += bufCourse.hours;
        ++semCount[bufCourse.Semester];
    }
    for (int i = 0; i < courses.size(); ++i) {
        ind[i] = courses[i].preCourse.size();
        for (int j=0; j< courses.size(); ++j)
            for (int k=0; k<courses[j].preCourse.size(); ++k)
                if (courses[j].preCourse[k]==courses[i].code) {
                    nex[i].push_back(j);
                    break;
                }
    }
    //test table
    /*
    for (int i = 0; i < courses.size(); ++i) {
        cout << courses[i].code << ":" ;
        for (int j = 0; j < nex[i].size(); ++j)
            cout << courses[nex[i][j]].code << " ";
        cout << endl;
    }
     */
    topoSearch(1,0);
    cerr << endl << "The current input file path has no solution! " <<endl;
    exit(1);
}