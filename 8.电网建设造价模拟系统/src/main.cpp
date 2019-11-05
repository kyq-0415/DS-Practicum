#include <iomanip>
#include "../include/ljj_Vector.h"
#include "../include/ljj_Heap.h"

using namespace std;

int cost[1000][1000];

void info() {
    cout << endl;
    cout<<setfill('=')<<setw(70)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "Power grid cost simulation system"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(70)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "A -- (re)Create power grid NODEs"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "B -- Add power grid EDGEs"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "C -- Build Minimum Spanning Tree"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "D -- Display Minimum Spanning Tree"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(50)<< left << "E -- EXIT"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(70)<<" "<<endl<<endl;
}

int main(){
    info();
    bool tag_exit=false;
    int numOfPoint=0, m, temp;
    string tempS, x, y;
    Vector<int> visited, lowest, linkFrom;
    Vector<int> from, to;
    Vector<string> name;
    while (!tag_exit) {
        char selection;
        cout << endl << "Please select operation: ";
        cin >> selection;
        switch (selection) {
            case ('A'): {
                name.clear();
                visited.clear(); lowest.clear(); linkFrom.clear();
                from.clear(); to.clear();
                cout << "Please input number of NODEs: ";
                cin >> numOfPoint;
                cout << "Please input names of NODEs in order: " <<endl;
                for (int i=0; i<numOfPoint; ++i)
                    for (int j=0; j<numOfPoint; ++j) cost[i][j]=INT_MAX;
                for (int i=0; i<numOfPoint; ++i) cin >> tempS, name.push_back(tempS);
                break;
            }
            case ('B'): {
                while (true) {
                    bool xfound=false, yfound=false;
                    int indx, indy;
                    cout << "Please input two NODEs and one EDGE: " ;
                    cin >> x >> y >> temp;
                    if (x=="?" && y=="?") break;
                    for (indx=0; indx<name.size(); ++indx)
                        if (name[indx]==x) {xfound=true; break;}
                    for (indy=0; indy<name.size(); ++indy)
                        if (name[indy]==y) {yfound=true; break;}
                    if (xfound && yfound) {
                        cost[indx][indy] = temp;
                        cost[indy][indx] = temp;
                    } else {}
                }
                break;
            }
            case ('C') : {
                if (numOfPoint==0||name.size()<numOfPoint||name.size()==0) {
                    cerr << "Lack of vital information! Please do op A first" << endl;
                    break;
                }
                cout << "Please input the initial NODE: ";
                cin >> tempS;
                bool xfound=false;
                int indx;
                for (indx=0; indx<name.size(); ++indx)
                    if (name[indx]==tempS) {xfound=true; break;}
                if (!xfound) {
                    cerr << "Fail to find a NODE named '"<< tempS << "' "<< endl;
                    break;
                } else temp=indx;

                for (int i=0; i<numOfPoint; ++i) visited.push_back(0), lowest.push_back(cost[temp][i]), linkFrom.push_back(temp);
                visited[temp]=1;
                for (int i=0; i<numOfPoint; ++i){
                    int min=INT_MAX, pos;
                    for (int j=0; j<numOfPoint; ++j)
                        if (!visited[j] && min>lowest[j]) min=lowest[j], pos=j;
                    if (min==INT_MAX) break;
                    visited[pos]=1;
                    from.push_back(pos);
                    to.push_back(linkFrom[pos]);
                    for (int j=0; j<numOfPoint; ++j)
                        if (cost[j][pos]<lowest[j]) lowest[j]=cost[j][pos], linkFrom[j]=pos;
                }
                if (from.size()==numOfPoint-1)
                    cout << "Build Successfully!" << endl;
                else cout << "Build Failed!" << endl;
                break;
            }
            case ('D'): {
                if (from.size()<numOfPoint-1 || numOfPoint==0)
                    cerr << "Fail to display the Minimum Spanning Tree! Please do op C first" << endl;
                else {
                    cout << "MST's edges and corresponding costs:"<< endl;
                    for (int i = 0; i < from.size(); ++i) {
                        if (from[i] > to[i]) swap(from[i], to[i]);
                        cout << name[from[i]] << "--(" << cost[from[i]][to[i]] << ")--" << name[to[i]] << endl;
                    }
                }
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
}